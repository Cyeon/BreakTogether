#pragma once
#include "Object.h"
class Image;
class Monster :
	public Object
{
private:
	Image* m_pImage;
	float m_fSpeed;
	Vec2 m_vCenterPos;
	float m_fMaxDistance;
	int m_iDir; // 1, -1
	int m_iHp;
	bool isDamaged;
	float atkDelay;
	float lastAtkTime;
	float aniDelayTime;
public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _f) { m_fSpeed = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
	void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
	void SetDelay();
public:
	void Update() override;
	void Render(HDC _dc) override;
	void EnterCollision(Collider* _pOther) override;
	//    Monster* Clone() { return new Monster(*this); }

	void CreateBullet();

	CLONE(Monster);
public:
	Monster();
	~Monster() override;
};
