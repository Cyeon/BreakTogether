#include "pch.h"
#include "Scene_GameOver.h"
#include "TimeMgr.h"
#include "ScoreMgr.h"

void Scene_GameOver::Enter()
{
	ScoreMgr::GetInst()->PushNewScore(ScoreMgr::GetInst()->GetCurrentScore());
	m_vScores = ScoreMgr::GetInst()->GetHighScores();

	m_fPlayTime = TimeMgr::GetInst()->GetPlayTime();
	swprintf(myLiveTime, sizeof(TCHAR) * 255, L"생존 시간 : %.2f", m_fPlayTime);
	wsprintf((LPWSTR)myScore.c_str(), L"점수 : %d", ScoreMgr::GetInst()->GetCurrentScore());
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
	TextOut(_dc, 100, 200, myScore.c_str(), lstrlen(myScore.c_str()));

	TextOut(_dc, 150, 300, L"HIGH SCORES", lstrlen(L"HIGH SCORES"));

	for (int i = 0; i < m_vScores.size(); i++)
	{
		wsprintf((LPWSTR)otherScore.c_str(), L"RANK %d : %d", i + 1, m_vScores[i]);
		TextOut(_dc, 100, 300 + (i + 1) * 30, otherScore.c_str(), lstrlen(otherScore.c_str()));
	}
}

Scene_GameOver::Scene_GameOver()
= default;

Scene_GameOver::~Scene_GameOver()
= default;