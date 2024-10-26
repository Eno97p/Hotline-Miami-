#include "stdafx.h"
#include "MyEdit.h"
#include "Define.h"
#include "KeyMgr.h"
#include "TileMgr.h"
#include "WallMgr.h"
#include "CCameraMgr.h"
#include "BmpMgr.h"
#include <string>
#include "Mouse.h"
#include "VWallMgr.h"
#include "CornerMgr.h"
CMyEdit::CMyEdit() : Walltype_Switch(0), m_tilmode(false)
{
	m_xInput = 0;
	m_yInput = 0;
}

CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize(void)
{
	m_fSpeed = 5.f;
	CTileMgr::Get_Instance()->Initialize();
	mssss = new CMouse;
	mssss->Initialize();
	WallMgr::Get_Instance()->Initialize();
	VWallMgr::Get_Instance()->Initialize();
	CornerMgr::Get_Instance()->Initialize();
	CCameraMgr::Get_Instance()->m_PosX = 800;
	CCameraMgr::Get_Instance()->m_PosY = 600;
}

void CMyEdit::Update()
{
	Key_Input();
	mssss->Update();
	CCameraMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	WallMgr::Get_Instance()->Update();
	VWallMgr::Get_Instance()->Update();
	CornerMgr::Get_Instance()->Update();
}

void CMyEdit::Late_Update()
{
	CTileMgr::Get_Instance()->Late_Update();
	WallMgr::Get_Instance()->Late_Update();
	VWallMgr::Get_Instance()->Late_Update();
	CornerMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{

	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Ground");
	int DiffX = CCameraMgr::Get_Instance()->m_fDiffX;
	int DiffY = CCameraMgr::Get_Instance()->m_fDiffY;

	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
	CTileMgr::Get_Instance()->Render(hDC);
	WallMgr::Get_Instance()->Render(hDC);
	VWallMgr::Get_Instance()->Render(hDC);
	CornerMgr::Get_Instance()->Render(hDC);
	mssss->Render(hDC);
	POINT	ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	wstring MouseX = to_wstring(ptMouse.x + DiffX);
	wstring MouseY = to_wstring(ptMouse.y+ DiffY);
	wstring CameraX = to_wstring(CCameraMgr::Get_Instance()->m_PosX);
	wstring CameraY = to_wstring(CCameraMgr::Get_Instance()->m_PosY);
	wstring Walltype = to_wstring(Walltype_Switch);

	TextOut(hDC, 10, 10, MouseX.c_str(), MouseX.length());
	TextOut(hDC, 110, 10, MouseY.c_str(), MouseY.length());
	TextOut(hDC, 210, 10, CameraX.c_str(), CameraX.length());
	TextOut(hDC, 310, 10, CameraY.c_str(), CameraY.length());
	TextOut(hDC, 100, 550, Walltype.c_str(), Walltype.length());

	if (!m_tilmode)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Tile");
		BitBlt(hDC,
			700,
			100,
			TILECX, TILECY, hMemDC, TILECX * m_xInput, TILECY * m_yInput, SRCCOPY);
	}
	else
	{
		HDC		wallDC = CBmpMgr::Get_Instance()->Find_Img(L"Corner");
		BitBlt(hDC,
			700,
			100,
			8, 8, wallDC, 8 * m_xInput, 8 * m_yInput, SRCCOPY);
	}

}

void CMyEdit::Release()
{
	CTileMgr::Destroy_Instance();
	WallMgr::Destroy_Instance();
	VWallMgr::Destroy_Instance();
	CornerMgr::Destroy_Instance();
	delete mssss;
	mssss = nullptr;
}

void CMyEdit::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		CCameraMgr::Get_Instance()->m_PosY -= m_fSpeed;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		CCameraMgr::Get_Instance()->m_PosY += m_fSpeed;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		CCameraMgr::Get_Instance()->m_PosX -= m_fSpeed;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		CCameraMgr::Get_Instance()->m_PosX += m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Up('H'))
	{
		if (m_tilmode)
		{
			m_tilmode = false;
		}
		else
		{
			m_tilmode = true;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Up('O'))
	{
		++m_xInput;
	}
	if (CKeyMgr::Get_Instance()->Key_Up('I'))
	{
		++m_yInput;
	}
	if (CKeyMgr::Get_Instance()->Key_Up('L'))
	{
		--m_xInput;
	}
	if (CKeyMgr::Get_Instance()->Key_Up('K'))
	{
		--m_yInput;
	}
	if (CKeyMgr::Get_Instance()->Key_Up('M'))
	{
		++Walltype_Switch;
		if (Walltype_Switch > 2)
		{
			Walltype_Switch = 0;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
	{
		POINT	ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);
		/*WallMgr::Get_Instance()->Picking(ptMouse.x+ CCameraMgr::Get_Instance()->m_fDiffX, ptMouse.y+ CCameraMgr::Get_Instance()->m_fDiffY, 0, 0);*/
		if (!m_tilmode)
		{
			CTileMgr::Get_Instance()->Picking(ptMouse.x + CCameraMgr::Get_Instance()->m_fDiffX,
				ptMouse.y + CCameraMgr::Get_Instance()->m_fDiffY,
				m_xInput, m_yInput); // 타일피킹
		}
		else
		{
			switch (Walltype_Switch)
			{
			case 0:
				WallMgr::Get_Instance()->Picking(ptMouse.x + CCameraMgr::Get_Instance()->m_fDiffX, ptMouse.y + CCameraMgr::Get_Instance()->m_fDiffY, 0, 0);
				break;
			case 1:
				VWallMgr::Get_Instance()->Picking(ptMouse.x + CCameraMgr::Get_Instance()->m_fDiffX, ptMouse.y + CCameraMgr::Get_Instance()->m_fDiffY, 0, 0);
				break;
			case 2:
				CornerMgr::Get_Instance()->Picking(ptMouse.x + CCameraMgr::Get_Instance()->m_fDiffX, ptMouse.y + CCameraMgr::Get_Instance()->m_fDiffY, m_xInput, m_yInput);
				break;
			}
		}
	}

	/*if (GetAsyncKeyState('S'))
	{
		CTileMgr::Get_Instance()->Save_Data5();
		WallMgr::Get_Instance()->Save_H5();
		VWallMgr::Get_Instance()->Save_V5();
		CornerMgr::Get_Instance()->Save_C5();
		return;
	}*/
	if (GetAsyncKeyState('A'))
	{
		CTileMgr::Get_Instance()->Load_Data5();
		WallMgr::Get_Instance()->Load_H5();
		VWallMgr::Get_Instance()->Load_V5();
		CornerMgr::Get_Instance()->Load_C5();
		return;
	}
}

