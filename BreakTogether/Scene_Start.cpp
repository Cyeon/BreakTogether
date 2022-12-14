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
#include "SkillMgr.h"
#include "TimeMgr.h"
#include "ItemMgr.h"
#include "ScoreMgr.h"

Scene_Start::Scene_Start()
= default;

Scene_Start::~Scene_Start()
= default;

void Scene_Start::GenerateMap()
{
	ScoreMgr::GetInst()->ScoreUp(1000);

	{
		// ���� ��ġ
		Vec2 vResolution(Vec2(Core::GetInst()->GetResolution()));
		int iMonster = 16;
		float fMoveDist = 25.f;
		float fObjScale = 50.f;
		float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / static_cast<float>(iMonster - 1);
		Monster* pMonsterObj = nullptr;
		for (int i = 0; i < iMonster; i++)
		{
			pMonsterObj = new Monster(objectCount);
			pMonsterObj->SetName(L"Monster");
			pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + static_cast<float>(i) * fTerm, 50.f));
			pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
			pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
			pMonsterObj->SetMoveDistance(fMoveDist);
			AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
		}
	}
	{
		//Block
		Vec2 vResolution(Vec2(Core::GetInst()->GetResolution()));
		int iBlock = 30;
		int iLine = 5;
		float fMoveDist = 25.f;
		float fObjScale = 64.f;
		float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / static_cast<float>(iBlock - 1);

		Vec2Int pos = { 0, 0 };
		for (int i = 0; i < iLine; i++)
		{
			for (int j = 0; j < iBlock; j++)
			{
				const auto obj = new Block(objectCount, pos);
				obj->SetName(L"Block");
				obj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + static_cast<float>(j) * fTerm,
				                 200.f + static_cast<float>(i) * fObjScale));
				obj->SetCenterPos(obj->GetPos());
				obj->SetScale(Vec2(150.f, 100.f));
				AddObject(obj, GROUP_TYPE::MONSTER);
				pos.x++;
			}
			pos.x = 0;
			pos.y++;
		}
	}
}

void Scene_Start::Enter()
{
	SoundMgr::GetInst()->LoadSound(L"BGM", true, L"Sound\\pianobgm.wav");
	SoundMgr::GetInst()->Play(L"BGM");

	TimeMgr::GetInst()->ResetPlayTime();
	ItemMgr::GetInst()->ResetItem();

	Player* player;

	{
		// Player
		player = new Player;
		Object* obj = player;
		obj->SetPos(Vec2(Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y - 50));
		obj->SetScale(Vec2(100.f, 100.f));
		AddObject(obj, GROUP_TYPE::PLAYER);
	}

	{
		// Tray
		Object* obj = new Tray(*player);
		obj->SetName(L"Tray");
		obj->SetPos(Vec2(Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y - 50));
		obj->SetScale(Vec2(100.f, 100.f));
		AddObject(obj, GROUP_TYPE::TRAY);
	}

	GenerateMap();
	ScoreMgr::GetInst()->ScoreUp(-1000);
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BULLET_MONSTER);
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::BALL);
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BALL, GROUP_TYPE::TRAY);
}

void Scene_Start::Exit()
{
	DeleteAll();
	CollisionMgr::GetInst()->CheckReset();
	SkillMgr::GetInst()->Clear();
}

void Scene_Start::Update()
{
	Scene::Update();
	SkillMgr::GetInst()->Update(fDT);

	ItemMgr::GetInst()->Update();
	if (objectCount <= 0)
	{
		GenerateMap();
	}

	if (KeyMgr::GetInst()->GetKey(KEY::Z) == KEY_STATE::HOLD)
	{
		SkillMgr::GetInst()->SkillBoom();
	}
	if (KeyMgr::GetInst()->GetKey(KEY::X) == KEY_STATE::HOLD)
	{
		SkillMgr::GetInst()->SkillSpawn();
	}
	if (KeyMgr::GetInst()->GetKey(KEY::C) == KEY_STATE::HOLD)
	{
		SkillMgr::GetInst()->SkillRun();
	}
}

void Scene_Start::Render(HDC _dc)
{
	Scene::Render(_dc);
	ItemMgr::GetInst()->Render(_dc);
	SkillMgr::GetInst()->Render(_dc);
	ScoreMgr::GetInst()->Render(_dc);
}