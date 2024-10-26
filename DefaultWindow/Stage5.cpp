#include "stdafx.h"
#include "Stage5.h"
#include "ObjMgr.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "Monster.h"
#include "Mouse.h"
#include "SoundMgr.h"
#include "PngMrg.h"
#include "Bat.h"
#include "Pipe.h"
#include "ShotGun.h"
#include "Uzi.h"
#include "Boss.h"
#include "Knife.h"
#include "Wall.h"
#include "WallMgr.h"
#include "VWallMgr.h"
#include "CornerMgr.h"
#include "CCameraMgr.h"
#include "SceneMgr.h"
#include "Go.h"
#include "PlayerUI.h"
#include "KeyMgr.h"

Stage5::Stage5() : StageClear(false), m_fVol(0.5f), m_fLoudVol(1.f), EventStart(false), m_5Num(0) , CloseEvent(false),
m_ePreB(SCENE_END),m_eCurB(NON_START) , m_fBloodpooltic(0.f), m_iBloodPool(0), m_bGroggyText(true)
{
	ZeroMemory(&m_rGate, sizeof(RECT));
}

Stage5::~Stage5()
{
	Release();
}

void Stage5::Initialize()
{
	srand(unsigned(time(NULL)));
	CObjMgr::Get_Instance()->Add_Object(MOUSE, CAbstractFactory<CMouse>::Create());



	CPlayer::Get_Instance()->Initialize();
	CPlayer::Get_Instance()->Get_Player()->Set_PosX(626);
	CPlayer::Get_Instance()->Get_Player()->Set_PosY(990);
	CCameraMgr::Get_Instance()->Set_Target(CPlayer::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CPlayerUI>::Create());
	
	CBoss::Get_Instance()->Initialize();
	CBoss::Get_Instance()->Get_Boss()->Set_PosX(626);
	CBoss::Get_Instance()->Get_Boss()->Set_PosY(300);
	
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CShotGun>::Create(895, 734, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CShotGun>::Create(895, 297, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CShotGun>::Create(982, 511, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CShotGun>::Create(366, 734, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CShotGun>::Create(366, 288, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CShotGun>::Create(274, 501, rand() % 360));

	
	CTileMgr::Get_Instance()->Load_Data5();
	WallMgr::Get_Instance()->Load_H5();
	VWallMgr::Get_Instance()->Load_V5();
	CornerMgr::Get_Instance()->Load_C5();

	m_rGate = { 587,786,661,822 };

	m_5Num = 0;
}

void Stage5::Update()
{
	CCameraMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	WallMgr::Get_Instance()->Update();
	VWallMgr::Get_Instance()->Update();
	CornerMgr::Get_Instance()->Update();
	CPlayer::Get_Instance()->Get_Player()->Update();
	CBoss::Get_Instance()->Get_Boss()->Update();
	CObjMgr::Get_Instance()->Update();

	/*if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN) && EventStart)
	{
		m_5Num++;
	}
	if (m_5Num > 1)
	{
		CPlayer::Get_Instance()->Set_NOMOVE(false);
		CBoss::Get_Instance()->Set_CutScene(false);
		CloseEvent = true;
		EventStart = false;
	}*/
	if (m_ePreB == BOSS_DIE && m_fBloodpooltic + 500 < GetTickCount() && m_iBloodPool <11)
	{
		m_iBloodPool++;
		m_fBloodpooltic = GetTickCount();
	}
}

void Stage5::Late_Update()
{
	CTileMgr::Get_Instance()->Late_Update();
	WallMgr::Get_Instance()->Late_Update();
	VWallMgr::Get_Instance()->Late_Update();
	CornerMgr::Get_Instance()->Late_Update();
	CPlayer::Get_Instance()->Get_Player()->Late_Update();
	CBoss::Get_Instance()->Get_Boss()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();

	int CameraX = CCameraMgr::Get_Instance()->m_fDiffX;
	int CameraY = CCameraMgr::Get_Instance()->m_fDiffY;
	RECT rc{};
	RECT mGate{ m_rGate.left - CameraX , m_rGate.top - CameraY,
	m_rGate.right - CameraX, m_rGate.bottom - CameraY };
	if (IntersectRect(&rc, &mGate, &(CPlayer::Get_Instance()->Get_Rect())) && !EventStart && !CloseEvent)
	{
		CPlayer::Get_Instance()->Set_NOMOVE(true);
		CBoss::Get_Instance()->Set_CutScene(true);
		EventStart = true;
	}
	if (m_ePreB == NON_START && CKeyMgr::Get_Instance()->Key_Down(VK_RETURN) && EventStart)
	{
		m_5Num++;
	}
	if (m_ePreB == NON_START && m_5Num > 2)
	{
		CPlayer::Get_Instance()->Set_NOMOVE(false);
		CBoss::Get_Instance()->Set_CutScene(false);
		CloseEvent = true;
		EventStart = false;
	}
	if (m_ePreB == BOSS_GROGGY && CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CPlayer::Get_Instance()->Set_NOMOVE(false);
		m_bGroggyText = false;
	}
	if (IntersectRect(&rc, &mGate, &(CPlayer::Get_Instance()->Get_Rect()))&& m_ePreB == BOSS_DIE)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SCORE_SCENE);
	}

	Is_Boss_Groggy();
	Is_Boss_Die();
	Scene_Motion_Change();
}

void Stage5::Render(HDC hDC)
{
	
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Blackback");
	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
	Graphics graphics(hDC);
	CTileMgr::Get_Instance()->Render(hDC);
	if (m_ePreB == BOSS_DIE)
	{
		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BloodPool"),
			CBoss::Get_Instance()->Get_Rect().left+10, CBoss::Get_Instance()->Get_Rect().top+10,
			50 * m_iBloodPool, 0,
			50, 50,
			UnitPixel);
		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BloodPool"),
			CBoss::Get_Instance()->Get_Rect().left + 30, CBoss::Get_Instance()->Get_Rect().top,
			50 * m_iBloodPool, 0,
			50, 50,
			UnitPixel);
	}
	WallMgr::Get_Instance()->Render(hDC);
	VWallMgr::Get_Instance()->Render(hDC);
	CornerMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CBoss::Get_Instance()->Get_Boss()->Render(hDC);
	CPlayer::Get_Instance()->Get_Player()->Render(hDC);
	
	/*if (Is_StageClear())
	{
		Graphics graphics(hDC);
		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Stage_Clear"),
			WINCX / 2 - 150, 150,
			300, 100);
	}*/
	if (EventStart && !CloseEvent)
	{
		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"TextBoxBoss"),
			200, 400,
			0, 100 * m_5Num,
			400, 100,
			UnitPixel);

		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BossFace"),
			600, 300);
	}
	if (m_ePreB == BOSS_GROGGY && m_bGroggyText)
	{
		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"TextBoxBoss"),
			200, 400,
			0, 300,
			400, 100,
			UnitPixel);

		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BossFace"),
			600, 300);
	}
}

