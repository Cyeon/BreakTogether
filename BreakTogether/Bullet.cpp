#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
#include "Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"

Bullet::Bullet()
	: m_vDir(Vec2(1.f, 1.f))
{
	m_pImage = ResMgr::GetInst()->ImgLoad(L"BulletImg", L"Image\\Bullet.bmp");
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
}

Bullet::~Bullet()
{
}


void Bullet::Update()
{
	Vec2 vPos = GetPos();
	vPos.x += 700.f * m_vDir.x * fDT;
	vPos.y += 700.f * m_vDir.y * fDT;
	SetPos(vPos);
}

void Bullet::Render(HDC _dc)
{
	int Width = static_cast<int>(m_pImage->GetWidth());
	int Height = static_cast<int>(m_pImage->GetHeight());

	Vec2 vPos = GetPos();
	TransparentBlt(_dc
		, static_cast<int>(vPos.x - (float)(Width / 2))
		, static_cast<int>(vPos.y - (float)(Height / 2))
		, Width, Height
		, m_pImage->GetDC()
		, 0, 0, Width, Height
		, RGB(255, 0, 255));
	Component_Render(_dc);
}

void Bullet::EnterCollision(Collider* _pOther)
{
	Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}
