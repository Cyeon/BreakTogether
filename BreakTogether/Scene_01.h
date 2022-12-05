#pragma once
#include "Scene.h"

class Scene_01 :
	public Scene
{
private:
public:
	Scene_01();
	~Scene_01() override;
public:
	void Enter() override;
	void Exit() override;
	void Update() override;
};
