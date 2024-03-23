#include "Public/TheGame.h"

#include <string>

#include "Public/GameObject.h"
#include "Public/Ship.h"
#include "Public/Enemy.h"
#include "Public/Bullet.h"
#include "Public/Particle.h"
#include "Public/ParticleSystem.h"
#include "Public/Statics.h"
#include "Public/Global.h"
#include "Public/Debug.h"

#include <thread>

#define USE_THREAD 1

TheGame::TheGame()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(GameStatics::screenWidth, GameStatics::screenHeight, "Game01");

	SetTargetFPS(60);

	Timer timer("TheGame constructor");

	gameState = EGameState::EGS_Start;

	// Spawn spaceship (player)
	spaceShip = new Ship( Vector2{GameStatics::halfScreenWidth, GameStatics::halfScreenHeight },Vector2{20,20},ORANGE );
	spaceShip->movementSpeed = 200.0f;
	
	// Spawn enemies and store them
	for (size_t i = 0; i < 10; i++)
	{		
		float rndSpeed = GameStatics::RandomFloat(250.0f, 350.0f);
		enemies.push_back(std::make_unique<Enemy>(Vector2{0}, Vector2{ 0 }, RED, BLACK, spaceShip->position, rndSpeed));
	}
	
	// Spawn and store the stars
	for (size_t i = 0; i < 200; i++)
	{
		float rndX = GameStatics::RandomFloat(0, GameStatics::screenWidth);
		float rndY = GameStatics::RandomFloat(0, GameStatics::screenHeight);

		float rndScale = GameStatics::RandomFloat(2.0f, 8.0f);
		float rndAlpha = GameStatics::RandomFloat(0.1, 1.0f);
		stars.push_back(Star{ {rndX,rndY},{rndScale}, Fade(WHITE, rndAlpha),rndAlpha, 1 });
	}
}

void TheGame::Run()
{
#if USE_THREAD

	std::cout << "USING THREADS\n";

	std::thread workerObjectLifetime(&TheGame::ManageGameObjectsLifetimeThread,this);	
	workerObjectLifetime.detach();

	std::thread workerCollisionCheck(&TheGame::CollisionsCheckThread, this);
	workerCollisionCheck.detach();
#endif

	while (!WindowShouldClose())
	{
		deltaTime = GetFrameTime();

		switch (gameState)
		{
		case TheGame::EGameState::EGS_Start:
			RenderMenuScene();
			break;
		case TheGame::EGameState::EGS_Play:
			RenderGameScene();
			break;
		case TheGame::EGameState::EGS_GameOver:
			RenderGameOverScene();
			break;		
		}		
	}	

	CloseWindow();
}


Vector2 TheGame::ManageKeyboardInput()
{
	Vector2 inputDir = { 0,0 };
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
	{
		inputDir.x = 1.0;
	}
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
	{
		inputDir.x = -1.0;
	}

	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
	{
		inputDir.y = -1.0;
	}
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
	{
		inputDir.y = 1.0;
	}

	return inputDir;
}

void TheGame::ManageGameObjectsLifeTime()
{
	// Delete gameobjects if lifespan is or below 0
	GameStatics::spawnedBullets.erase(
		std::remove_if(
			GameStatics::spawnedBullets.begin(),
			GameStatics::spawnedBullets.end(),
			[](const std::shared_ptr<GameObject>& gameObject) { return gameObject->GetLifeTime() <= 0; }),
		GameStatics::spawnedBullets.end());

	GameStatics::particleSystemsToManage.erase(
		std::remove_if(
			GameStatics::particleSystemsToManage.begin(),
			GameStatics::particleSystemsToManage.end(),
			[](const std::shared_ptr<ParticleSystem>& particleSys) { return particleSys->bIsSysActive == false; }),
		GameStatics::particleSystemsToManage.end());
}

void TheGame::ManageGameObjectsLifetimeThread()
{
	using namespace std::literals::chrono_literals;
	while (true)
	{
		//std::lock_guard<std::mutex> lock(manageGOMutex);
		manageGOMutex.lock();
		// Delete gameobjects if lifespan is or below 0
		GameStatics::spawnedBullets.erase(
			std::remove_if(
				GameStatics::spawnedBullets.begin(),
				GameStatics::spawnedBullets.end(),
				[](const std::shared_ptr<GameObject>& gameObject) { return gameObject->GetLifeTime() <= 0; }),
			GameStatics::spawnedBullets.end());

		GameStatics::particleSystemsToManage.erase(
			std::remove_if(
				GameStatics::particleSystemsToManage.begin(),
				GameStatics::particleSystemsToManage.end(),
				[](const std::shared_ptr<ParticleSystem>& particleSys) { return particleSys->bIsSysActive == false; }),
			GameStatics::particleSystemsToManage.end());

		manageGOMutex.unlock();

		std::this_thread::sleep_for(100ms);
	}
}

