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

Button::Button() :m_wButtonPath(L"Image\\button.bmp"), m_wButtonHoverPath(L"Image\\button_hover.bmp"), m_wButtonName(L"StartButton"), m_wButtonHoverName(L"ButtonHover")
{
	image_ = ResMgr::GetInst()->ImgLoad(m_wButtonName, m_wButtonPath);
}

Button::Button(wstring buttonName, wstring buttonHName, wstring buttonPath, wstring buttonHoverPath)
	: m_wButtonPath(buttonPath), m_wButtonHoverPath(buttonHoverPath), m_wButtonName(buttonName), m_wButtonHoverName(buttonHName)
{
	image_ = ResMgr::GetInst()->ImgLoad(buttonName, buttonPath);
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
			image_ = ResMgr::GetInst()->ImgLoad(m_wButtonHoverName, m_wButtonHoverPath);
		}
	}
	else
	{
		image_ = ResMgr::GetInst()->ImgLoad(m_wButtonName, m_wButtonPath);
	}
}

void Button::Render(HDC _dc)
{
	image_->Render(_dc, GetPos(), Vec2(0, 0));
	Component_Render(_dc);
}

Button::~Button()
= default;
