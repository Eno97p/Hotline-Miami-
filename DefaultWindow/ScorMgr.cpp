#include "stdafx.h"
#include "ScorMgr.h"
ScorMgr* ScorMgr::m_pInstance = nullptr;

ScorMgr::ScorMgr() : m_iTotalScore(0), m_iPlayerDeadCount(0), m_fPlayTime(0.f),
m_tRank(nullptr),m_MeleeKill(0), m_BulletKill(0), m_iMin(0), m_iSec(0), m_SwapWeapon(0)
{					 																			
}

ScorMgr::~ScorMgr()
{
	Release();
}

void ScorMgr::Initialize()
{
	
}

void ScorMgr::Update()
{

}

void ScorMgr::Render(HDC hDC)
{

}

void ScorMgr::Release()
{

}

void ScorMgr::TotalScore_Calc()
{
	float fTotalTime = GetTickCount() - m_fPlayTime;
	fTotalTime = fTotalTime / 1000;
	m_iMin = (int)fTotalTime / 60;
	m_iSec = (int)fTotalTime % 60;
	m_iTotalScore += m_SwapWeapon * 50;
	m_iTotalScore += m_MeleeKill * 300;
	m_iTotalScore += m_BulletKill * 150;

	if (m_iMin < 2)
	{
		m_iTotalScore += 4000;
	}
	else if (2 < m_iMin && m_iMin < 3)
	{
		m_iTotalScore += 2000;
	}
	else if (3 < m_iMin && m_iMin < 4)
	{
		m_iTotalScore += 1000;
	}
	else
	{
		m_iTotalScore += 500;
	}
	m_iTotalScore -= m_iPlayerDeadCount * 1000;
}


