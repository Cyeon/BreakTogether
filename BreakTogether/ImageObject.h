#pragma once
#include <string>

#include "Image.h"
#include "pch.h">
#include "Object.h"
#include "Vec2.h"

class ImageObject : public Object
{
private:
	Image* image_ = nullptr;
	bool initialized = false;

public:
	ImageObject(wstring _name, wstring _path, Vec2 _scale);
	~ImageObject() override;

	void Update() override;
	void Render(HDC _dc) override;
	CLONE(ImageObject);
};

