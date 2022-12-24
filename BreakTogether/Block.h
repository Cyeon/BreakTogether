#pragma once
#include "Object.h"
class Image;
class Block :
	public Object
{
private:
	int m_iHp;
	Image* m_pImage;
	Vec2 m_vCenterPos;
	bool isdead;
	int& objectCount;

public:
	Block(int& objectCount);
	~Block();

	void Update() override;
	void Render(HDC _dc) override;

	void SetDamage(int _iDamage) { m_iHp -= _iDamage; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
	int GetHp() { return m_iHp; }

	CLONE(Block);

	void EnterCollision(Collider* _pOther) override;
};