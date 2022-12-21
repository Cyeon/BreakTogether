#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
#include "Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
Bullet::Bullet()
	: m_fTheta(M_PI / 4.f)
	, m_vDir(Vec2(1.f, 1.f))
	, m_pImage(nullptr)

{
	m_pImage = ResMgr::GetInst()->ImgLoad(L"BulletImg", L"Image\\bullet.bmp");
	CreateCollider();
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Vec2 vPos = GetPos();
	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;

	SetPos(vPos);
}

void Bullet::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	int Width = (int)m_pImage->GetWidth();
	int Height = (int)m_pImage->GetHeight();

	TransparentBlt(_dc
		, (int)(vPos.x - (float)(Width / 2))
		, (int)(vPos.y - (float)(Height / 2))
		, Width, Height
		, m_pImage->GetDC()
		, 0, 0, Width, Height,
		RGB(255, 0, 255));
	Component_Render(_dc);
}