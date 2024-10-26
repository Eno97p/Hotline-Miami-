#include "stdafx.h"
#include "ScoreBoard.h"
#include "ScorMgr.h"
#include "BmpMgr.h"
#include "CCameraMgr.h"
#include "SoundMgr.h"
#include <string>
CScoreBoard::CScoreBoard():PreScore(SCORE_END), CurScore(MINSCORE), ScoreTic(0.f), iFrame(0),
m_iTotalScore(0), m_iPlayerDeadCount(0), m_MeleeKill(0), m_BulletKill(0), m_iMin(0), m_iSec(0),
m_SwapWeapon(0), m_fVVol(0.5f)
{
	CSoundMgr::Get_Instance()->StopAll();
	ZeroMemory(&MeleeKill, sizeof(RECT));
	ZeroMemory(&BulletKill, sizeof(RECT));
	ZeroMemory(&Min, sizeof(RECT));
	ZeroMemory(&Sec, sizeof(RECT));
	ZeroMemory(&SwapWeapon, sizeof(RECT));
	ZeroMemory(&Rank, sizeof(RECT)); 
	ZeroMemory(&DEADCOUNT, sizeof(RECT));
	ZeroMemory(&Total, sizeof(RECT));
}

CScoreBoard::~CScoreBoard()
{

}

void CScoreBoard::Initialize()
{
	/*CCameraMgr::Get_Instance()->Initialize();*/
	ScorMgr::Get_Instance()->TotalScore_Calc();




	Min = { 100,50,200,100 };
	Sec = { 200,50,300,100 };
	MeleeKill = { 100,100,200,150 };
	BulletKill = { 100,150,200,200 };
	SwapWeapon = { 100,200,200,250 };
	DEADCOUNT = { 100,250,200,300 };
	Total = { 100,300,200,350 };
	Rank = { 100,350,200,400 };

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"Miami2.ogg", m_fVVol);
}

void CScoreBoard::Update()
{
	SCMotion_Change();
	TimeCalc();
}

void CScoreBoard::Late_Update()
{
}

void CScoreBoard::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"ScoreBoard");
	BitBlt(hDC, 0, 0, 800, 600, hGroundDC, 0, 0, SRCCOPY);

	wstring MIN = to_wstring(m_iMin);
	wstring SEC = to_wstring(m_iSec);
	wstring MK = to_wstring(m_MeleeKill);
	wstring BK = to_wstring(m_BulletKill);
	wstring SWP = to_wstring(m_SwapWeapon);
	wstring DS = to_wstring(m_iPlayerDeadCount);
	wstring TS = to_wstring(m_iTotalScore);
	

	RECT MINS = { Min.left + 50,Min.top,Min.right + 50,Min.bottom };
	RECT SECS = { Sec.left + 50,Sec.top,Sec.right + 50,Sec.bottom };
	RECT MKS = { MeleeKill.left + 100,MeleeKill.top,MeleeKill.right + 100,MeleeKill.bottom };
	RECT BKS = { BulletKill.left + 100,BulletKill.top,BulletKill.right + 100,BulletKill.bottom };
	RECT SWPS = { SwapWeapon.left + 100,SwapWeapon.top,SwapWeapon.right + 100,SwapWeapon.bottom };
	RECT DSS = { DEADCOUNT.left + 100,DEADCOUNT.top,DEADCOUNT.right + 100,DEADCOUNT.bottom };
	RECT TSS = { Total.left + 100,Total.top,Total.right + 100,Total.bottom };
	RECT RKS = { Rank.left + 100,Rank.top,Rank.right + 100,Rank.bottom };
		




	DrawText(hDC, TEXT("분 :"), -1, &Min, DT_CENTER | DT_VCENTER);
	DrawText(hDC, TEXT("초 :"), -1, &Sec, DT_CENTER | DT_VCENTER);
	DrawText(hDC, TEXT("근접킬 :"), -1, &MeleeKill, DT_CENTER | DT_VCENTER);
	DrawText(hDC, TEXT("원거리 :"), -1, &BulletKill, DT_CENTER | DT_VCENTER);
	DrawText(hDC, TEXT("무기교체 :"), -1, &SwapWeapon, DT_CENTER | DT_VCENTER);
	DrawText(hDC, TEXT("죽음 :"), -1, &DEADCOUNT, DT_CENTER | DT_VCENTER);
	DrawText(hDC, TEXT("총 점수 :"), -1, &Total, DT_CENTER | DT_VCENTER);
	DrawText(hDC, TEXT("랭크 :"), -1, &Rank, DT_CENTER | DT_VCENTER);

	DrawText(hDC, MIN.c_str(), -1, &MINS, DT_CENTER | DT_VCENTER);
	DrawText(hDC, SEC.c_str(), -1, &SECS, DT_CENTER | DT_VCENTER);
	DrawText(hDC, MK.c_str(), -1, &MKS, DT_CENTER | DT_VCENTER);
	DrawText(hDC, BK.c_str(), -1, &BKS, DT_CENTER | DT_VCENTER);
	DrawText(hDC, SWP.c_str(), -1, &SWPS, DT_CENTER | DT_VCENTER);
	DrawText(hDC, DS.c_str(), -1, &DSS, DT_CENTER | DT_VCENTER);
	DrawText(hDC, TS.c_str(), -1, &TSS, DT_CENTER | DT_VCENTER);
	if (PreScore == RANK)
	{
		DrawText(hDC, TEXT("B"), -1, &RKS, DT_CENTER | DT_VCENTER);
	}

	
	//DrawText(hDC, wsClip.c_str(), -1, &m_tRect, DT_CENTER | DT_VCENTER);
	//DrawText(hDC, TEXT("/"), -1, &Slash, DT_CENTER | DT_VCENTER);
	//DrawText(hDC, wsMxClip.c_str(), -1, &mxClip, DT_CENTER | DT_VCENTER);
}

