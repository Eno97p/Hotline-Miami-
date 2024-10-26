#include "stdafx.h"
#include "Stage4.h"
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
#include "CollisionMgr.h"
Stage4::Stage4() :StageClear(false), m_fVol(0.5f), PreCS(EVENT_END), CurCS(NOTBOMB), fFrame(0.f), iExXNum(0), iExYNum(0)
{
	ZeroMemory(&m_rBombRect, sizeof(RECT));
	ZeroMemory(&m_rEventRT, sizeof(RECT));
	ZeroMemory(&m_rGate, sizeof(RECT));
}

Stage4::~Stage4()
{
	Release();
	
}

void Stage4::Initialize()
{
	srand(unsigned(time(NULL)));
	CObjMgr::Get_Instance()->Add_Object(MOUSE, CAbstractFactory<CMouse>::Create());

	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CUzi>::Create(800, 225, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CPipe>::Create(557, 612, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CBat>::Create(557, 705, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CShotGun>::Create(1378, 830, rand() % 360));

	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(988, 644, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(937, 644, rand() % 360, BAT));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1010, 551, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(894, 405, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(633, 204, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(653, 329, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1205, 373, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1319, 591, rand() % 360, BAT));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1392, 521, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1320, 859, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1797, 621, rand() % 360, PIPE));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1770, 692, rand() % 360, BAT));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1768, 754, rand() % 360, BAT));

	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(797, 461, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1227, 453, rand() % 360, BAT, PATROLL));

	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(894, 333, rand() % 360, SHOTGUN, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(637, 403, rand() % 360, UZI));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(984, 381, rand() % 360, SHOTGUN));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1115, 223, rand() % 360, UZI));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1317, 259, rand() % 360, SHOTGUN, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1248, 603, rand() % 360, UZI, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1319, 780, rand() % 360, SHOTGUN));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1229, 782, rand() % 360, UZI));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1874, 665, rand() % 360, SHOTGUN));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1874, 734, rand() % 360, UZI));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(801, 297, rand() % 360, UZI, PATROLL));

	CPlayer::Get_Instance()->Initialize();
	CPlayer::Get_Instance()->Get_Player()->Set_PosX(556);
	CPlayer::Get_Instance()->Get_Player()->Set_PosY(655);
	CCameraMgr::Get_Instance()->Set_Target(CPlayer::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CPlayerUI>::Create());
	CTileMgr::Get_Instance()->Load_Data4();
	WallMgr::Get_Instance()->Load_H4();
	VWallMgr::Get_Instance()->Load_V4();
	CornerMgr::Get_Instance()->Load_C4();

	m_rGate = { 2523,459,2582,513 };
	m_rEventRT = { 1616,660,1660,720 };
	m_rBombRect = { 1480,567,1795,815 };
}

void Stage4::Update()
{
	CCameraMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	WallMgr::Get_Instance()->Update();
	VWallMgr::Get_Instance()->Update();
	CornerMgr::Get_Instance()->Update();
	CPlayer::Get_Instance()->Get_Player()->Update();
	CObjMgr::Get_Instance()->Update();
}

void Stage4::Late_Update()
{
	CTileMgr::Get_Instance()->Late_Update();
	WallMgr::Get_Instance()->Late_Update();
	VWallMgr::Get_Instance()->Late_Update();
	CornerMgr::Get_Instance()->Late_Update();
	CPlayer::Get_Instance()->Get_Player()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();

	int CameraX = CCameraMgr::Get_Instance()->m_fDiffX;
	int CameraY = CCameraMgr::Get_Instance()->m_fDiffY;

	if (PreCS == EXPLOSION)
	{
		if (fFrame + 20 < GetTickCount())
		{
			iExXNum++;
			fFrame = GetTickCount();
			if (iExXNum == 4)
			{
				++iExYNum;
				iExXNum = 0;
			}
			if (iExXNum == 1 && iExYNum == 2)
			{
				CurCS = BOMBEND;
			}
		}
	}


	if (Is_StageClear())
	{

		if (!StageClear)
		{
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlaySound(L"sndLevelComplete.wav", SOUND_EFFECT, m_fVol);
			CSoundMgr::Get_Instance()->PlayBGM(L"Crush.ogg", m_fVol);
			CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<Go>::Create(2550, 513, 1));
			StageClear = true;
		}
		RECT rc{};
		RECT mGate{ m_rGate.left - CameraX , m_rGate.top - CameraY,
		m_rGate.right - CameraX, m_rGate.bottom - CameraY };
		if (IntersectRect(&rc, &mGate, &(CPlayer::Get_Instance()->Get_Rect())))
		{
			CSoundMgr::Get_Instance()->StopAll();
			CSoundMgr::Get_Instance()->PlayBGM(L"Hotline.ogg", m_fVol);
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE5);
		}

	}
	BombEvent();
	SC_Motion_Change();
}