void TheGame::ManageStars(float deltaTime)
{
	BeginBlendMode(BLEND_ALPHA);

	for (auto& star : stars)
	{
		if (star.alpha <= 0.1f)
		{
			star.alphaMulti = -1;
		}
		else if (star.alpha >= 0.9f)
		{
			star.alphaMulti = 1;
		}

		star.alpha = star.alpha - (deltaTime * star.alphaMulti * 0.25f);
		DrawPoly(star.position, 4, star.scale.x, 90, ColorAlpha(star.color, star.alpha));
	}
	EndBlendMode();
}

void TheGame::ManageEnemy()
{
	enemyActivationTimer -= deltaTime;
	if (enemyActivationTimer <= 0)
	{
		enemyActivationTimer = 2.0f;
		if (enemies[enemyActivationIndex]->GetLifeTime() <= 0)
		{
			ResetEnemy(enemies[enemyActivationIndex].get(), spaceShip->position);
		}
		enemyActivationIndex++;

		if (enemyActivationIndex > enemies.size() - 1)
		{
			enemyActivationIndex = 0;
		}
	}


	for (const auto& enemy : enemies)
	{
		if (enemy->GetLifeTime() > 0)
		{
			enemy->Draw();
			enemy->Update(deltaTime);
			enemy->SetLifeTime(enemy->GetLifeTime() - deltaTime);
		}
	}
}

void TheGame::ManageGameObjects(float deltaTime)
{
	std::lock_guard<std::mutex> lock(manageGOMutex);
	for (const auto& goInWorld : GameStatics::spawnedBullets)
	{
		goInWorld->Draw();
		goInWorld->Update(deltaTime);
	}

	for (const auto& particleInWorld : GameStatics::particleSystemsToManage)
	{
		if (particleInWorld->bIsSysActive)
		{
			particleInWorld->Update(deltaTime);
		}
	}
}

void TheGame::ManageGameUI()
{
	DrawText(("Score: " + std::to_string(global.playerScore)).c_str(), 0, 0, 50, ColorAlpha(BLACK, 0.5f));
	DrawFPS(GameStatics::screenWidth - 100, GameStatics::screenHeight - 50);

	float playerRetryIconScale = 30;
	for (size_t i = 0; i < global.playerLifes; i++)
	{
		float xPos = GameStatics::halfScreenWidth + playerRetryIconScale * 2 * i;
		xPos += 250;
		DrawPoly({ xPos, 50 }, 3, playerRetryIconScale, 180, ColorAlpha(GREEN, 0.5f));
	}

}

void TheGame::CollisionsCheck()
{
	// Enemy - bullet collision
	for (auto& bullet : GameStatics::spawnedBullets)
	{
		for (auto& enemy : enemies)
		{
			if (!bullet.get() || !enemy.get() || enemy->GetLifeTime() <= 0) continue;
			if (CheckCollisionCircles(bullet->position, bullet->scale.x, enemy->position, enemy->scale.x))
			{				
				bullet->SetLifeTime(0);
				enemy->OnReceiveHit();

				ResetEnemy(enemy.get(), spaceShip->position);
			}
		}
	}

	// Enemy - Spaceship collision
	for (auto& enemy : enemies)
	{
		if (!enemy.get() || enemy->GetLifeTime() <= 0) continue;
		if (CheckCollisionCircles(spaceShip->position, spaceShip->scale.x, enemy->position, enemy->scale.x))
		{
			cout << "Spaceship received hit : " << enemy->position.x << " " << enemy->position.y << "\n";
			spaceShip->OnReceiveHit();
			ResetScene();
		}
	}
}

void TheGame::CollisionsCheckThread()
{
	using namespace std::literals::chrono_literals;
	while (true)
	{
		collisionCheckMutex.lock();
		// Enemy - bullet collision
		for (auto& bullet : GameStatics::spawnedBullets)
		{
			for (auto& enemy : enemies)
			{
				if (!bullet.get() || !enemy.get() || enemy->GetLifeTime() <= 0) continue;
				if (CheckCollisionCircles(bullet->position, bullet->scale.x, enemy->position, enemy->scale.x))
				{
					bullet->SetLifeTime(0);
					enemy->OnReceiveHit();

					ResetEnemy(enemy.get(), spaceShip->position);
				}
			}
		}

		// Enemy - Spaceship collision
		for (auto& enemy : enemies)
		{
			if (!enemy.get() || enemy->GetLifeTime() <= 0) continue;
			if (CheckCollisionCircles(spaceShip->position, spaceShip->scale.x, enemy->position, enemy->scale.x))
			{
				cout << "Spaceship received hit : " << enemy->position.x << " " << enemy->position.y << "\n";
				spaceShip->OnReceiveHit();
				ResetScene();
			}
		}

		collisionCheckMutex.unlock();

		std::this_thread::sleep_for(1ms);
	}	
}

void TheGame::ResetEnemy(Enemy* enemy, Vector2& targetPos)
{
	if (!enemy) return;

	float rndScale = GameStatics::RandomFloat(10.0f, 50.0f);

	enemy->ReInitializeEnemy(GetRandomPositionOnScreenBoundaries(), {rndScale}, targetPos);

}

