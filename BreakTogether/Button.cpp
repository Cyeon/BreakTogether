#include "pch.h"
#include "Player.h"
#include "Ball.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Button.h"

#include "Image.h"
#include "KeyMgr.h"
#include "MouseMgr.h"
#include "Vec2.h"

Button::Button() {
	image_ = ResMgr::GetInst()->ImgLoad(L"Button", L"Image\\button.bmp");
}

void Button::Update()
{
	auto mouse = MouseMgr::GetInst()->GetMouse();
	const auto rect = GetRect();

	if (PtInRect(&rect, mouse.vPos.toPoint()))
	{
		const auto mouse = MouseMgr::GetInst()->GetMouse();

		if (mouse.bLButton)
		{
			// 마우스 눌렀을 때
			ChangeScene(SCENE_TYPE::START);
		}
		else
		{
			image_ = ResMgr::GetInst()->ImgLoad(L"ButtonHover", L"Image\\button_hover.bmp");
		}
	}
	else
	{
		image_ = ResMgr::GetInst()->ImgLoad(L"Button", L"Image\\button.bmp");
	}
}

void Button::Render(HDC _dc)
{
	image_->Render(_dc, GetPos(), Vec2(0, 0));
	Component_Render(_dc);
}

Button::~Button()
= default;
