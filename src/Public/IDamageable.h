#pragma once

class IDamageable
{
public:
	void virtual OnReceiveHit() = 0;
};