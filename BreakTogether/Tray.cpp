#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Tray.h"

#include "Image.h"
#include "Vec2.h"

Tray::Tray(Player& player) : player_(player) {
	CreateCollider();
	GetCollider()->SetScale(Vec2(200.f, 10.f));

	image_ = ResMgr::GetInst()->ImgLoad(L"Tray", L"Image\\tray.bmp");
	image_->SetScale(Vec2(4.f, 4.f));
}

void Tray::Update()
{
	Vec2 playerPos = player_.GetPos();
	playerPos.y -= 35.f;
	SetPos(playerPos);
}

void Tray::Render(HDC _dc)
{
	image_->Render(_dc, GetPos(), Vec2(90.f, 0.f));
	Component_Render(_dc);
}

Tray::~Tray()
= default;
