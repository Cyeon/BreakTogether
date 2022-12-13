#pragma once
#include "Object.h"

class Image;

class Player :
	public Object
{
private:
	Image* m_pImage{};
public:
	Player();
	~Player() override;
private:
	void CreateBall();
	Image* tray_image{};
	CLONE(Player);
public:
	void Update() override;
	void Render(HDC _dc) override;
};
