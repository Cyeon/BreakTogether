#pragma once
#include <string>

#include "Image.h"
#include "pch.h">
#include "Object.h"
#include "Vec2.h"

class Button : public Object
{
private:
	Image* image_ = nullptr;
	wstring m_wButtonPath;
	wstring m_wButtonHoverPath;
	wstring m_wButtonName;
	wstring m_wButtonHoverName;

public:
	void Update() override;
	void Render(HDC _dc) override;
	RECT GetRect() {
		Vec2 pos = GetPos();
		Vec2 scale = Vec2(static_cast<int>(image_->GetWidth()), static_cast<int>(image_->GetHeight()));

		RECT rect = {
			static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(pos.x) + static_cast<int>(scale.x),
			static_cast<int>(pos.y) + static_cast<int>(scale.y)
		};

		rect.left -= static_cast<int>(scale.x) / 2;
		rect.right -= static_cast<int>(scale.x) / 2;
		rect.top -= static_cast<int>(scale.y) / 2;
		rect.bottom -= static_cast<int>(scale.y) / 2;

		return rect;

	}
	Button();
	Button(wstring buttonName, wstring buttonHName,wstring buttonPath, wstring buttonHoverPath);
	~Button() override;
	CLONE(Button);
};

