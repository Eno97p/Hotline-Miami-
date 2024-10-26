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
	// MCIWndCreate : ��Ƽ �̵� ����ϱ� ���� ������ ���� �Լ�

	//m_hVideo = MCIWndCreate(g_hWnd,	// �θ� �ڵ�
	//						nullptr,	// mci �������� �ν��Ͻ� �ڵ�
	//						WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // WS_CHILD(�ڽ� â), WS_VISIBLE(�� ��� �ÿ�), MCIWNDF_NOPLAYBAR(�÷��̹� �������� ����)
	//						L"../Video/Wildlife.wmv");	// ����� ������ ���
	//
	//// MoveWindow : ������ ������ ����� ũ�⸦ ����
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
