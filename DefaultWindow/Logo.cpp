#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PngMrg.h"
#include "CCameraMgr.h"
#include "SoundMgr.h"
CLogo::CLogo() : m_fVolume(1.f)
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo.bmp", L"Logo");*/
	/*PngMrg::Get_Instance()->Insert_Png(L"../Image/Logo.png", L"Logo");*/
	// MCIWndCreate : 멀티 미디어를 재생하기 위한 윈도우 생성 함수

	//m_hVideo = MCIWndCreate(g_hWnd,	// 부모 핸들
	//						nullptr,	// mci 윈도우의 인스턴스 핸들
	//						WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // WS_CHILD(자식 창), WS_VISIBLE(그 즉시 시연), MCIWNDF_NOPLAYBAR(플레이바 생성하지 않음)
	//						L"../Video/Wildlife.wmv");	// 재생할 파일의 경로
	//
	//// MoveWindow : 동영상 파일을 재생할 크기를 설정
	//MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	//MCIWndPlay(m_hVideo);
	/*CSoundMgr::Get_Instance()->PlayBGM(L"Daisuke.ogg", m_fVolume);*/

}

void CLogo::Update()
{
	if(GetAsyncKeyState(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}
}

void CLogo::Late_Update()
{
}

void CLogo::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Logo");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	//Graphics	graphic(hDC);
	//graphic.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Logo"),
	//	0, 0, 1600, 900);
	
}

void CLogo::Release()
{
	//MCIWndClose(m_hVideo);
}
