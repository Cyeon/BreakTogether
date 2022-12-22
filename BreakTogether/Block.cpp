#include "pch.h"
#include "Block.h"
#include "Collider.h"
#include"Image.h"
#include "PathMgr.h"
#include "ResMgr.h"

Block::Block() :m_iHp(1)
{
	isdead = false;
	m_pImage = ResMgr::GetInst()->ImgLoad(L"BasicBlockImg", L"Image\\BasicBlock.bmp");
	m_pImage->SetScale(Vec2(4.f, 4.f));
	CreateCollider();
	GetCollider()->SetScale(Vec2(64.f, 64.f));
}

Block::~Block()
{
}

void Block::Update()
{
}

void Block::Render(HDC _dc)
{
	m_pImage->Render(_dc, GetPos(), Vec2(0.f, 0.f));
	Component_Render(_dc);
}

void Block::EnterCollision(Collider* _pOther) {
	if (isdead) return;
	Object* pOtherObj = _pOther->GetObj();
	wstring wStr = pOtherObj->GetName();
	if (wStr == L"BALL") {
		SetDamage(1);
		if (m_iHp <= 0) {
			isdead = true;
			DeleteObject(this);
		}
	}
}