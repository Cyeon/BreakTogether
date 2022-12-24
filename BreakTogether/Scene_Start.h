#pragma once
#include "Scene.h"

class Scene_Start :
	public Scene
{
public:
	void Enter() override;
	void Exit() override;
	void Update() override;
	void Render(HDC _dc) override;
public:
	Scene_Start();
	~Scene_Start() override;
};
