#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Monster.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"
#include "SoundMgr.h"
#include "PngMrg.h"
#include "WallMgr.h"
#include "VWallMgr.h"
#include "CornerMgr.h"
#include "CCameraMgr.h"
#include "ScorMgr.h"
CMainGame::CMainGame() 
	: m_iFPS(0), m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);
	CCameraMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo.bmp", L"Logo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BlackBack.bmp", L"Blackback");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ScoreBack.bmp", L"ScoreBoard");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/White.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood.bmp", L"Blood");

	PngMrg::Get_Instance()->Insert_Png(L"../Image/Weapon.png", L"Weapon");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Jacket_ps.png", L"PlayerForm");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/JacketDead.png", L"PlayerDead");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Mafia.png", L"Mafia");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Mafia_Hit.png", L"Mafia_Hit");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Boss.png", L"Boss");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Weapon_Intersect.png", L"Weapon_Intersect");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/stageclear.png", L"Stage_Clear");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Go.png", L"Go");

	PngMrg::Get_Instance()->Insert_Png(L"../Image/PlayerLeg.png", L"PlayerLeg");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/MafiaLeg.png", L"MafiaLeg");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/BossLeg.png", L"BossLeg");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/img/wallH.bmp", L"WallH");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/img/wallV.bmp", L"WallV");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/img/corner.bmp", L"Corner");

	PngMrg::Get_Instance()->Insert_Png(L"../Image/Effects1.png", L"Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/img/TileTotalEXt.bmp", L"Tile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/img/sprBasicTiel.bmp", L"Block");

	PngMrg::Get_Instance()->Insert_Png(L"../Image/TextBoxFull.png", L"TextBox"); 
	PngMrg::Get_Instance()->Insert_Png(L"../Image/NewTextBox.png", L"TextBoxBoss");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Fat_face.png", L"BossFace");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Boss_Dead.png", L"BossDead");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Tutorial.png", L"Tutorial");

	PngMrg::Get_Instance()->Insert_Png(L"../Image/ExplosionFull.png", L"Explosion");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Bomb.png", L"Bomb");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/BombTrace.png", L"BombTrace");

	PngMrg::Get_Instance()->Insert_Png(L"../Image/BloodPool.png", L"BloodPool");

	
	CSoundMgr::Get_Instance()->Initialize();
	ScorMgr::Get_Instance()->Initialize();
//#ifdef _DEBUG
//
//	if (::AllocConsole() == TRUE)
//	{
//		FILE* nfp[3];
//		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
//		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
//		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
//		std::ios::sync_with_stdio();
//	}
//
//#endif 
}

void CMainGame::Update(void)
{
	CCameraMgr::Get_Instance()->Update();
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
#pragma region 프레임 출력

	/*++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}*/

#pragma endregion 프레임 출력

	if (SC_LOGO == CSceneMgr::Get_Instance()->Get_SceneID())
		return;

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	
	CSceneMgr::Get_Instance()->Render(hMemDC);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	// 윈도우 문자열 출력 함수

	//TCHAR	szBuff[32] = L"";

	//wsprintf(szBuff, L"Bullet : %d", m_ObjList[BULLET].size()); 

	//swprintf_s(szBuff, L"Bullet : %f", 3.14f);
	
	// wsprintf : winapi 라이브러리에서 제공하는 함수
	// swprintf_s : visual c++ 라이브러리에서 제공하는 함수, 모든 서식 문자를 지원

	//TextOut(m_DC, 50, 50, szBuff, lstrlen(szBuff));

	//RECT	rc{ 100, 100, 200, 200 };
	//DrawText(m_DC, szBuff, lstrlen(szBuff), &rc, DT_CENTER);

}

void CMainGame::Release(void)
{
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG

	CSoundMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	PngMrg::Destroy_Instance();
	WallMgr::Destroy_Instance();
	VWallMgr::Destroy_Instance();
	CornerMgr::Destroy_Instance();
	CCameraMgr::Destroy_Instance();
	ScorMgr::Destroy_Instance();
	ReleaseDC(g_hWnd, m_DC);
}
