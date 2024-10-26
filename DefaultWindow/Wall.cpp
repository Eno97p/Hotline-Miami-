#include "stdafx.h"
#include "Wall.h"
#include "BmpMgr.h"
#include "PngMrg.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"

CWall::CWall() : m_iDrawID(0), m_iOption(0), m_TileKey(nullptr)
{

}

CWall::~CWall()
{
	Release();
}

void CWall::Initialize()
{
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 8.f;
	m_TileKey = L"WallH";

	m_eRender = BACKGROUND;

}

int CWall::Update()
{
	__super::Update_Rect();
	__super::Update_Rect_Pos();
	return OBJ_NOEVENT;
}

void CWall::Late_Update()
{
	CCollisionMgr::Collision_Rect(this, CObjMgr::Get_Instance()->Get_List(BULLET));
	CCollisionMgr::Collision_Rect(this, CObjMgr::Get_Instance()->Get_List(MBULLET));
}

void CWall::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_TileKey);
	BitBlt(hDC,
		m_tRect.left ,
		m_tRect.top ,
		m_tInfo.fCX, m_tInfo.fCY, hMemDC, 0, 0 , SRCCOPY);
	
}

void CWall::Release()
{
	
}
