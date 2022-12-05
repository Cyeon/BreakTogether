#include "pch.h"
#include "SelectGDI.h"
#include "Core.h"

SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePenType)
	: m_hDC(_dc)
	  , m_hDefaultPen(nullptr)
	  , m_hDefaultBrush(nullptr)
{
	HPEN hColorPen = Core::GetInst()->GetPen(_ePenType);
	m_hDefaultPen = static_cast<HPEN>(SelectObject(_dc, hColorPen));
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType)
	: m_hDC(_dc)
	  , m_hDefaultPen(nullptr)
	  , m_hDefaultBrush(nullptr)
{
	HBRUSH hColorBrush = Core::GetInst()->GetBrush(_eBrushType);
	m_hDefaultBrush = static_cast<HBRUSH>(SelectObject(_dc, hColorBrush));
}

SelectGDI::~SelectGDI()
{
	SelectObject(m_hDC, m_hDefaultPen);
	SelectObject(m_hDC, m_hDefaultBrush);
}
