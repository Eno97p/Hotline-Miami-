#include "stdafx.h"
#include "Go.h"
#include "PngMrg.h"
#include "CCameraMgr.h"
Go::Go():m_PngKey(nullptr)
{
	
}

Go::~Go()
{
}

void Go::Initialize()
{
	m_tInfo.fCX = 25;
	m_tInfo.fCY = 50;
	m_PngKey = L"Go";
	m_eRender = BACKGROUND;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0; //0 주면 아래방향 1주면 위방향
	m_tFrame.dwSpeed = 500;
	m_tFrame.dwTime = GetTickCount();
}

int Go::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	__super::Update_Rect_Pos();
	return OBJ_NOEVENT;
}

void Go::Late_Update()
{
	m_tFrame.iMotion = (int)m_fAngle;
	Move_Frame();
}

void Go::Render(HDC hDC)
{
	Graphics graphic(hDC);
	graphic.DrawImage(PngMrg::Get_Instance()->Get_Image(m_PngKey),
		(INT)(m_tRect.left), (INT)(m_tRect.top),
		(INT)(m_tFrame.iMotion * m_tInfo.fCX), (INT)(m_tFrame.iFrameStart * m_tInfo.fCY),
		(INT)m_tInfo.fCX, (INT)m_tInfo.fCY,
		UnitPixel);
}

void Go::Release()
{
}
