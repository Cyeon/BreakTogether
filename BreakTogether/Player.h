#pragma once
#include "Object.h"

class Image;

class Player :
	public Object
{
private:
	Image* m_pImage{};
	float m_fSpeed;
	int m_iHp;
public:
	Player();
	~Player() override;
private:
	void CreateBall();
	Image* tray_image{};
	CLONE(Player);
	float runTime = 0;
public:
	void Update() override;
	void Render(HDC _dc) override;
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void EnterCollision(Collider* _pOther) override;
};
