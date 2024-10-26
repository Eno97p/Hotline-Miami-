#include "stdafx.h"
#include "Stage2.h"
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
Stage2::Stage2() : m_fVolume(1.f) , StageClear(false)
{
	ZeroMemory(&m_rGate, sizeof(RECT));
}

Stage2::~Stage2()
{
	Release();
}

void Stage2::Initialize()
{
	srand(unsigned(time(NULL)));
	CObjMgr::Get_Instance()->Add_Object(MOUSE, CAbstractFactory<CMouse>::Create());
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CBat>::Create(485, 872, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CPipe>::Create(277, 675, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CShotGun>::Create(449, 727, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(369, 606, rand() % 360, PIPE));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(362, 777, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(362, 783, rand() % 360, PIPE));

	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(521, 880, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(341, 1118, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(423, 1118, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(823, 917, rand() % 360, PIPE, PATROLL));

	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(827, 574, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(827, 624, rand() % 360, PIPE, PATROLL));

	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(604, 815, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(506, 726, rand() % 360, UZI, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(525, 1129, rand() % 360, PIPE));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(823, 859, rand() % 360, UZI, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(711, 724, rand() % 360, SHOTGUN, PATROLL));
	CPlayer::Get_Instance()->Initialize();
	CPlayer::Get_Instance()->Get_Player()->Set_PosX(213);
	CPlayer::Get_Instance()->Get_Player()->Set_PosY(523);
	CCameraMgr::Get_Instance()->Set_Target(CPlayer::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CPlayerUI>::Create());

	CTileMgr::Get_Instance()->Load_Data2();
	WallMgr::Get_Instance()->Load_H2();
	VWallMgr::Get_Instance()->Load_V2();
	CornerMgr::Get_Instance()->Load_C2();

	m_rGate = { 938, 700, 996, 758 };
}

void Stage2::Update()
{
	CCameraMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	WallMgr::Get_Instance()->Update();
	VWallMgr::Get_Instance()->Update();
	CornerMgr::Get_Instance()->Update();
	CPlayer::Get_Instance()->Get_Player()->Update();
	CObjMgr::Get_Instance()->Update();
}

void Stage2::Late_Update()
{
	
	CTileMgr::Get_Instance()->Late_Update();
	WallMgr::Get_Instance()->Late_Update();
	VWallMgr::Get_Instance()->Late_Update();
	CornerMgr::Get_Instance()->Late_Update();
	CPlayer::Get_Instance()->Get_Player()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();


	int CameraX = CCameraMgr::Get_Instance()->m_fDiffX;
	int CameraY = CCameraMgr::Get_Instance()->m_fDiffY;
	if (Is_StageClear())
	{
		if (!StageClear)
		{
			CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<Go>::Create(960, 730, 0));
			StageClear = true;
		}

		RECT rc{};
		RECT mGate{ m_rGate.left - CameraX , m_rGate.top - CameraY,
		m_rGate.right - CameraX, m_rGate.bottom - CameraY };
		if (IntersectRect(&rc, &mGate, &(CPlayer::Get_Instance()->Get_Rect())))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE3);
		}

	}
}

void Stage2::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Blackback");
	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
	CTileMgr::Get_Instance()->Render(hDC);
	WallMgr::Get_Instance()->Render(hDC);
	VWallMgr::Get_Instance()->Render(hDC);
	CornerMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CPlayer::Get_Instance()->Get_Player()->Render(hDC);
	if (Is_StageClear())
	{
		Graphics graphics(hDC);
		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Stage_Clear"),
			WINCX / 2 - 150, 150,
			300, 100);
	}
}

void Stage2::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(MOUSE);
	CObjMgr::Get_Instance()->Delete_ID(WEAPON);
	CObjMgr::Get_Instance()->Delete_ID(BULLET);
	CObjMgr::Get_Instance()->Delete_ID(MBULLET);
	CObjMgr::Get_Instance()->Delete_ID(EFFECTS);
	CPlayer::Get_Instance()->Destroy_Instance();
}

bool Stage2::Is_StageClear()
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
