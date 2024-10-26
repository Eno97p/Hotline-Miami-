#include "stdafx.h"
#include "Tutorial.h"
#include "ObjMgr.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "Mouse.h"
#include "SoundMgr.h"
#include "PngMrg.h"
#include "Wall.h"
#include "WallMgr.h"
#include "VWallMgr.h"
#include "CornerMgr.h"
#include "CCameraMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "Go.h"
#include "PlayerUI.h"
#include "ScorMgr.h"

Tutorial::Tutorial() : m_fVol(0.5f), m_fPhoneCalltime(0.f) , isPhonecall(true), ImageNum(0), CloseEvent(true)
{
	ZeroMemory(&m_rPhone, sizeof(RECT));
	ZeroMemory(&m_rGate, sizeof(RECT));
}

Tutorial::~Tutorial()
{
	Release();
	CSoundMgr::Get_Instance()->PlayBGM(L"Crystals.ogg", m_fVol);
}

void Tutorial::Initialize()
{
	m_fPhoneCalltime = GetTickCount();
	CObjMgr::Get_Instance()->Add_Object(MOUSE, CAbstractFactory<CMouse>::Create());

	CPlayer::Get_Instance()->Initialize();
	CPlayer::Get_Instance()->Get_Player()->Set_PosX(787);
	CPlayer::Get_Instance()->Get_Player()->Set_PosY(591);
	CCameraMgr::Get_Instance()->Set_Target(CPlayer::Get_Instance()->Get_Player());
	
	CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CPlayerUI>::Create());
	CTileMgr::Get_Instance()->Load_DataT();
	WallMgr::Get_Instance()->Load_HT();
	VWallMgr::Get_Instance()->Load_VT();
	CornerMgr::Get_Instance()->Load_CT();

	m_rGate = { 618,412,675,440 };
	m_rPhone = { 492,567,544,594 };

	CSoundMgr::Get_Instance()->PlayBGM(L"DeepCover.ogg", m_fVol);


	m_TFrame.iFrameStart = 0;
	m_TFrame.iFrameEnd = 11;
	m_TFrame.iMotion = 0;
	m_TFrame.dwTime = GetTickCount();
	m_TFrame.dwSpeed = 50;

	ScorMgr::Get_Instance()->Set_Timer();
}

void Tutorial::Update()
{
	CCameraMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	WallMgr::Get_Instance()->Update();
	VWallMgr::Get_Instance()->Update();
	CornerMgr::Get_Instance()->Update();
	CPlayer::Get_Instance()->Get_Player()->Update();
	CObjMgr::Get_Instance()->Update();

	if (CKeyMgr::Get_Instance()->Key_Up(VK_RETURN) && CloseEvent)
	{
		ImageNum++;
	}
	if (ImageNum > 1)
	{
		CloseEvent = false;
		CPlayer::Get_Instance()->Set_NOMOVE(false);
		CObjMgr::Get_Instance()->Delete_ID(EFFECTS);
	}
	Move_Frame();
}

void Tutorial::Late_Update()
{
	CTileMgr::Get_Instance()->Late_Update();
	WallMgr::Get_Instance()->Late_Update();
	VWallMgr::Get_Instance()->Late_Update();
	CornerMgr::Get_Instance()->Late_Update();
	CPlayer::Get_Instance()->Get_Player()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();

	if (m_fPhoneCalltime + 3000 < GetTickCount() && isPhonecall)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"PhoneCall.wav", SOUND_EFFECT, m_fVol);
		CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<Go>::Create(515, 576, 0));
		isPhonecall = false;
	}
	

	int CameraX = CCameraMgr::Get_Instance()->m_fDiffX;
	int CameraY = CCameraMgr::Get_Instance()->m_fDiffY;
	RECT rc{};
	RECT mGate{ m_rGate.left - CameraX , m_rGate.top - CameraY,
	m_rGate.right - CameraX, m_rGate.bottom - CameraY };
	
	if (IntersectRect(&rc, &mGate, &(CPlayer::Get_Instance()->Get_Rect())))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
	}
}

void Tutorial::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Blackback");
	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
	CTileMgr::Get_Instance()->Render(hDC);
	WallMgr::Get_Instance()->Render(hDC);
	VWallMgr::Get_Instance()->Render(hDC);
	CornerMgr::Get_Instance()->Render(hDC);
	CPlayer::Get_Instance()->Get_Player()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);


	int CameraX = CCameraMgr::Get_Instance()->m_fDiffX;
	int CameraY = CCameraMgr::Get_Instance()->m_fDiffY;
	RECT RC{};
	RECT PH{ m_rPhone.left - CameraX , m_rPhone.top - CameraY,
	m_rPhone.right - CameraX ,m_rPhone.bottom - CameraY };
	if (CloseEvent && !isPhonecall && IntersectRect(&RC, &PH, &(CPlayer::Get_Instance()->Get_Rect())))
	{
		CPlayer::Get_Instance()->Set_NOMOVE(true);
		Graphics Grap(hDC);
		Grap.DrawImage(PngMrg::Get_Instance()->Get_Image(L"TextBox"),
			100, 300,
			0, 100 * ImageNum,
			400, 100,
			UnitPixel);

		Grap.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Tutorial"),
			650, 300,
			81 * m_TFrame.iFrameStart, 0,
			81, 90,
			UnitPixel);
	}

	//graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(m_PngKey), //그려야 할 이미지 (스프라이트 시트)
	//	m_tRect.left, m_tRect.top,					//그리기 시작할 위치
	//	m_tFrame.iMotion * 40, m_tFrame.iFrameStart * 40,					//이미지의 어디서부터 그릴지
	//	(INT)m_tInfo.fCX, (INT)m_tInfo.fCY,				//이미지의 어디까지 그릴지
	//	UnitPixel);
}

void Tutorial::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(MOUSE);
	CObjMgr::Get_Instance()->Delete_ID(EFFECTS);
	CPlayer::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->StopAll();
}

void Tutorial::Move_Frame()
{
	if (m_TFrame.dwSpeed + m_TFrame.dwTime < GetTickCount())
	{
		++m_TFrame.iFrameStart;

		if (m_TFrame.iFrameStart > m_TFrame.iFrameEnd)
			m_TFrame.iFrameStart = 0;

		m_TFrame.dwTime = GetTickCount();
	}
}
