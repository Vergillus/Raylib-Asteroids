#pragma once

class Global
{
public:
	int playerScore = 0;
	int playerLifes = 3;

private:
	Global() = default;
	Global(const Global&) = delete;
	Global(Global&&) = delete;

public:
	static Global& Instance()
	{
		static Global global;
		return global;
	}
};

namespace {
	Global& global = Global::Instance();
}
// static Global& global = Global::Instance(); if you like
