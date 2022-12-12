#include "pch.h"
#include "Block.h"
#include "Collider.h"

Block::Block() :m_vPos(Vec2(0.f, 0.f)), m_vScale(Vec2(100.f, 100.f)), m_iHp(1)
{
	CreateCollider();
	GetCollider()->SetScale(m_vScale);
}

Block::~Block()
{
}

void Block::EnterCollision(Collider* _pOther) {
	Object* pOtherObj = _pOther->GetObj();
	wstring wStr = pOtherObj->GetName();
	if (wStr.find(L"Player_Bullet_") != wstring::npos) {
		if (m_iHp <= 0) {
			DeleteObject(this);
		}
	}
}