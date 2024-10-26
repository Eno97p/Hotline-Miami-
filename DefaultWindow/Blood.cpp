#include "stdafx.h"
#include "Blood.h"
#include "BmpMgr.h"
#include "CCameraMgr.h"
void CBlood::Initialize()
{
	m_tInfo.fCX = 15;
	m_tInfo.fCY = 15;
	m_eRender = UI;
	m_pFrameKey = L"Blood";
}

int CBlood::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	__super::Update_Rect();
	__super::Update_Rect_Pos();
	return OBJ_NOEVENT;
}

void CBlood::Late_Update()
{

}

void CBlood::Render(HDC hDC)
{
	
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left ,
		m_tRect.top ,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0, //소스 그림의 시작 좌표
		0,			//소스 그림의 시작 좌표
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(238, 243, 250));
}

void CBlood::Release()
{
}