void TheGame::ResetScene()
{
	if (global.playerLifes == 0)
	{
		gameState = EGameState::EGS_GameOver;
	}

	for (auto& enemy : enemies)
	{
		enemy->SetLifeTime(0);
	}

	enemyActivationTimer = 2.0f;
	enemyActivationIndex = 0;

	bIsSceneResetNeeded = true;

	spaceShip->input = { 0,0 };
	spaceShip->velocity = { 0,0 };
}

void TheGame::ManageDelayedSceneReset(const Color& bgColor)
{
	BeginDrawing();
	ClearBackground(bgColor);
	DrawText(std::to_string((int)std::ceil(sceneResetDelay)).c_str(), GameStatics::halfScreenWidth - 25, GameStatics::halfScreenHeight - 25, 50, DARKGREEN);
	EndDrawing();

	sceneResetDelay -= deltaTime;

	if (sceneResetDelay <= 0.0f)
	{
		sceneResetDelay = 3.0f;
		bIsSceneResetNeeded = false;
	}
	ManageGameObjects(deltaTime);
}

Vector2 TheGame::GetRandomPositionOnScreenBoundaries()
{
	const EDirections rndDirection = static_cast<EDirections>(GetRandomValue(0, static_cast<int>(EDirections::D_MAX) - 1));

	Vector2 rndPos = { 0,0 };

	switch (rndDirection)
	{
	case TheGame::EDirections::ED_UP:
		{
			rndPos.x = GameStatics::RandomFloat(0, GameStatics::screenWidth);			
			break;
		}
	case TheGame::EDirections::ED_DOWN:
		{
			rndPos.x = GameStatics::RandomFloat(0, GameStatics::screenWidth);
			rndPos.y = GameStatics::screenHeight;
			break;
		}
	case TheGame::EDirections::ED_LEFT:
		{			
			rndPos.y = GameStatics::RandomFloat(0, GameStatics::screenHeight);
			break;
		}
	case TheGame::EDirections::ED_RIGHT:
		{
			rndPos.x = GameStatics::screenWidth;
			rndPos.y = GameStatics::RandomFloat(0, GameStatics::screenHeight);
			break;
		}
	}

	return rndPos;
}

void TheGame::RenderMenuScene()
{
	const Vector2 playBtnPos = { GameStatics::halfScreenWidth - 50, GameStatics::halfScreenHeight };
	const Rectangle playBtnCollRect = { playBtnPos.x - 45,playBtnPos.y - 15,200, 80 };

	Color playBtnColor = MAGENTA;

	if (CheckCollisionPointRec(GetMousePosition(), playBtnCollRect))
	{
		playBtnColor = GREEN;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			gameState = EGameState::EGS_Play;
		}
	}

	BeginDrawing();

	ClearBackground(bgColor);

	DrawText("The Game", GameStatics::halfScreenWidth - 190, GameStatics::halfScreenHeight - 150, 80, BLACK);

	DrawRectangleRoundedLines(playBtnCollRect, 1.0f, 0.0f, 2.0f, playBtnColor);

	DrawText("Play", playBtnPos.x,playBtnPos.y , 50, playBtnColor);

	EndDrawing();
}

void TheGame::RenderGameScene()
{
	ManageStars(deltaTime);

	if (bIsSceneResetNeeded)
	{
		ManageDelayedSceneReset(bgColor);
		return;
	}

	spaceShip->input = ManageKeyboardInput();
	spaceShip->Update(deltaTime);

	if (Vector2Length(GetMouseDelta()) != 0)
	{
		spaceShip->RotateShip(GetMousePosition());
	}


	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE))
	{
		spaceShip->SpawnBullet();
	}

	BeginDrawing();//-----------------------------------------

	ClearBackground(bgColor);

	spaceShip->Draw();

	DrawCircleV(spaceShip->GetMuzzlePosition(), 5, RED);

	ManageEnemy();

	BeginBlendMode(BLEND_ALPHA);//******************************************		

	ManageGameObjects(deltaTime);

	ManageGameUI();

	EndBlendMode(); //*****************************************************

	// Debug-- SpaceShip collision circle visualization
	DrawCircleLines(spaceShip->position.x, spaceShip->position.y, spaceShip->scale.x * 0.8f, GREEN);

	EndDrawing();//-----------------------------------------			

#if !USE_THREAD
	CollisionsCheck();
	ManageGameObjectsLifeTime();
#endif
}

void TheGame::RenderGameOverScene()
{
	BeginDrawing();

	ClearBackground(bgColor);

	DrawText("GAME OVER", GameStatics::halfScreenWidth - 240, GameStatics::halfScreenHeight - 100, 80, RED);

	DrawText("Score", GameStatics::halfScreenWidth - 70, GameStatics::halfScreenHeight, 50, GRAY);

	std::string scoreStr = std::to_string(global.playerScore);

	DrawText(std::to_string(global.playerScore).c_str(), GameStatics::halfScreenWidth - 10 * scoreStr.length(), GameStatics::halfScreenHeight + 50, 50, GRAY);

	EndDrawing();
}

TheGame::~TheGame()
{
	if (spaceShip)
	{
		delete spaceShip;
	}
}