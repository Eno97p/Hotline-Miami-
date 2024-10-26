#include "stdafx.h"
#include "Stage3.h"
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
Stage3::Stage3() : StageClear(false)
{
	ZeroMemory(&m_rGate, sizeof(RECT));
}

Stage3::~Stage3()
{
	Release();
}

void Stage3::Initialize()
{
	srand(unsigned(time(NULL)));
	CObjMgr::Get_Instance()->Add_Object(MOUSE, CAbstractFactory<CMouse>::Create());

	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CShotGun>::Create(788, 1607, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CShotGun>::Create(1109, 1475, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CUzi>::Create(799, 1374, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CUzi>::Create(928, 1521, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CPipe>::Create(1224, 1380, rand() % 360));

	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1225, 1241, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1071, 1226, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1071, 1284, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1071, 1328, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1050, 1565, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1128, 1568, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1088, 1531, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(566, 1403, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(566, 1449, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(286, 1442, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(344, 1442, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(514, 1695, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(567, 1695, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(639, 1695, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(514, 1802, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(567, 1802, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(639, 1802, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(674, 1875, rand() % 360, BAT, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(808, 1429, rand() % 360, SHOTGUN));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(793, 1516, rand() % 360, UZI));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(882, 1561, rand() % 360, SHOTGUN));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(292, 1927, rand() % 360, UZI));


	CPlayer::Get_Instance()->Initialize();
	CPlayer::Get_Instance()->Get_Player()->Set_PosX(1224);
	CPlayer::Get_Instance()->Get_Player()->Set_PosY(1443);
	CCameraMgr::Get_Instance()->Set_Target(CPlayer::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CPlayerUI>::Create());
	CTileMgr::Get_Instance()->Load_Data3();
	WallMgr::Get_Instance()->Load_H3();
	VWallMgr::Get_Instance()->Load_V3();
	CornerMgr::Get_Instance()->Load_C3();

	m_rGate = { 360,1980,440,2040 };
}

void Stage3::Update()
{
	CCameraMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	WallMgr::Get_Instance()->Update();
	VWallMgr::Get_Instance()->Update();
	CornerMgr::Get_Instance()->Update();
	CPlayer::Get_Instance()->Get_Player()->Update();
	CObjMgr::Get_Instance()->Update();
}

void Stage3::Late_Update()
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
			CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<Go>::Create(360, 2026, 1));
			StageClear = true;
		}
		RECT rc{};
		RECT mGate{ m_rGate.left - CameraX , m_rGate.top - CameraY,
		m_rGate.right - CameraX, m_rGate.bottom - CameraY };
		if (IntersectRect(&rc, &mGate, &(CPlayer::Get_Instance()->Get_Rect())))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE4);
		}

	}
}

void Stage3::Render(HDC hDC)
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

void Stage3::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(MOUSE);
	CObjMgr::Get_Instance()->Delete_ID(WEAPON);
	CObjMgr::Get_Instance()->Delete_ID(BULLET);
	CObjMgr::Get_Instance()->Delete_ID(MBULLET);
	CObjMgr::Get_Instance()->Delete_ID(EFFECTS);
	CPlayer::Get_Instance()->Destroy_Instance();
}

bool Stage3::Is_StageClear()
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
