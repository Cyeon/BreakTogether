#include "pch.h"
#include "Player.h"
#include "Ball.h"
#include "ResMgr.h"
#include "Collider.h"
#include "ImageObject.h"

#include "Image.h"
#include "KeyMgr.h"
#include "MouseMgr.h"
#include "Vec2.h"

ImageObject::ImageObject(wstring _name, wstring _path, Vec2 _scale)
{
	image_ = ResMgr::GetInst()->ImgLoad(_name, _path);
	image_->SetScale(_scale);
}

void ImageObject::Render(HDC _dc)
{
	image_->Render(_dc, GetPos(), Vec2(0, 0));
	Component_Render(_dc);
}

ImageObject::~ImageObject()
= default;

void ImageObject::Update()
{

}