void Stage5::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(MOUSE);
	CObjMgr::Get_Instance()->Delete_ID(WEAPON);
	CObjMgr::Get_Instance()->Delete_ID(BULLET);
	CObjMgr::Get_Instance()->Delete_ID(MBULLET);
	CObjMgr::Get_Instance()->Delete_ID(EFFECTS);


	CPlayer::Get_Instance()->Destroy_Instance();
	CBoss::Get_Instance()->Destroy_Instance();
}

void Stage5::Scene_Motion_Change()
{
	/*NON_START, BOSS_GROGGY, BOSS_DIE, SCENE_END*/
	if (m_ePreB != m_eCurB)
	{
		switch (m_eCurB)
		{
		case NON_START:
			break;
		case BOSS_GROGGY:
			CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CPipe>::Create(626, 497, rand() % 360));
			CPlayer::Get_Instance()->Set_NOMOVE(true);
			break;
		case BOSS_DIE:
			m_fBloodpooltic = GetTickCount();
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlaySound(L"sndHit1.wav", SOUND_EFFECT, m_fLoudVol);
			CSoundMgr::Get_Instance()->PlaySound(L"sndLevelComplete.wav", SOUND_EFFECT, m_fVol);
			CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<Go>::Create(619, 781, 0));
			break;
		}
		m_ePreB = m_eCurB;
	}
}

void Stage5::Is_Boss_Groggy()
{
	if (CBoss::Get_Instance()->Get_GROGGY() == true)
	{
		m_eCurB = BOSS_GROGGY;
	}
}

void Stage5::Is_Boss_Die()
{
	if (CBoss::Get_Instance()->Get_Boss_Dead())
	{
		m_eCurB = BOSS_DIE;
	}
}


