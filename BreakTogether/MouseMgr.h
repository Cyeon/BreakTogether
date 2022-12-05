#pragma once
#include "pch.h"
#include "define.h"

struct MouseInfo
{
	Vec2 vPos;
};

class MouseMgr
{
public:
	SINGLE(MouseMgr);
private:
	MouseMgr();
	~MouseMgr();
private:
	const LPPOINT lp_point = new POINT;
	MouseInfo mouse_info_;

public:
	MouseInfo& GetMouse();
	void Update();
	void Init();
};
