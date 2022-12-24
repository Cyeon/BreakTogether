#pragma once
#include "Object.h"
#include "Vec2.h"
class Image;
class Block :
	public Object
{
	int m_iHp;
	Image* m_pImage;
	Vec2 m_vCenterPos;
	bool isdead;
	int& objectCount;
	Vec2Int position;
	bool isExplosionNow = false;

public:
	Block(int& objectCount, Vec2 position);
	Block(int& objectCount, Vec2Int position);
	~Block();

	void Update() override;
	void Render(HDC _dc) override;

	void SetDamage(int _iDamage) { m_iHp -= _iDamage; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
	int GetHp() { return m_iHp; }

	CLONE(Block);

	void EnterCollision(Collider* _pOther) override;
	void DestroyBlock();
};