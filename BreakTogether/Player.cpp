#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Image.h"
#include "MouseMgr.h"

Player::Player()
{
	// collider 새성
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 30.f));

	// image 업로드
	Image* p_img = ResMgr::GetInst()->ImgLoad(L"PlayerAni", L"Image\\character.bmp");
	tray_image = ResMgr::GetInst()->ImgLoad(L"PlayerTray", L"Image\\tray.bmp");

	// animator 생성 및 animation 사용
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"character_front", p_img, Vec2(0.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 4,
		0.2f);
	GetAnimator()->CreateAnimation(L"character_back", p_img, Vec2(0.f, 48.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 4,
		0.2f);
	GetAnimator()->CreateAnimation(L"character_left", p_img, Vec2(0.f, 96.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 4,
		0.2f);
	GetAnimator()->CreateAnimation(L"character_right", p_img, Vec2(0.f, 144.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 4,
		0.2f);

	GetAnimator()->Play(L"character_front", true);

	// animation offset 위로 올리기. 
	Animation* p_anim = GetAnimator()->FindAnimation(L"character_front");
	for (size_t i = 0; i < p_anim->GetMaxFrame(); i++)
		p_anim->GetFrame(i).vOffset = Vec2(0.f, 0.f);
}

Player::~Player()
= default;

void Player::Update()
{
	Vec2 vPos = GetPos();
	const Vec2 vMousePos = MouseMgr::GetInst()->GetMouse().vPos;

	if (abs(vPos.x - vMousePos.x) > 1.f)
	{
		if (vPos.x < vMousePos.x)
		{
			vPos.x += 300.f * fDT;
			GetAnimator()->Play(L"character_right", true);
		}
		else
		{
			vPos.x -= 300.f * fDT;
			GetAnimator()->Play(L"character_left", true);
		}
	}
	else
	{
		GetAnimator()->Play(L"character_front", true);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateBullet();
	}

	SetPos(vPos);
	GetAnimator()->Update();
}

void Player::CreateBullet()
{
	Vec2 vBulletPos = GetPos();
	vBulletPos.y -= GetScale().y / 2.f;

	// 
	auto pBullet = new Bullet;
	pBullet->SetName(L"Bullet_Player");
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vec2(25.f, 25.f));
	pBullet->SetDir(Vec2(0.f, -1.f));
	CreateObject(pBullet, GROUP_TYPE::BULLET_PLAYER);
	//Scene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	//pCurScene->AddObject(pBullet,GROUP_TYPE::BULLET);
}

void Player::Render(HDC _dc)
{
	Component_Render(_dc);
	// void Image::Render(const HDC hdc, const Vec2 & pos, const Vec2 & offset) const
	tray_image->Render(_dc, GetPos(), Vec2(tray_image->GetWidth() / 2, 48 / 4));
}
