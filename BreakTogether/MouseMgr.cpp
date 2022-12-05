#include "MouseMgr.h"

#include "BWindow.h"

MouseMgr::MouseMgr()
{
}

MouseMgr::~MouseMgr()
{
}

MouseInfo& MouseMgr::GetMouse()
{
	return mouse_info_;
}

void MouseMgr::Update()
{
	GetCursorPos(lp_point);

	const HWND h_wnd = GetFocus();

	if (ScreenToClient(h_wnd, lp_point))
	{
		mouse_info_.vPos.x = lp_point->x;
		mouse_info_.vPos.y = lp_point->y;
	}
}

void MouseMgr::Init()
{
	mouse_info_ = {};
}
