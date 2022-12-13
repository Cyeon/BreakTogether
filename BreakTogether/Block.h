#pragma once
#include "Object.h"
class Image;
class Block :
	public Object
{
private:
	int m_iHp;
	Image* m_pImage;

public:
	Block();
	~Block();

	void Update() override;
	void Render(HDC _dc) override;

	void SetHp(int _iDamage) { m_iHp -= _iDamage; }
	int GetHp() { return m_iHp; }

	CLONE(Block);

	void EnterCollision(Collider* _pOther) override;
};