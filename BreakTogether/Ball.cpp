#include "pch.h"
#include "Ball.h"
#include "TimeMgr.h"
#include "Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Core.h"

Ball::Ball()
	: m_vDir(Vec2(1.f, 1.f)), m_vSize(Vec2(0, 0))
{
	m_pImage = ResMgr::GetInst()->ImgLoad(L"BallImg", L"Image\\ball.bmp");
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
	m_vSize.x = static_cast<int>(m_pImage->GetWidth());
	m_vSize.y = static_cast<int>(m_pImage->GetHeight());
}

Ball::~Ball()
= default;

void Ball::Bounce(BounceDir bounce_dir)
{
	if (m_bounce) return;
	m_bounce = true;
	switch (bounce_dir)
	{
	case Ball::BounceDir::X:
		m_vDir.x *= -1.f;
		break;
	case Ball::BounceDir::Y:
		m_vDir.y *= -1.f;
		break;
	default:
		break;
	}
}


void Ball::Update()
{
	m_bounce = false;
	Vec2 vPos = GetPos();

	if (vPos.x < 0 || vPos.x > Core::GetInst()->GetResolution().x)
	{
		Bounce(BounceDir::X);
	}

	if (vPos.y < 0)
	{
		Bounce(BounceDir::Y);
	}
	else if (vPos.y > Core::GetInst()->GetResolution().y)
	{
		DeleteObject(this);
	}

	const auto normalized_dir = m_vDir.Normalize();

	vPos.x += 700.f * normalized_dir.x * fDT;
	vPos.y += 700.f * normalized_dir.y * fDT;

	SetPos(vPos);

}

void Ball::Render(HDC _dc)
{
	const int Width = m_vSize.x;
	const int Height = m_vSize.y;

	const Vec2 vPos = GetPos();
	TransparentBlt(_dc
		, static_cast<int>(vPos.x - (float)(static_cast<int>(m_pImage->GetWidth()) / 2))
		, static_cast<int>(vPos.y - (float)(static_cast<int>(m_pImage->GetHeight()) / 2))
		, Width, Height
		, m_pImage->GetDC()
		, 0, 0, (static_cast<int>(m_pImage->GetWidth())), static_cast<int>(m_pImage->GetHeight())
		, RGB(255, 0, 255));
	Component_Render(_dc);
}

void Ball::EnterCollision(Collider * _pOther)
{
	Object* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Tray")
	{
		Bounce(BounceDir::Y);
		m_vDir.x = (GetPos().x - pOtherObj->GetPos().x) / 100.f;
		return;
	}

	const Vec2 vPos = GetCollider()->GetFinalPos();
	const Vec2 vOtherPos = pOtherObj->GetPos();

	const float x_diff = vPos.x - vOtherPos.x;
	const float y_diff = vPos.y - vOtherPos.y;

	if (abs(x_diff) > abs(y_diff))
		Bounce(BounceDir::X);
	else
		Bounce(BounceDir::Y);
}
