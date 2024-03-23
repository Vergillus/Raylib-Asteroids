#pragma once
#include <chrono>
#include <iostream>

struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	const char* debugTxt;

	Timer(const char* txt)
	{
		start = std::chrono::high_resolution_clock::now();

		debugTxt = txt;
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000.0f;

		int index = 0;
		while (debugTxt[index] != '\0')
		{
			std::cout << debugTxt[index++];
		}

		std::cout << " DEBUG::Timer took " << ms << "\n";

		debugTxt = nullptr;
	}
};