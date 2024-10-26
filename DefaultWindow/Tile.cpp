#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"



CTile::CTile()
	: m_iXNum(0), m_iYNum(0) , m_TileKey(nullptr)
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
	m_TileKey = L"Tile";
	m_eRender = BACKGROUND;
}

int CTile::Update()
{

	__super::Update_Rect();
	__super::Update_Rect_Pos();
	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{

}

void CTile::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_TileKey);
	/*BitBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		TILECX, TILECY, hMemDC, TILECX * m_iXNum, TILECY* m_iYNum, SRCCOPY);*/

	GdiTransparentBlt(hDC,
				m_tRect.left,
				m_tRect.top,
				TILECX,
				TILECY,
				hMemDC,
		TILECX * m_iXNum, //소스 그림의 시작 좌표
		TILECY * m_iYNum,			//소스 그림의 시작 좌표
		TILECX,
		TILECY,
				RGB(0, 0, 255));
}

void CTile::Release()
{
	
}

void CTile::Set_TileKey(int i)
{
	switch (i)
	{
	case 1:
		m_TileKey = L"Tile";
		break;
	case 2:
		m_TileKey = L"Block";
		break;
	}
}
