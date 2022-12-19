#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "ResMgr.h"
Monster::Monster()
	: m_fSpeed(100.f)
	, m_vCenterPos(Vec2(0.f, 0.f))
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_iHp(5)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));

	m_pImage = ResMgr::GetInst()->ImgLoad(L"MonsterAni", L"Image\\monster.bmp");

	CreateAnimator();

	Vec2 vLT = Vec2(0.f, 0.f);
	Vec2 vSliceSize = Vec2(32.f, 32.f);
	Vec2 vStep = Vec2(32.f, 0.f);
	Vec2 vAniSize = Vec2(50.f, 50.f);
	GetAnimator()->CreateAnimation(L"monster_front", m_pImage, vLT, vSliceSize, vStep, 4, 0.2f, vAniSize, true);
	GetAnimator()->CreateAnimation(L"monster_damage", m_pImage, vLT, vSliceSize, vStep, 4, 0.2f, vAniSize, true);
}

Monster::~Monster()
{
}

void Monster::Update()
{
	if (isDamaged) {
		GetAnimator()->Play(L"monster_damage", false);
		isDamaged = false;
	}
	else
	{
		GetAnimator()->Play(L"monster_front", true);
	}
}

void Monster::EnterCollision(Collider* _pOther)
{
	Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"BALL")
	{
		m_iHp -= 1;
		isDamaged = true;
		if (m_iHp <= 0)
			DeleteObject(this);
	}
}
