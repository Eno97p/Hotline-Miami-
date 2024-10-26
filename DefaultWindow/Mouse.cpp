#include "stdafx.h"
#include "Mouse.h"
#include "CCameraMgr.h"
#include <string>
CMouse::CMouse()
{
	
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_eRender = UI;
}

int CMouse::Update()
{
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);


	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
	/*ShowCursor(FALSE);*/
}

void CMouse::Render(HDC hDC)
{
	/*float halfwidth = (m_tInfo.fY - (m_tInfo.fCY / 2)) - (m_tInfo.fY + (m_tInfo.fCY / 2)) * 0.5f;
	float halflength = ((m_tInfo.fX + (m_tInfo.fCX / 2)) - (m_tInfo.fX - (m_tInfo.fCX / 2))) * 0.5f;*/
	float halfwidth = (m_tRect.bottom - m_tRect.top) / 2.f;
	float halflength = (m_tRect.right - m_tRect.left) / 2.f;
	

	MoveToEx(hDC, m_tRect.left,
		m_tRect.bottom - halfwidth,
		NULL);
	LineTo(hDC, m_tRect.right, m_tRect.bottom - halfwidth);
	MoveToEx(hDC, m_tRect.right - halflength, m_tRect.top, NULL);
	LineTo(hDC, m_tRect.right - halflength, m_tRect.bottom);


	/*wstring MouseX = to_wstring(m_tInfo.fX);
	wstring MouseY = to_wstring(m_tInfo.fY);
	wstring CameraX = to_wstring((int)(m_tInfo.fX + CCameraMgr::Get_Instance()->m_fDiffX));
	wstring CameraY = to_wstring((int)(m_tInfo.fY + CCameraMgr::Get_Instance()->m_fDiffY));
	

	TextOut(hDC, 10, 10, MouseX.c_str(), MouseX.length());
	TextOut(hDC, 110, 10, MouseY.c_str(), MouseY.length());
	TextOut(hDC, 500, 10, CameraX.c_str(), CameraX.length());
	TextOut(hDC, 600, 10, CameraY.c_str(), CameraY.length());*/
	


}

void CMouse::Release()
{
}