void CScoreBoard::Release()
{
}

void CScoreBoard::SCMotion_Change()
{
	/*TIMESCORE, KillSCORE, SWAPSCORE, DEADSCORE, RANK*/
	if (PreScore != CurScore)
	{
		switch (CurScore)
		{
		case MINSCORE:
			ScoreTic = GetTickCount();
			break;
		case SECSCORE:
			ScoreTic = GetTickCount();
			break;
		case MKillSCORE:
			ScoreTic = GetTickCount();
			break;
		case BKillSCORE:
			ScoreTic = GetTickCount();
			break;
		case SWAPSCORE:
			ScoreTic = GetTickCount();
			break;
		case DEADSCORE:
			ScoreTic = GetTickCount();
			break;
		case RANK:
			ScoreTic = GetTickCount();
			break;
		}


		PreScore = CurScore;
	}
}

void CScoreBoard::TimeCalc()
{
	if (PreScore == MINSCORE && m_iMin < ScorMgr::Get_Instance()->Get_Min())
	{
		m_iMin++;
		if (m_iMin == ScorMgr::Get_Instance()->Get_Min())
		{
			CurScore = SECSCORE;
		}
	}
	if (PreScore == SECSCORE && m_iSec < ScorMgr::Get_Instance()->Get_Sec())
	{
		m_iSec++;
		if (m_iSec == ScorMgr::Get_Instance()->Get_Sec())
		{
			CurScore = MKillSCORE;
		}
	}
	if (PreScore == MKillSCORE && m_MeleeKill < ScorMgr::Get_Instance()->Get_Total_MeleeKill())
	{
		m_MeleeKill++;
		if (m_MeleeKill == ScorMgr::Get_Instance()->Get_Total_MeleeKill())
		{
			CurScore = BKillSCORE;
		}
	}
	if (PreScore == BKillSCORE && m_BulletKill < ScorMgr::Get_Instance()->Get_Total_BulletKill())
	{
		m_BulletKill++;
		if (m_BulletKill == ScorMgr::Get_Instance()->Get_Total_BulletKill())
		{
			CurScore = SWAPSCORE;
		}
	}
	if (PreScore == SWAPSCORE && m_SwapWeapon < ScorMgr::Get_Instance()->Get_Swap_Count())
	{
		m_SwapWeapon++;
		if (m_SwapWeapon == ScorMgr::Get_Instance()->Get_Swap_Count())
		{
			CurScore = DEADSCORE;
		}
	}
	if (PreScore == DEADSCORE && m_iPlayerDeadCount < ScorMgr::Get_Instance()->Get_Dead_Count())
	{
		m_iPlayerDeadCount++;
		if (m_iPlayerDeadCount == ScorMgr::Get_Instance()->Get_Dead_Count())
		{
			CurScore = RANK;
		}
	}
	if (PreScore == RANK)
	{
		m_iTotalScore = ScorMgr::Get_Instance()->Get_ToTal_Scores();
	}

}

