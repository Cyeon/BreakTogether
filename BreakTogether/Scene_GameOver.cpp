#include "pch.h"
#include "Scene_GameOver.h"
#include "TimeMgr.h"

void Scene_GameOver::Enter()
{
	m_fPlayTime = TimeMgr::GetInst()->GetPlayTime();
	swprintf(myLiveTime, sizeof(TCHAR) * 255, L"생존 시간 : %.2f", m_fPlayTime);
	
}

void Scene_GameOver::Exit()
{
	DeleteAll();
}

void Scene_GameOver::Update()
{
	Scene::Update();
}

void Scene_GameOver::Render(HDC _dc)
{
	TextOut(_dc, 100, 100, myLiveTime, lstrlen(myLiveTime));
}

Scene_GameOver::Scene_GameOver() 
= default;

Scene_GameOver::~Scene_GameOver()
= default;