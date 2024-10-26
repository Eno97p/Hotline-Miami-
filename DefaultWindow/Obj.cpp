#include "stdafx.h"
#include "Obj.h"


CObj::CObj() : m_fSpeed(0.f), m_eDir(DIR_END), m_bDead(false), m_fAngle(0.f), m_pTarget(nullptr)
, m_pFrameKey(nullptr), m_eRender(RENDER_END), m_bWeaponIntersect(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CObj::~CObj()
{
}

void CObj::Set_Wall()
{


}

void CObj::Set_Intersect(bool intersect)
{
	m_bWeaponIntersect = intersect;
}

void CObj::Set_WeaponState(WEAPONSTATE WPSTATE)
{
	m_eWeaponState = WPSTATE;
}

void CObj::Update_Rect()
{
	//m_tInfo.fX -= (CCameraMgr::Get_Instance()->m_fDiffX);
	//m_tInfo.fY -= (CCameraMgr::Get_Instance()->m_fDiffY);
	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top		= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom	= LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
	/*m_tRect.left -= CCameraMgr::Get_Instance()->m_fDiffX;
	m_tRect.top -= CCameraMgr::Get_Instance()->m_fDiffY;
	m_tRect.right -= CCameraMgr::Get_Instance()->m_fDiffX;
	m_tRect.bottom -= CCameraMgr::Get_Instance()->m_fDiffY;*/

}

void CObj::Update_Rect_Pos()
{
	m_tRect.left -= CCameraMgr::Get_Instance()->m_fDiffX;
	m_tRect.top -= CCameraMgr::Get_Instance()->m_fDiffY;
	m_tRect.right -= CCameraMgr::Get_Instance()->m_fDiffX;
	m_tRect.bottom -= CCameraMgr::Get_Instance()->m_fDiffY;
}

void CObj::Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;

		m_tFrame.dwTime = GetTickCount();
	}

}

