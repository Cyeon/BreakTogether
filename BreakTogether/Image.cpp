#include "pch.h"
#include "Image.h"
#include "Core.h"

Image::Image()
	: m_hdc(nullptr)
	, m_hBit(nullptr)
	, m_bitInfo{}
{
}

Image::~Image()
{
	DeleteDC(m_hdc);
	DeleteObject(m_hBit);
}

void Image::Load(const wstring& _strFilePath)
{
	m_hBit = static_cast<HBITMAP>(LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE));
	assert(m_hBit); // 예외처리

	// 비트맵과 연결할 DC
	m_hdc = CreateCompatibleDC(Core::GetInst()->GetMainDC());
	SelectObject(m_hdc, m_hBit);

	// 가로 세로 길이
	//	BITMAP tInfo = {};
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
	//tInfo.bmWidth;
	//tInfo.bmHeight;


	//if (nullptr == m_hBit)
	//{

	//}
}

void Image::SetScale(const Vec2& p)
{
	scale = p;
}

void Image::Render(const HDC hdc, const Vec2& pos, const Vec2& offset) const
{
	TransparentBlt(hdc, pos.x - offset.x, pos.y - offset.y, m_bitInfo.bmWidth, m_bitInfo.bmHeight,
		m_hdc, 0, 0, m_bitInfo.bmWidth * static_cast<int>(scale.x), m_bitInfo.bmHeight * static_cast<int>(scale.y), RGB(255, 0, 255));
}
