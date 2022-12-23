#include "pch.h"
#include "Scene_Title.h"

#include "Button.h"
#include "Core.h"
#include "ImageObject.h"
#include "KeyMgr.h"
#include "Object.h"
#include "SoundMgr.h"

Scene_Title::Scene_Title()
= default;

Scene_Title::~Scene_Title()
= default;

void Scene_Title::Enter()
{
	SoundMgr::GetInst()->LoadSound(L"BGM", true, L"Sound\\pianobgm.wav");
	SoundMgr::GetInst()->Play(L"BGM");

	{ // 시작 버튼
		Object* obj = new Button;
		obj->SetName(L"Start");
		obj->SetPos(Vec2(Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y / 2 + 300));
		obj->SetScale(Vec2(100.f, 100.f));
		AddObject(obj, GROUP_TYPE::UI);
	}

	{ // 타이틀 로고 
		Object* obj = new ImageObject(L"TitleLogo", L"Image\\Title.bmp", Vec2(1.5f, 1.5f));
		obj->SetName(L"Background");
		obj->SetPos(Vec2(Core::GetInst()->GetResolution().x / 2.f, Core::GetInst()->GetResolution().y / 2.5f));
		obj->SetScale(Vec2(100.f, 100.f));
		AddObject(obj, GROUP_TYPE::UI);
	}
}

void Scene_Title::Exit()
{
}

void Scene_Title::Update()
{
	Scene::Update();
}