void Stage4::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Blackback");
	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
	int CameraX = CCameraMgr::Get_Instance()->m_fDiffX;
	int CameraY = CCameraMgr::Get_Instance()->m_fDiffY;
	Graphics graphics(hDC);
	RECT Rc{};
	RECT BOMB{ m_rEventRT.left - CameraX , m_rEventRT.top - CameraY ,
	m_rEventRT.right - CameraX , m_rEventRT.bottom - CameraY };
	CTileMgr::Get_Instance()->Render(hDC);
	if (PreCS == BOMBEND)
	{
		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"BombTrace"),
			1420 - CameraX, 500 - CameraY);
	}
	WallMgr::Get_Instance()->Render(hDC);
	VWallMgr::Get_Instance()->Render(hDC);
	CornerMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CPlayer::Get_Instance()->Get_Player()->Render(hDC);
	if (Is_StageClear())
	{

		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Stage_Clear"),
			WINCX / 2 - 150, 150,
			300, 100);
	}

	if (PreCS == NOTBOMB)
	{
		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Bomb"),
			BOMB.left, BOMB.top);
	}
	else if (PreCS == EXPLOSION)
	{
		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Explosion"),
			1272 - CameraX, 330 - CameraY,
			500 * iExXNum, 500* iExYNum,
			500, 500,
			UnitPixel);
	}
}

void Stage4::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(MOUSE);
	CObjMgr::Get_Instance()->Delete_ID(WEAPON);
	CObjMgr::Get_Instance()->Delete_ID(BULLET);
	CObjMgr::Get_Instance()->Delete_ID(MBULLET);
	CObjMgr::Get_Instance()->Delete_ID(EFFECTS);
	CPlayer::Get_Instance()->Destroy_Instance();

	
}

bool Stage4::Is_StageClear()
{
	for (auto& iter : CObjMgr::Get_Instance()->Get_List(MONSTER))
	{
		if (iter)
		{
			if (!static_cast<CMonster*>(iter)->IS_MONSTERDEAD())
			{
				return false;
			}
		}
	}
	return true;
}

void Stage4::BombEvent()
{
	int CameraX = CCameraMgr::Get_Instance()->m_fDiffX;
	int CameraY = CCameraMgr::Get_Instance()->m_fDiffY;
	RECT Rc{};
	RECT BOMB{ m_rEventRT.left - CameraX , m_rEventRT.top - CameraY ,
	m_rEventRT.right - CameraX , m_rEventRT.bottom - CameraY };
	RECT Destroy{ m_rBombRect.left - CameraX, m_rBombRect.top - CameraY,
		m_rBombRect.right - CameraX,m_rBombRect.bottom - CameraY };

	if (PreCS == NOTBOMB && IntersectRect(&Rc, &BOMB, &(CPlayer::Get_Instance()->Get_Rect())))
	{
		CurCS = EXPLOSION;
		CPlayer::Get_Instance()->Player_Die();
		CCollisionMgr::BOMB_RECT2(Destroy, CObjMgr::Get_Instance()->Get_List(MONSTER));
	}
	else if (PreCS == NOTBOMB && CCollisionMgr::BOMB_RECT(BOMB, CObjMgr::Get_Instance()->Get_List(BULLET)))
	{
		CurCS = EXPLOSION;
		CCollisionMgr::BOMB_RECT2(Destroy, CObjMgr::Get_Instance()->Get_List(MONSTER));

	}


}

void Stage4::SC_Motion_Change()
{
	/*NOTBOMB, EXPLOSION, BOMBEND, EVENT_END*/
	if (PreCS != CurCS)
	{
		switch (CurCS)
		{
		case NOTBOMB:
			break;
		case EXPLOSION:
			CSoundMgr::Get_Instance()->PlaySound(L"sndBigExplosion.wav", SOUND_EFFECT, m_fVol);
			fFrame = GetTickCount();
			break;
		case BOMBEND:
			break;
		}
		PreCS = CurCS;
	}

}
