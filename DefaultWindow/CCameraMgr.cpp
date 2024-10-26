#include "stdafx.h"
#include "CCameraMgr.h"
#include "Define.h"
#include "Obj.h"
#include "KeyMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "Mouse.h"

CCameraMgr* CCameraMgr::m_pInstance = nullptr;

void CCameraMgr::Initialize()
{
	m_RLSX = WINCX;
	m_RLSY = WINCY;
	m_PosX = WINCX / 2;
	m_PosY = WINCY / 2;
	m_pTarget = nullptr;
}

void CCameraMgr::Update()
{
	
	if (GetAsyncKeyState(VK_SHIFT))
	{
		float x = CObjMgr::Get_Instance()->Get_Mouse()->Get_Info().fX + m_fDiffX;
		float y = CObjMgr::Get_Instance()->Get_Mouse()->Get_Info().fY + m_fDiffY;
		m_PosX = x;
		m_PosY = y;
	}
	else
	{
		if (m_pTarget != nullptr)
		{
			m_PosX = m_pTarget->Get_Info().fX;
			m_PosY = m_pTarget->Get_Info().fY;
		}
	}
	
	m_fDiffX = m_PosX - (WINCX / 2);  //Diff°¡ »©Áà¾ß ÇÏ´Â °ª.
	m_fDiffY = m_PosY - (WINCY / 2);

	
}

CCameraMgr::CCameraMgr()
{
	
}

CCameraMgr::~CCameraMgr()
{

}





