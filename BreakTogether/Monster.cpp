#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Collider.h"

Monster::Monster()
	: m_fSpeed(100.f)
	  , m_vCenterPos(Vec2(0.f, 0.f))
	  , m_fMaxDistance(50.f)
	  , m_iDir(1)
	  , m_iHp(5)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

Monster::~Monster()
{
}

void Monster::Update()
{
	
}

void Monster::EnterCollision(Collider* _pOther)
{
	Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"BALL")
	{
		m_iHp -= 1;
		if (m_iHp <= 0)
			DeleteObject(this);
	}
}
