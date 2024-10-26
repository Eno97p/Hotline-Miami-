#include "stdafx.h"
#include "Stage.h"
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
CStage::CStage() : m_fVolume(1.f), StageClear(false)
{
	
	ZeroMemory(&m_rGate, sizeof(RECT));
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	// 플레이어 추가	
	srand(unsigned(time(NULL)));
	/*CObjMgr::Get_Instance()->Delete_ID(MOUSE);
	CObjMgr::Get_Instance()->Delete_ID(WEAPON);
	CObjMgr::Get_Instance()->Delete_ID(BULLET);
	CObjMgr::Get_Instance()->Delete_ID(MBULLET);
	CObjMgr::Get_Instance()->Delete_ID(EFFECTS);
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(PLAYER);*/
	
	CObjMgr::Get_Instance()->Add_Object(MOUSE, CAbstractFactory<CMouse>::Create());
	/*CObjMgr::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer>::Create(1274,1175,0));*/
	CPlayer::Get_Instance()->Initialize();
	CPlayer::Get_Instance()->Get_Player()->Set_PosX(1274);
	CPlayer::Get_Instance()->Get_Player()->Set_PosY(1175);
	CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CPlayerUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CBat>::Create(1168,1176,rand()%360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CPipe>::Create(885, 1041, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CShotGun>::Create(872, 687, rand() % 360));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CUzi>::Create(1195, 945, rand() % 360));

	CObjMgr::Get_Instance()->Add_Object(MONSTER,CAbstractFactory<CMonster>::Create(927, 836, rand() % 360,UZI,PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(812, 1019, rand() % 360, BAT));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1017, 1125, rand() % 360, PIPE, PATROLL));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(1222, 950, rand() % 360, SHOTGUN));
	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(861, 1064, rand() % 360, PIPE));

	CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(796, 686, rand() % 360, BAT));

	

	//CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CBoss>::Create(400, 300, rand() % 360));
	CCameraMgr::Get_Instance()->Set_Target(CPlayer::Get_Instance()->Get_Player());


	/*for (int i = 0; i < 5; ++i)
	{
		CObjMgr::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMonster>::Create(rand() % WINCX, rand() % WINCY, 0.f));
	}*/

	//CLineMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Data();
	WallMgr::Get_Instance()->Load_H();
	VWallMgr::Get_Instance()->Load_V();
	CornerMgr::Get_Instance()->Load_C();

	
	
	m_rGate = { 600, 825, 650, 880 };
	
}

void CStage::Update()
{
	CCameraMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	WallMgr::Get_Instance()->Update();
	VWallMgr::Get_Instance()->Update();
	CornerMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CPlayer::Get_Instance()->Get_Player()->Update();
	
}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
	WallMgr::Get_Instance()->Late_Update();
	VWallMgr::Get_Instance()->Late_Update();
	CornerMgr::Get_Instance()->Late_Update();
	CPlayer::Get_Instance()->Get_Player()->Late_Update();

	int CameraX = CCameraMgr::Get_Instance()->m_fDiffX;
	int CameraY = CCameraMgr::Get_Instance()->m_fDiffY;

	
	if (Is_StageClear())
	{
		if (!StageClear)
		{
			CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<Go>::Create(625, 850, 0));
			StageClear = true;
		}

		RECT rc{};
		/*CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<Go>::Create(630, 900, 0));*/
		
		RECT mGate{ m_rGate.left - CameraX , m_rGate.top - CameraY,
		m_rGate.right - CameraX, m_rGate.bottom - CameraY };
		if (IntersectRect(&rc, &mGate, &(CPlayer::Get_Instance()->Get_Rect())))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE2);
		}

	}
}

void CStage::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Blackback");
	
	/*HDC		hGroundDC = PngMrg::Get_Instance()->Get_Image(L"Blackback")*/
	/*int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();*/

	int CameraX = CCameraMgr::Get_Instance()->m_fDiffX;
	int CameraY = CCameraMgr::Get_Instance()->m_fDiffY;

	BitBlt(hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	WallMgr::Get_Instance()->Render(hDC);
	VWallMgr::Get_Instance()->Render(hDC);
	CornerMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	CPlayer::Get_Instance()->Get_Player()->Render(hDC);
	//CLineMgr::Get_Instance()->Render(hDC);

	if (Is_StageClear())
	{
		Graphics graphics(hDC);
		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Stage_Clear"),
			WINCX / 2 - 150, 150,
			300, 100);
	}

}

void CStage::Release()
{
	/*CSoundMgr::Get_Instance()->StopAll();*/
	CObjMgr::Get_Instance()->Delete_ID(MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(MOUSE);
	CObjMgr::Get_Instance()->Delete_ID(WEAPON);
	CObjMgr::Get_Instance()->Delete_ID(BULLET);
	CObjMgr::Get_Instance()->Delete_ID(MBULLET);
	CObjMgr::Get_Instance()->Delete_ID(EFFECTS);
	CPlayer::Get_Instance()->Destroy_Instance();
	
}

bool CStage::Is_StageClear()
{
	for (auto& iter : CObjMgr::Get_Instance()->Get_List(MONSTER))
	{
		if (!static_cast<CMonster*>(iter)->IS_MONSTERDEAD())
		{
			return false;
		}
	}
	return true;
}
