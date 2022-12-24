#pragma once
#include "Scene.h"

class Scene_Start :
	public Scene
{
public:
	void GenerateMap();
	void Enter() override;
	void Exit() override;
	void Update() override;
public:
	Scene_Start();
	~Scene_Start() override;
	int objectCount = 0;
};
