#include "stdafx.h"
#include "WallV.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"

WallV::WallV(): m_iDrawID(0), m_iOption(0), m_TileKey(nullptr)
{
}

WallV::~WallV()
{
	Release();
}

void WallV::Initialize()
{
	m_tInfo.fCX = 8.f;
	m_tInfo.fCY = 32.f;
	m_TileKey = L"WallV";

	m_eRender = BACKGROUND;
}

int WallV::Update()
{
	__super::Update_Rect();
	__super::Update_Rect_Pos();
	return OBJ_NOEVENT;
}

void WallV::Late_Update()
{
	CCollisionMgr::Collision_Rect(this, CObjMgr::Get_Instance()->Get_List(BULLET));
	CCollisionMgr::Collision_Rect(this, CObjMgr::Get_Instance()->Get_List(MBULLET));
}

void WallV::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_TileKey);
	BitBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tInfo.fCX, m_tInfo.fCY, hMemDC, 0, 0, SRCCOPY);

	/*Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);*/
}

void WallV::Release()
{
}
