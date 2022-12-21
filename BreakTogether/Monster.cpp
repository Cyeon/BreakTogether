#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "ResMgr.h"
#include "Bullet.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "KeyMgr.h"

Monster::Monster()
	: m_fSpeed(100.f)
	, m_vCenterPos(Vec2(0.f, 0.f))
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_iHp(5)
	, isDamaged(false)
	, delay(1.5f)
	, lastTime(0.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(60.f, 60.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, 35.f));

	m_pImage = ResMgr::GetInst()->ImgLoad(L"MonsterAni", L"Image\\monster.bmp");

	CreateAnimator();
	Vec2 vLT = Vec2(0.f, 0.f);
	Vec2 vSliceSize = Vec2(32.f, 32.f);
	Vec2 vStep = Vec2(32.f, 0.f);
	Vec2 vAniSize = Vec2(100.f, 100.f);
	GetAnimator()->CreateAnimation(L"monster_front", m_pImage, vLT, vSliceSize, vStep, 4, 0.2f, vAniSize, true);
	vLT = Vec2(0.f, 33.f);
	GetAnimator()->CreateAnimation(L"monster_damage", m_pImage, vLT, vSliceSize, vStep, 4, 0.2f, vAniSize, true);

	Vec2 offsetPos = Vec2(-35.f, 0.f);

	Animation* pAnim = GetAnimator()->FindAnimation(L"monster_front");
	for (size_t i = 0; i < pAnim->GetMaxFrame(); i++)
		pAnim->GetFrame(i).vOffset = offsetPos;
	pAnim = GetAnimator()->FindAnimation(L"monster_damage");
	for (size_t i = 0; i < pAnim->GetMaxFrame(); i++)
		pAnim->GetFrame(i).vOffset = offsetPos;
}

Monster::~Monster()
{
}

void Monster::Update()
{
	if (lastTime + delay <= TimeMgr::GetInst()->GetPlayTime()) {
		lastTime = TimeMgr::GetInst()->GetPlayTime();
		CreateBullet();
	}
}

void Monster::Render(HDC _dc)
{
	if (isDamaged) {
		GetAnimator()->Play(L"monster_damage", true);
		//isDamaged = false;
		return;
	}
	GetAnimator()->Play(L"monster_front", true);
	GetAnimator()->Update();
	Component_Render(_dc);
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

void Monster::CreateBullet()
{
	Vec2 vBulletPos = GetPos();
	vBulletPos.y += GetScale().y / 2.f;
	Bullet* pBullet = new Bullet;
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	pBullet->SetDir(Vec2(0.f, 10.f));
	Scene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pBullet, GROUP_TYPE::BULLET_MONSTER);
}