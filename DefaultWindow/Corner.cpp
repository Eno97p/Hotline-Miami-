#include "stdafx.h"
#include "Corner.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

Corner::Corner() : m_iXNum(0), m_iYNum(0), m_TileKey(nullptr)
{
}

Corner::~Corner()
{
    Release();
}

void Corner::Initialize()
{
    m_tInfo.fCX = 8.f;
    m_tInfo.fCY = 8.f;
    m_TileKey = L"Corner";
    m_eRender = BACKGROUND;
}

int Corner::Update()
{
    __super::Update_Rect();
    __super::Update_Rect_Pos();
    return OBJ_NOEVENT;
}

void Corner::Late_Update()
{
    CCollisionMgr::Collision_Rect(this, CObjMgr::Get_Instance()->Get_List(BULLET));
    CCollisionMgr::Collision_Rect(this, CObjMgr::Get_Instance()->Get_List(MBULLET));
}

void Corner::Render(HDC hDC)
{
  
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_TileKey);
 


    GdiTransparentBlt(hDC,
        m_tRect.left ,
        m_tRect.top ,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hMemDC,
        (int)m_tInfo.fCX *m_iXNum, //소스 그림의 시작 좌표
        (int)m_tInfo.fCY * m_iYNum,			//소스 그림의 시작 좌표
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        RGB(0, 0, 255));
}

void Corner::Release()
{
}
