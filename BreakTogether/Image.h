#pragma once
#include "Res.h"

class Image :
	public Res
{
private:
	HDC m_hdc;
	HBITMAP m_hBit;
	BITMAP m_bitInfo;
private:
	Image();
	~Image() override;
	Vec2 scale = { 1.f, 1.f };
	friend class ResMgr;
public:
	void Load(const wstring& _strFilePath);
	void Render(HDC hdc, const Vec2& pos, const Vec2& offset) const;
	UINT GetWidth() { return m_bitInfo.bmWidth; }
	UINT GetHeight() { return m_bitInfo.bmHeight; }
	HDC GetDC() { return m_hdc; }
	void SetScale(const Vec2& p);
};
