#pragma once
#include "Object.h"
#include "Player.h"

class Tray :
	public Object
{
public:
	Player& player_;
	void Update() override;

	Tray(Player& player);
	~Tray() override;
};
