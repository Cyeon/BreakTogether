#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Tray.h"
#include "Vec2.h"

Tray::Tray(Player& player) : player_(player) {
	CreateCollider();
	GetCollider()->SetScale(Vec2(60.f, 75.f));

	Image* p_img = ResMgr::GetInst()->ImgLoad(L"PlayerAni", L"Image\\tray.bmp");
	
}

void Tray::Update()
{
	SetPos(player_.GetPos());
}

Tray::~Tray()
= default;
