#include "stdafx.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "SoundMgr.h"
#include "PngMrg.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "MyMenu.h"
CMyMenu::CMyMenu() : m_fVolume(0.f), LogoTnum(0), LogoTic(0.f)
{
}


CMyMenu::~CMyMenu()
{
	Release();

}

void CMyMenu::Initialize()
{
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");

	//CObj*	pObj = CAbstractFactory<CMyButton>::Create(200.f, 400.f, 0.f);
	//pObj->Set_FrameKey(L"Start");
	//CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	//pObj = CAbstractFactory<CMyButton>::Create(400.f, 400.f, 0.f);
	//pObj->Set_FrameKey(L"Edit");
	//CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	//pObj = CAbstractFactory<CMyButton>::Create(600.f, 400.f, 0.f);
	//pObj->Set_FrameKey(L"Exit");
	//CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Logo_Text2.png", L"LogoTxt");


	m_fVolume = 1.f;
	CSoundMgr::Get_Instance()->PlayBGM(L"Daisuke.ogg", m_fVolume);

	LogoTic = GetTickCount();
}

void CMyMenu::Update()
{

	if (CKeyMgr::Get_Instance()->Key_Down('0'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_TUTO);
		return;
	}

}

void CMyMenu::Late_Update()
{

	if (LogoTic + 700 < GetTickCount())
	{
		if (LogoTnum == 0)
		{
			LogoTnum = 1;
		}
		else
		{
			LogoTnum = 0;
		}
		LogoTic = GetTickCount();
	}
}

void CMyMenu::Render(HDC hDC)
{

	/*HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Menu");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);*/


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Logo");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	Graphics Grab(hDC);
	Grab.DrawImage(PngMrg::Get_Instance()->Get_Image(L"LogoTxt"),
		200, 300,
		0, 100 * LogoTnum,
		400, 100,
		UnitPixel);
	/*CObjMgr::Get_Instance()->Render(hDC);*/



}

void CMyMenu::Release()
{
	/*CObjMgr::Get_Instance()->Delete_ID(BUTTON);*/
	CSoundMgr::Get_Instance()->StopAll();
}
