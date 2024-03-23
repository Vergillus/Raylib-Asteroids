// Raylib-Game01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Public/TheGame.h"

struct Player
{
	Vector2 position;
	float speed;
	float playerWH;
	bool bCanJump;
};

struct EnvItem
{
	Rectangle rect;
	int blocking;
	Color color;
};


//void UpdatePositions(Vector2* positins, int size, const Vector2& inputDir, const float speed);
//
//void GameDeneme(const int& screenWidth, const int& screenHeight, const float& halfScreenWidth, const float& halfScreenHeight);
//void GameDeneme2(const int& screenWidth, const int& screenHeight, const float& halfScreenWidth, const float& halfScreenHeight);
//void TrigLookAt(Vector2* positionArr, int size, const Vector2& lookAtDir, const float angle, const Vector2& origin);
//
//void UpdatePlayer(Player* player, const vector<EnvItem>& envItems, float delta, const float gravity, const float playerJumpSpeed, const float playerMovementSpeed);
//

int main()
{
	TheGame game;
	game.Run();


	//GameDeneme(screenWidth, screenHeight, halfScreenWidth, halfScreenHeight);
	//GameDeneme2(screenWidth, screenHeight, halfScreenWidth, halfScreenHeight);
}


//void GameDeneme(const int& screenWidth, const int& screenHeight, const float& halfScreenWidth, const float& halfScreenHeight)
//{
//	float trigRadius = 50.0f;
//
//	Vector2 trianglePoints[] =
//	{
//		Vector2{ screenWidth / 2.0f + trigRadius, screenHeight / 2.0f + trigRadius }, // bottom left point
//		Vector2{ screenWidth / 2.0f, screenHeight / 2.0f - trigRadius }, // center top point
//		Vector2{ screenWidth / 2.0f - trigRadius, screenHeight / 2.0f + trigRadius }, // bottom righ point
//	};
//
//	Vector2 trigOrigin{ halfScreenWidth, halfScreenHeight };
//	Vector2 trigForward{ 0,1 };
//
//	float playerRecWH = 100.0f;
//	Rectangle playerRec = { 400,200,playerRecWH, playerRecWH };
//
//	Camera2D camera = { 0 };
//	camera.target = { playerRec.x + 20.0f, playerRec.y + 20.0f };
//	camera.offset = { halfScreenWidth, halfScreenHeight };
//	camera.rotation = 0.0f;
//	camera.zoom = 1.0f;
//
//	float rotation = 0.0f;
//	Vector2 origin{ playerRecWH / 2.0f, playerRecWH / 2.0f };
//
//	Vector2 ballPos{ halfScreenWidth, halfScreenHeight };
//	Vector2 ballVelocity = Vector2Zero();
//
//	/* Vector2 p1{ screenWidth / 2.0f - 10.0f, screenHeight / 2.0f - 10.0f };
//	Vector2 p2{ screenWidth / 2.0f + 10.0f, screenHeight / 2.0f - 10.0f };
//	Vector2 p3{ screenWidth / 2.0f, screenHeight / 2.0f + 10.0f };*/
//
//	Vector2 inputDir;
//	Vector2 mousePos, mousePosPrev = GetMousePosition();
//
//	while (!WindowShouldClose())
//	{
//		inputDir = Vector2{ 0,0 };
//
//		if (IsKeyDown(KEY_RIGHT))
//		{
//			inputDir.x = 1.0;
//		}
//		if (IsKeyDown(KEY_LEFT))
//		{
//			inputDir.x = -1.0;
//		}
//
//		if (IsKeyDown(KEY_UP))
//		{
//			inputDir.y = -1.0;
//		}
//		if (IsKeyDown(KEY_DOWN))
//		{
//			inputDir.y = 1.0;
//		}
//
//		if (inputDir.x != 0 || inputDir.y != 0)
//		{
//			//UpdatePositions(trianglePoints, 3, inputDir, 2.0f);
//			playerRec.x += inputDir.x * 2.0f;
//			playerRec.y += inputDir.y * 2.0f;
//		}
//
//		camera.target = { playerRec.x , playerRec.y };
//
//		if (IsKeyDown(KEY_A)) camera.rotation--;
//		else if (IsKeyDown(KEY_S)) camera.rotation++;
//
//		if (camera.rotation > 40) camera.rotation = 40;
//		else if (camera.rotation < -40) camera.rotation = -40;
//
//		if (IsKeyPressed(KEY_R))
//		{
//			camera.zoom = 1;
//			camera.rotation = 0.0f;
//		}
//
//		BeginDrawing();
//
//		ClearBackground(DARKBLUE);
//
//		BeginMode2D(camera);
//		mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
//		DrawRectangle(screenWidth / 2, 320, 400, 8000, MAGENTA);
//
//
//		Vector2 mouseDelta = GetMouseDelta();
//
//		Vector2 playerWorldOrigin{ playerRec.x, playerRec.y };
//
//		DrawLineV(playerWorldOrigin, mousePos, BLACK);
//
//		Vector2 lookAtDir = Vector2Normalize(Vector2Subtract(mousePos, playerWorldOrigin));
//		float angle = atan2f(lookAtDir.y, lookAtDir.x) * RAD2DEG;
//
//		DrawRectanglePro(playerRec, origin, angle + 180, RED);
//
//		DrawLine((int)camera.target.x, -screenHeight * 10, (int)camera.target.x, screenHeight * 10, GREEN);
//		DrawLine(-screenWidth * 10, (int)camera.target.y, screenWidth * 10, (int)camera.target.y, GREEN);
//
//		DrawPoly(camera.target, 3, 80, (89 - angle), ORANGE);
//
//
//		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
//		{
//			float ballSpeed = 500;
//			ballPos = camera.target;
//			ballVelocity = Vector2{ lookAtDir.x * ballSpeed * GetFrameTime(), lookAtDir.y * ballSpeed * GetFrameTime() };
//		}
//
//		ballPos.x += ballVelocity.x;
//		ballPos.y += ballVelocity.y;
//
//		DrawCircleV(ballPos, 30, BLACK);
//
//
//		EndMode2D();
//
//		//float yPosOffset = sinf(GetTime() * 2.0f) * 100;       
//
//		//DrawText("HELL YEAH!!!!", 0, 0, 20, BLACK);
//
//		//DrawTriangleStrip(trianglePoints, 3, DARKBLUE);
//
//
//		//Vector2 lookAtDir = Vector2Normalize(Vector2Subtract(mousePos,trigOrigin));
//		//float angle = Vector2Angle(lookAtDir, trigForward);
//		//Vector2 rotatedVec = Vector2Rotate(lookAtDir, angle);
//		////std::cout << angle << " " << rotatedVec.x << " " << rotatedVec.y << "\n";
//		//trigForward = rotatedVec;        
//		//DrawLineV(trigOrigin, mousePos, BLACK);
//
//		//if (!Vector2Equals(mousePos, mousePosPrev))
//		//{
//		//   // TrigLookAt(trianglePoints, 3, rotatedVec, angle, trigOrigin);
//		//}
//
//		//mousePosPrev = mousePos;
//
//		EndDrawing();
//	}
//
//	CloseWindow();
//}
//
//void GameDeneme2(const int& screenWidth, const int& screenHeight, const float& halfScreenWidth, const float& halfScreenHeight)
//{
//
//	constexpr float gravity = 600;
//	constexpr float playerJumpSpeed = 350.0f;
//	constexpr float playerSpeed = 200.0f;
//
//	Player player =
//	{
//		{400,280},
//		0,
//		40,
//		false
//	};
//
//	vector<EnvItem> envItems =
//	{
//		{{0, 0, 1000, 400},0,LIGHTGRAY},
//		{{0, 400, 1000, 200},1,GRAY},
//		{{300, 200, 400, 10},1,GRAY},
//		{{250, 300, 100, 10},1,GRAY},
//		{{650, 300, 100, 10},1,GRAY},
//	};
//
//	Camera2D camera;
//	camera.target = player.position;
//	camera.offset = Vector2{ halfScreenWidth, halfScreenHeight };
//	camera.rotation = 0.0f;
//	camera.zoom = 1.0f;
//
//	Vector2 up{ 0,-1 };
//
//	float rotation = 0.0f;
//
//	while (!WindowShouldClose())
//	{
//		float deltaTime = GetFrameTime();
//
//		UpdatePlayer(&player, envItems, deltaTime, gravity, playerJumpSpeed, playerSpeed);
//
//		BeginDrawing();
//
//		BeginMode2D(camera);
//
//		for (size_t i = 0; i < envItems.size(); i++)
//		{
//			DrawRectangleRec(envItems[i].rect, envItems[i].color);
//		}
//
//		Rectangle playerRect{ player.position.x - 20, player.position.y - 40, player.playerWH,player.playerWH };
//		DrawRectanglePro(playerRect,Vector2{ player.playerWH / 2.0f ,player.playerWH / 2.0f},rotation, RED);
//
//		Vector2 dir = Vector2Normalize(Vector2Subtract(GetMousePosition(), player.position));
//
//		float angle =  Vector2LineAngle(dir, up) * RAD2DEG;		
//		
//
//		Vector3 a = Vector3{ dir.x,dir.y,0 };
//		Vector3 b = Vector3{ up.x,up.y,0 };
//
//		Vector3 c = Vector3CrossProduct(a, b);
//
//		cout << c.x << " " << c.y  << " "  << c.z << "\n";
//
//		float angleMulti = 0;
//		if (c.z > 0) angleMulti = 1;
//		else if (c.z < 0) angleMulti = -1;
//
//
//		rotation -= angle * angleMulti;		
//		
//		DrawText(std::to_string(angle).c_str(), 0, 0, 20, BLACK);
//
//		Vector2 newUp = Vector2Rotate(up, angle * angleMulti);
//
//		DrawLineV(player.position, Vector2Add(player.position , Vector2Scale(up, 100)), BLUE);
//
//		up = dir;
//
//		EndMode2D();
//
//		EndDrawing();
//	}
//
//	CloseWindow();
//
//}
//
//void UpdatePlayer(Player* player, const vector<EnvItem>& envItems, float delta, const float gravity, const float playerJumpSpeed, const float playerMovementSpeed)
//{
//	if (IsKeyDown(KEY_LEFT)) player->position.x -= playerMovementSpeed * delta;
//	if (IsKeyDown(KEY_RIGHT)) player->position.x += playerMovementSpeed * delta;
//	if (IsKeyDown(KEY_SPACE) && player->bCanJump)
//	{
//		player->speed = -playerJumpSpeed;
//		player->bCanJump = false;
//	}
//
//	bool bHitObstacle = false;
//	for (const EnvItem& env : envItems)
//	{
//		if (env.blocking && env.rect.x  <= player->position.x + player->playerWH * 0.4f &&
//			env.rect.x + env.rect.width >= player->position.x - player->playerWH * 0.4f &&
//			env.rect.y >= player->position.y &&
//			env.rect.y <= player->position.y + player->speed * delta)
//		{
//			bHitObstacle = true;
//			player->speed = 0.0f;
//			player->position.y = env.rect.y;
//		}
//	}
//
//	if (!bHitObstacle)
//	{
//		float gravityMulti = 1.0f;
//		if (player->speed >= 0) gravityMulti *= 3.0f;
//
//		player->position.y += player->speed * delta;
//		player->speed += gravity * gravityMulti * delta;		
//		//player->bCanJump = false;
//	}
//	else
//	{
//		player->bCanJump = true;
//	}
//
//}
//
//void UpdatePositions(Vector2* positionArr, int size, const Vector2& inputDir, const float speed)
//{
//	for (size_t i = 0; i < size; i++)
//	{
//		positionArr[i].x += inputDir.x * speed;
//		positionArr[i].y += inputDir.y * speed;
//	}
//}
//
//void TrigLookAt(Vector2* positionArr, int size, const Vector2& lookAtDir, const float angle, const Vector2& origin)
//{
//	for (size_t i = 0; i < size; i++)
//	{
//
//		Vector2 diff = (Vector2Subtract(positionArr[i], origin));
//		float ang = Vector2Angle(diff, lookAtDir);
//
//		diff = Vector2Rotate(diff, angle);
//		positionArr[i] = diff;
//
//	}
//}