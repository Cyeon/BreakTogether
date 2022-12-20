#include "pch.h"
#include "Scene_Start.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "Tray.h"
#include "Block.h"
#include "BlockMgr.h"

Scene_Start::Scene_Start()
= default;

Scene_Start::~Scene_Start()
= default;

void Scene_Start::Enter()
{
	SoundMgr::GetInst()->LoadSound(L"BGM", true, L"Sound\\pianobgm.wav");
	SoundMgr::GetInst()->Play(L"BGM");

	Player* player;

	{ // Player
		player = new Player;
		Object* obj = player;
		obj->SetPos(Vec2(Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y - 50));
		obj->SetScale(Vec2(100.f, 100.f));
		AddObject(obj, GROUP_TYPE::PLAYER);
	}

	{ // Tray
		Object* obj = new Tray(*player);
		obj->SetName(L"Tray");
		obj->SetPos(Vec2(Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y - 50));
		obj->SetScale(Vec2(100.f, 100.f));
		AddObject(obj, GROUP_TYPE::TRAY);
	}
	
	{ //Block
		Vec2 vResolution(Vec2(Core::GetInst()->GetResolution()));
		int iBlock = 16;
		float fMoveDist = 25.f;
		float fObjScale = 64.f;
		float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / static_cast<float>(iBlock - 1);

		Block* obj = nullptr;

		for (int i = 0; i < iBlock; i++)
		{
			obj = new Block();
			obj->SetName(L"Block");
			obj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + static_cast<float>(i) * fTerm, 300.f));
			obj->SetCenterPos(obj->GetPos());
			obj->SetScale(Vec2(150.f, 100.f));
			AddObject(obj, GROUP_TYPE::MONSTER);
		}
	}
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BULLET_MONSTER);
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::BALL);
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BALL, GROUP_TYPE::TRAY);
}

void Scene_Start::Exit()
{
	DeleteAll();
	CollisionMgr::GetInst()->CheckReset();
}

void Scene_Start::Update()
{
	Scene::Update();
	/*if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::SCENE_01);
	}*/
}
