#pragma once
#include "Object.h"
class Block :
	public Object
{
private:
	Vec2 m_vScale;
	Vec2 m_vPos;
	int m_iHp;

public:
	Block();
	~Block();
	void SetHp(int _iDamage) { m_iHp -= _iDamage; }
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }

	int GetHp() { return m_iHp; }
	Vec2 GetPos() { return m_vPos; }

	void EnterCollision(Collider* _pOther) override;
};