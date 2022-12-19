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
	
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		mouse_info_.bLButton = true;
	}
	else
	{
		mouse_info_.bLButton = false;
	}

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		mouse_info_.bRButton = true;
	}
	else
	{
		mouse_info_.bRButton = false;
	}
}

void MouseMgr::Init()
{
	mouse_info_ = {};
}
