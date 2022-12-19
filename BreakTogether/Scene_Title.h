#pragma once
#include "Scene.h"

class Scene_Title :
	public Scene
{
private:
public:
	Scene_Title();
	~Scene_Title() override;
public:
	void Enter() override;
	void Exit() override;
	void Update() override;
};
