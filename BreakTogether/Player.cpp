#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Ball.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Image.h"
#include "MouseMgr.h"
#include "SkillMgr.h"
#include "ItemMgr.h"

Player::Player() :m_fSpeed(500.f), m_iHp(3), m_bDamageAble(true)
{
	// collider ����
	CreateCollider();
	GetCollider()->SetScale(Vec2(60.f, 75.f));

	// image ���ε�
	Image* p_img = ResMgr::GetInst()->ImgLoad(L"PlayerAni", L"Image\\character.bmp");
	m_pHpImage = ResMgr::GetInst()->ImgLoad(L"HpImg", L"Image\\Heart.bmp");
	// animator ���� �� animation ���
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"character_front", p_img, Vec2(0.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 4, 0.2f, Vec2(192.f, 192.f));
	GetAnimator()->CreateAnimation(L"character_back", p_img, Vec2(0.f, 48.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 4, 0.2f, Vec2(192.f, 192.f));
	GetAnimator()->CreateAnimation(L"character_left", p_img, Vec2(0.f, 96.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 4, 0.2f, Vec2(192.f, 192.f));
	GetAnimator()->CreateAnimation(L"character_right", p_img, Vec2(0.f, 144.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 4, 0.2f, Vec2(192.f, 192.f));

	GetAnimator()->Play(L"character_front", true);

	Vec2 offsetPos = Vec2(-72.5f, -72.5f);

	// animation offset ���� �ø���. 
	Animation* pAnim = GetAnimator()->FindAnimation(L"character_front");
	for (size_t i = 0; i < pAnim->GetMaxFrame(); i++)
		pAnim->GetFrame(i).vOffset = offsetPos;
	pAnim = GetAnimator()->FindAnimation(L"character_back");
	for (size_t i = 0; i < pAnim->GetMaxFrame(); i++)
		pAnim->GetFrame(i).vOffset = offsetPos;
	pAnim = GetAnimator()->FindAnimation(L"character_left");
	for (size_t i = 0; i < pAnim->GetMaxFrame(); i++)
		pAnim->GetFrame(i).vOffset = offsetPos;
	pAnim = GetAnimator()->FindAnimation(L"character_right");
	for (size_t i = 0; i < pAnim->GetMaxFrame(); i++)
		pAnim->GetFrame(i).vOffset = offsetPos;

	SkillMgr::GetInst()->OnSkill1.emplace_back([&]
		{
			CreateBall();
		});

	SkillMgr::GetInst()->OnSkill2.emplace_back([&]
		{
			runTime = 5; // 달리기 시간
		});
}

Player::~Player()
= default;

void Player::Update()
{
	Vec2 vPos = GetPos();
	const Vec2 vMousePos = MouseMgr::GetInst()->GetMouse().vPos;

	if (abs(vPos.x - vMousePos.x) > 5.f)
	{
		float tempSpeed = m_fSpeed * fDT;
		if (runTime > 0)
		{
			tempSpeed *= 1.3f;
		}
		if (vPos.x < vMousePos.x)
		{
			vPos.x += tempSpeed;
			GetAnimator()->Play(L"character_right", true);
		}
		else
		{
			vPos.x -= tempSpeed;
			GetAnimator()->Play(L"character_left", true);
		}
	}
	else
	{
		GetAnimator()->Play(L"character_front", true);
	}

	SetPos(vPos);
	GetAnimator()->Update();

	runTime -= fDT;
}

void Player::CreateBall()
{
	Vec2 vBallPos = GetPos();
	vBallPos.y -= GetScale().y / 2.f + 10.f;

	{ // Ball
		Ball* pBall = new Ball();
		pBall->SetName(L"BALL");
		pBall->SetPos(vBallPos);
		pBall->SetScale(Vec2(25.f, 25.f));
		pBall->SetDir(Vec2(rand() % 2 ? 1.f : -1.f, -1.f));
		CreateObject(pBall, GROUP_TYPE::BALL);
	}
}

void Player::Render(HDC _dc)
{
	int Width = (int)m_pHpImage->GetWidth();
	int Height = (int)m_pHpImage->GetHeight();
	for (int i = 0; i < m_iHp; i++)
	{
		TransparentBlt(_dc
			, (int)(0.f+i*(64.f))
			, (int)(800.f)
			, 64.f, 64.f
			, m_pHpImage->GetDC()
			, 0, 0, Width, Height,
			RGB(255, 0, 255));
	}
	Component_Render(_dc);
}

void Player::EnterCollision(Collider * _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Bullet") {
		if (!m_bDamageAble) { return; }
		m_iHp--;
		if (m_iHp <= 0) {
			ChangeScene(SCENE_TYPE::OVER);
		}
	}
}