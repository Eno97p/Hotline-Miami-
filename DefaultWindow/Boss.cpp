#include "stdafx.h"
#include "Boss.h"
#include "ObjMgr.h"
#include "PngMrg.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "WallMgr.h"
#include "VWallMgr.h"
#include "SoundMgr.h"
CBoss* CBoss::m_pInstance = nullptr;

CBoss::CBoss()  : m_eBCurState(IDLE), m_eBPreState(STATE_END), iHP(0), HitTic(0.f), HitDelay(false), m_bCutScene(true)
{
	ZeroMemory(&m_rDetect, sizeof(RECT));
}

CBoss::~CBoss()
{
	m_pTarget = nullptr;
}

void CBoss::Initialize()
{
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;
	iHP = 30;
	m_bCutScene = true;
	Set_Target(CPlayer::Get_Instance()->Get_Player());
	m_PngKey = L"Boss";
	LegKey = L"BossLeg";
	m_fSpeed = 6.f;
	m_tFrame.iMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount();

	m_Leg.iFrameStart = 0;
	m_Leg.iFrameEnd = 0;
	m_Leg.iMotion = 0;
	m_Leg.dwTime = GetTickCount();
	m_Leg.dwSpeed = 50;

	/*m_bActive = true;*/
	m_eRender = GAMEOBJECT;

}

int CBoss::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	
	if (!m_bCutScene && m_eBPreState != DEAD)
	{
		Caculate_PlayerTargetAngle();
	}

	if (m_eBPreState == HIT_DELAY && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_eBCurState = IDLE;
	}
	__super::Update_Rect();
	__super::Update_Rect_Pos();
	return OBJ_NOEVENT;
}

void CBoss::Late_Update()
{
	m_rDetect = { m_tRect.left - 10, m_tRect.top - 10, m_tRect.right + 10, m_tRect.bottom + 10 };
	RECT rc{};
	if (m_eBPreState != HIT_DELAY && m_eBPreState != DEAD && m_eBPreState != GROGGY &&
		IntersectRect(&rc, &(m_pTarget->Get_Rect()), &(m_rDetect)))
	{
		m_eBCurState = PUNCH;
		if (7 <= m_tFrame.iFrameStart && m_tFrame.iFrameStart <= 10)
		{
			CCollisionMgr::Monster_Attack_to_Player(this, m_pTarget);
		}
	}
	

	if (m_eBPreState != DEAD && m_eBPreState != GROGGY && CCollisionMgr::Collision_Boss(this, CObjMgr::Get_Instance()->Get_List(BULLET)))
	{
		Initializing_Blood();
		m_eBCurState = HIT_DELAY;
		if (iHP <= 0)
		{
			m_eBCurState = GROGGY;
			m_eCurMove = UNMOVE;
		}
	}

	if (m_eBPreState != DEAD && m_eBPreState != GROGGY)
	{
		if (m_bCutScene == false && m_eBPreState != HIT_DELAY && static_cast<CPlayer*>(m_pTarget)->Get_State() == false)
		{
			Player_Chase();
			CCollisionMgr::Collision_RectEx(this, WallMgr::Get_Instance()->Get_vector());
			CCollisionMgr::Collision_RectEx(this, VWallMgr::Get_Instance()->Get_vector());
			Move_LegFrame();
		}
		Move_MotionChange();
		Move_Frame();
		if (static_cast<CPlayer*>(m_pTarget)->Get_State() == true)
		{
			m_eCurMove = UNMOVE;
			m_eBCurState = IDLE;
		}

	}
	Motion_Change();
	
}

void CBoss::Render(HDC hDC)
{
	int RenderX = m_tInfo.fX - CCameraMgr::Get_Instance()->m_fDiffX;
	int RenderY = m_tInfo.fY - CCameraMgr::Get_Instance()->m_fDiffY;

	Graphics graphics(hDC);						//이미지 회전 및 출력을 위한 그래픽스 선언
	graphics.TranslateTransform(RenderX, RenderY);  //행렬 회전함수
	graphics.RotateTransform(m_fTargetAngle);		//회전 함수
	graphics.TranslateTransform(-RenderX, -RenderY);
	if (m_eBPreState != DEAD)
	{
		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(LegKey),
			m_tRect.left + 15, m_tRect.top + 15,
			m_Leg.iFrameStart * 40, 0,
			40, 40,
			UnitPixel);
	}
	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(m_PngKey), //그려야 할 이미지 (스프라이트 시트)
		m_tRect.left, m_tRect.top,					//그리기 시작할 위치
		m_tFrame.iMotion * 70, m_tFrame.iFrameStart * 70,					//이미지의 어디서부터 그릴지
		(INT)m_tInfo.fCX, (INT)m_tInfo.fCY,				//이미지의 어디까지 그릴지
		UnitPixel);
}

void CBoss::Release()
{
}

void CBoss::Motion_Change()
{
	if (m_eBPreState != m_eBCurState)
	{
		switch (m_eBCurState)
		{
		case IDLE :
			m_tFrame.iMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;

		case PUNCH :
			m_tFrame.iMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HIT_DELAY:
			m_tFrame.iMotion = 2;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case GROGGY:
			m_tFrame.iMotion = 3;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_eCurMove = UNMOVE;
			break;

		case DEAD :
			Initializing_Blood();
		
			m_tFrame.iMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			m_PngKey = L"BossDead";
			m_tInfo.fCX = 110;
			m_tInfo.fCY = 80;
			m_eCurMove = UNMOVE;
			break;

		}

		m_eBPreState = m_eBCurState;
	}
}

void CBoss::Set_CutScene(bool _bool)
{
	m_bCutScene = _bool;
}

bool CBoss::Get_GROGGY()
{
	if (m_eBPreState == GROGGY)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CBoss::Get_Boss_Dead()
{
	if (m_eBPreState == DEAD)
	{
		return true;
	}
	else
	{
		return false;
	}
}
