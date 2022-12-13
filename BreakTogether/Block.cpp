#include "pch.h"
#include "Block.h"
#include "Collider.h"
#include"Image.h"
#include "PathMgr.h"
#include "ResMgr.h"

Block::Block() :m_iHp(1)
{
	m_pImage = ResMgr::GetInst()->ImgLoad(L"BasicBlockImg", L"Image\\BasicBlock.bmp");
	//m_pImage->SetScale(Vec2(3.f, 3.f));
	//CreateCollider();
	//GetCollider()->SetScale(Vec2(150.f, 100.f));
}

Block::~Block()
{
}

void Block::Update()
{
}

void Block::Render(HDC _dc)
{
	//int width = static_cast<int>(m_pImage->)
	// 
	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();

	//int Width = static_cast<int>(m_pImage->GetWidth());
	//int Height = static_cast<int>(m_pImage->GetHeight());

	//TransparentBlt(_dc
	//	, static_cast<int>(vPos.x - (float)(Width / 2))
	//	, static_cast<int>(vPos.y - (float)(Height / 2))
	//	, Width, Height
	//	, m_pImage->GetDC()
	//	, 0, 0, Width, Height
	//	, RGB(255, 0, 255));

	Component_Render(_dc);
}

void Block::EnterCollision(Collider* _pOther) {
	Object* pOtherObj = _pOther->GetObj();
	wstring wStr = pOtherObj->GetName();
	if (wStr.find(L"Player_Bullet_") != wstring::npos || wStr.find(L"Bullet_Player") != wstring::npos) {
		m_iHp -= 1;
		if (m_iHp <= 0) {
			DeleteObject(this);
		}
	}
}