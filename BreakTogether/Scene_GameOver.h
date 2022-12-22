#pragma once
#include "Scene.h"
class Scene_GameOver :
	public Scene
{
private:
	float m_fPlayTime;
	TCHAR myLiveTime[255];
	wstring myScore;
	wstring otherScore;
	vector<int> m_vScores;
public:
	void Enter() override;
	void Exit() override;
	void Update() override;

	void Render(HDC _dc) override;

	Scene_GameOver();
	~Scene_GameOver() override;

};