#pragma once
#include "Object.h"
#include "Player.h"

class Tray :
	public Object
{
private:
	Image* image_ = nullptr;

public:
	Player& player_;
	void Update() override;
	void Render(HDC _dc) override;
	Tray(Player& player);
	~Tray() override;
	CLONE(Tray);
};
