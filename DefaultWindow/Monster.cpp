#include "stdafx.h"
#include "Monster.h"
#include "BmpMgr.h"

#include "KeyMgr.h"
#include "ObjMgr.h"
#include "PngMrg.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "MBullet.h"
#include "CollisionMgr.h"
#include "Blood.h"
#include "Pipe.h"
#include "Bat.h"
#include "Uzi.h"
#include "ShotGun.h"
#include "SoundMgr.h"
#include "Player.h"
#include "ScorMgr.h"
#include "VWallMgr.h"
#include "WallMgr.h"


CMonster::CMonster() : m_fWidth(0.f), m_fHeight(0.f), m_fDiagonal(0.f), m_fTargetAngle(0.f), m_PngKey(nullptr), m_bActive(false)
, m_ePreState(MS_END), m_eCurState(IDLE), m_Posinlength(20.f),
curdetect(UNDETECT), predetect(UNDETECT), m_DetectTic(0.0f), g_fVolume(1.f), m_eCurMove(UNMOVE), m_ePreMove(MV_END), LegKey(nullptr),
isGunLoaded(true), m_fPatrollspeed(0.f)
{
	ZeroMemory(&m_rDetect, sizeof(RECT));
	ZeroMemory(&m_rCloseRange, sizeof(RECT));
	ZeroMemory(&m_tPosin, sizeof(POINT));
	ZeroMemory(&m_Leg, sizeof(FRAME));
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	Set_Target(CPlayer::Get_Instance()->Get_Player());
	m_PngKey = L"Mafia";
	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster.bmp", L"Monster");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Plg.bmp", L"Plg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Reset.bmp", L"Reset");*/

	m_fSpeed = 6.f;
	m_fPatrollspeed = 2.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 50;

	m_Leg.iFrameStart = 0;
	m_Leg.iFrameEnd = 0;
	m_Leg.iMotion = 0;
	m_Leg.dwTime = GetTickCount();
	m_Leg.dwSpeed = 50;
	LegKey = L"MafiaLeg";
	m_eRender = GAMEOBJECT;
	
}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	


	if (m_eCurState != DEAD && static_cast<CPlayer*>(m_pTarget)->Get_State() == false)
	{
		m_rDetect = { m_tRect.left - 100, m_tRect.top - 100, m_tRect.right + 100, m_tRect.bottom + 100 };
		m_rCloseRange = { m_tRect.left - 10,m_tRect.top - 10,m_tRect.right + 10,m_tRect.bottom + 10 };
		RECT rc{};
		if (IntersectRect(&rc, &(m_pTarget->Get_Rect()), &(m_rDetect)))
		{
			curdetect = ISDETECT;
			Detect_Delay();
			if (m_DetectTic + 500 < GetTickCount())
			{
				m_bActive = true;
			}
		}
		else
		{
			m_bActive = false;
			curdetect = UNDETECT;
			if (static_cast<CPlayer*>(m_pTarget)->Get_State() == true)
			{
				m_eCurState = PATROLL;
			}
		}
		
		if (m_bActive)
		{
			Caculate_PlayerTargetAngle();
			RECT re{};
			/*m_fAngle = m_fTargetAngle;*/
			/*m_fAngle = m_fTargetAngle + 180.f;*/

			switch (m_eWeaponState)
			{
			case UZI:
				m_eCurState = ATTACK;
				Player_Chase();
				if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
				{
					CObjMgr::Get_Instance()->Add_Object(MBULLET, CAbstractFactory<MBullet>::Create((float)m_tPosin.x,
						(float)m_tPosin.y,
						m_fBulletAngle,this));
				}
				break;
			case SHOTGUN:
				m_eCurState = ATTACK;
				Player_Chase();
				if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && isGunLoaded)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"ShotGun.wav", SOUND_EFFECT, g_fVolume);
					CObjMgr::Get_Instance()->Add_Object(MBULLET, CAbstractFactory<MBullet>::Create((float)m_tPosin.x,
						(float)m_tPosin.y,
						m_fBulletAngle, this));
					CObjMgr::Get_Instance()->Add_Object(MBULLET, CAbstractFactory<MBullet>::Create((float)m_tPosin.x,
						(float)m_tPosin.y,
						m_fBulletAngle-1.f, this));
					CObjMgr::Get_Instance()->Add_Object(MBULLET, CAbstractFactory<MBullet>::Create((float)m_tPosin.x,
						(float)m_tPosin.y,
						m_fBulletAngle+1.f, this));
					CObjMgr::Get_Instance()->Add_Object(MBULLET, CAbstractFactory<MBullet>::Create((float)m_tPosin.x,
						(float)m_tPosin.y,
						m_fBulletAngle-2.f, this));
					CObjMgr::Get_Instance()->Add_Object(MBULLET, CAbstractFactory<MBullet>::Create((float)m_tPosin.x,
						(float)m_tPosin.y,
						m_fBulletAngle+2.f, this));
					isGunLoaded = false;
				}
				if (m_tFrame.iFrameStart == 0)
				{
					isGunLoaded = true;
				}
				break;
			case BAT:
				Player_Chase();
				if (IntersectRect(&re, &(m_pTarget->Get_Rect()), &(m_rCloseRange)))
				{
					m_eCurState = ATTACK;
					if (4 <= m_tFrame.iFrameStart && m_tFrame.iFrameStart <= 6)
					{
						CCollisionMgr::Monster_Attack_to_Player(this, m_pTarget);
					}
				}
				break;
			case PIPE:
				Player_Chase();
				if (IntersectRect(&re, &(m_pTarget->Get_Rect()), &(m_rCloseRange)))
				{
					m_eCurState = ATTACK;
					if (5 <= m_tFrame.iFrameStart && m_tFrame.iFrameStart <= 7)
					{
						CCollisionMgr::Monster_Attack_to_Player(this, m_pTarget);
				
					}
				}
				break;
			}

		}
	}
	Patroll();
	__super::Update_Rect();
	__super::Update_Rect_Pos();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	int RenderX = m_tInfo.fX - CCameraMgr::Get_Instance()->m_fDiffX;
	int RenderY = m_tInfo.fY - CCameraMgr::Get_Instance()->m_fDiffY;

	m_tPosin.x = LONG(RenderX + m_Posinlength * cos(m_fBulletAngle * (PI / 180.f)));
	if (m_fHeight < 0)
	{
		m_tPosin.y = LONG(RenderY - m_Posinlength * sin(m_fBulletAngle * (PI / 180.f)));
	}
	else
	{
		m_tPosin.y = LONG(RenderY + m_Posinlength * sin(m_fBulletAngle * (PI / 180.f)));
	}

	if (m_eCurState != DEAD && CCollisionMgr::Collision_Rect(this, CObjMgr::Get_Instance()->Get_List(BULLET)))
	{
		Initializing_Blood();
		m_eCurState = DEAD;
		ScorMgr::Get_Instance()->Plus_BulletKill();
	}
	if (m_eCurState != DEAD)
	{
		Move_LegFrame();
		Move_MotionChange();
		if (static_cast<CPlayer*>(m_pTarget)->Get_State() == true && m_eCurState != PATROLL )
		{
			m_eCurMove = UNMOVE;
			m_eCurState = IDLE;
		}
	}

	Weapon_Check();
	Motion_Change();

	Move_Frame();
}

void CMonster::Render(HDC hDC)
{
	int RenderX = m_tInfo.fX - CCameraMgr::Get_Instance()->m_fDiffX;
	int RenderY = m_tInfo.fY - CCameraMgr::Get_Instance()->m_fDiffY;
	

	Graphics graphics(hDC);						//이미지 회전 및 출력을 위한 그래픽스 선언
	graphics.TranslateTransform(RenderX, RenderY);  //행렬 회전함수
	if (m_bActive)
	{
		graphics.RotateTransform(m_fTargetAngle);
	}
	else
	{
		graphics.RotateTransform(m_fAngle);
	}
	graphics.TranslateTransform(-RenderX, -RenderY);

	if (m_eCurState != DEAD)
	{
		graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(LegKey),
			m_tRect.left-2, m_tRect.top-2,
			m_Leg.iFrameStart * 32, 0,
			32, 32,
			UnitPixel);
	}
	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(m_PngKey), //그려야 할 이미지 (스프라이트 시트)
		m_tRect.left, m_tRect.top,					//그리기 시작할 위치
		(INT)(m_tFrame.iMotion * m_tInfo.fCX), (INT)(m_tFrame.iFrameStart * m_tInfo.fCX),					//이미지의 어디서부터 그릴지
		(INT)m_tInfo.fCX, (INT)m_tInfo.fCY,				//이미지의 어디까지 그릴지
		UnitPixel);

	/*MoveToEx(hDC, (int)RenderX, (int)RenderY, nullptr);
	LineTo(hDC, m_tPosin.x, m_tPosin.y);*/
	
	

	//PlgBlt(hPlgDC,				// 회전 시킬 이미지를 어디에 그릴 것인지 설정한다.
	//		m_tPoint,			// 그림을 그릴 사각형의 좌표 포인터 변수 3개, 즉 배열을 전달한다.
	//		hMemDC,				// 어디에 있는 이미지를 그릴 것인지 설정
	//		0, 0,				// 그림을 그릴 이미지의 X,Y 시작 좌표
	//		(int)m_tInfo.fCX,	// 그림을 그릴 이미지의 가로, 세로 길이
	//		(int)m_tInfo.fCY,
	//		NULL,
	//		NULL,
	//		NULL);

	

}

void CMonster::Release()
{
}

void CMonster::Caculate_PlayerTargetAngle()
{
	int RenderX = m_tInfo.fX - CCameraMgr::Get_Instance()->m_fDiffX;
	int RenderY = m_tInfo.fY - CCameraMgr::Get_Instance()->m_fDiffY;

	m_fWidth = m_pTarget->Get_Info().fX - CCameraMgr::Get_Instance()->m_fDiffX - RenderX; // 타깃과의 밑변
	m_fHeight = m_pTarget->Get_Info().fY - CCameraMgr::Get_Instance()->m_fDiffY - RenderY;	//타깃과의 높이 
	m_fDiagonal = sqrt(m_fWidth * m_fWidth + m_fHeight * m_fHeight); //타깃과의 빗변
	m_fTargetAngle = atan2(m_fHeight, m_fWidth) * (180.0f / PI);  //아크탄젠트 공식(그냥쓰셈)
	if (m_fTargetAngle < 0.0f) {					//아크탄젠트 치역 계산
		m_fTargetAngle += 360.0f;
	}

	/*m_fAngle = acos(m_fPlayerwidth / m_fPlayerDiagonal) * 180 / PI;*/
	/*m_fTargetAngle += 180.f;*/
	m_fBulletAngle = acos(m_fWidth / m_fDiagonal) * 180 / PI;
	/*m_fBulletAngle = m_fTargetAngle - 180.f;*/
	/*if (m_pTarget->Get_Info().fY - CCameraMgr::Get_Instance()->m_fDiffY > m_tInfo.fY - CCameraMgr::Get_Instance()->m_fDiffY)
	{
		m_fBulletAngle *= -1.f;
	}*/

}

void CMonster::Weapon_Check()
{
	/*{ UNARMED, PIPE, BAT, KNIFE, UZI, SHOTGUN, WP_END };*/
	switch (m_eWeaponState)
	{
	case UZI:
		m_tFrame.iMotion = 0;
		break;
	case SHOTGUN:
		m_tFrame.iMotion = 1;
		break;
	case BAT:
		m_tFrame.iMotion = 2;
		break;
	case PIPE:
		m_tFrame.iMotion = 3;
		break;
	}
}

void CMonster::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK :
			m_tFrame.iFrameStart = 0;
			switch (m_eWeaponState)
			{
			case UZI:
				/*m_rCloseRange = m_rDetect;*/
				m_tFrame.iFrameEnd = 1;
				m_tFrame.dwSpeed = 50;
				break;
			case SHOTGUN :
				/*m_rCloseRange = m_rDetect;*/
				m_tFrame.iFrameEnd = 2;
				m_tFrame.dwSpeed = 250;
				break;
			case BAT:
				m_tFrame.iFrameEnd = 7;
				m_tFrame.dwSpeed = 50;
				break;
			case PIPE:
				m_tFrame.iFrameEnd = 8;
				m_tFrame.dwSpeed = 50;
				break;
			}
			m_tFrame.dwTime = GetTickCount();
			break;

		case PATROLL:
			m_eCurMove = MOVE;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_eCurMove = PATRL;
			break;
		case DEAD :
			m_tInfo.fCX = 50.f;
			m_tInfo.fCY = 50.f;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_PngKey = L"Mafia_Hit";
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CMonster::Initializing_Blood()
{
	if (m_eCurState != DEAD)
	{
		Drop_Weapon();
		srand(unsigned(time(NULL)));
		CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CBlood>::Create(m_tInfo.fX + rand() % 30, m_tInfo.fY + rand() % 30, 0));
		CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CBlood>::Create(m_tInfo.fX - rand() % 30, m_tInfo.fY - rand() % 30, 0));
		CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CBlood>::Create(m_tInfo.fX + rand() % 30, m_tInfo.fY - rand() % 30, 0));
		CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CBlood>::Create(m_tInfo.fX - rand() % 30, m_tInfo.fY + rand() % 30, 0));

	}
}

void CMonster::Drop_Weapon()
{
	if (m_eWeaponState != UNARMED)
	{
		switch (m_eWeaponState)
		{
		case PIPE:
			CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CPipe>::Create(m_tInfo.fX, m_tInfo.fY, rand() % 360));
			break;
		case BAT:
			CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CBat>::Create(m_tInfo.fX, m_tInfo.fY, rand() % 360));
			break;
		case UZI:
			CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CUzi>::Create(m_tInfo.fX, m_tInfo.fY, rand() % 360));
			break;
		case SHOTGUN:
			CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CShotGun>::Create(m_tInfo.fX, m_tInfo.fY, rand() % 360));
			break;
		}
	}
}

void CMonster::Detect_Delay()
{
	/*if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)*/

	if(predetect != curdetect )
	{
		switch (curdetect)
		{
		case ISDETECT :
			m_DetectTic = GetTickCount();
			break;
		case UNDETECT :
			break;
		}

		predetect = curdetect;
	}
}

void CMonster::Player_Chase()
{
	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		m_tInfo.fY += m_fSpeed;
	else if (m_pTarget->Get_Info().fY < m_tInfo.fY)
		m_tInfo.fY -= m_fSpeed;

	if (m_pTarget->Get_Info().fX > m_tInfo.fX)
		m_tInfo.fX += m_fSpeed;
	else if (m_pTarget->Get_Info().fX < m_tInfo.fX)
		m_tInfo.fX -= m_fSpeed;
	CCollisionMgr::Collision_RectEx(this, VWallMgr::Get_Instance()->Get_vector());
	CCollisionMgr::Collision_RectEx(this, WallMgr::Get_Instance()->Get_vector());
	m_eCurMove = MOVE;
}

void CMonster::Set_DEAD_State()
{
	if (m_eCurState != DEAD)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"sndHit1.wav", SOUND_EFFECT, g_fVolume);
		ScorMgr::Get_Instance()->Plus_MeleeKill();
	}
	Initializing_Blood();

	m_eCurState = DEAD;
}

void CMonster::Patroll()
{
	if (m_eCurState == PATROLL)
	{
		if (CCollisionMgr::Collision_Rect_Patroll(this, VWallMgr::Get_Instance()->Get_vector()) ||
			CCollisionMgr::Collision_Rect_Patroll(this, WallMgr::Get_Instance()->Get_vector()))
		{
			m_fAngle = rand() % 360;
		}
		
		/*m_fPatrollspeed*/
		m_tInfo.fX += m_fPatrollspeed * cos(m_fAngle * (PI / 180.f));
		m_tInfo.fY += m_fPatrollspeed * sin(m_fAngle * (PI / 180.f));
		
	}
}

void CMonster::Move_LegFrame()
{
	if (m_Leg.dwSpeed + m_Leg.dwTime < GetTickCount())
	{
		++m_Leg.iFrameStart;

		if (m_Leg.iFrameStart > m_Leg.iFrameEnd)
			m_Leg.iFrameStart = 0;

		m_Leg.dwTime = GetTickCount();
	}

}

void CMonster::Move_MotionChange()
{
	if (m_ePreMove != m_eCurMove)
	{
		switch (m_eCurMove)
		{
		case UNMOVE:
			m_Leg.iFrameStart = 0;
			m_Leg.iFrameEnd = 0;
			m_Leg.dwSpeed = 50;
			m_Leg.dwTime = GetTickCount();
			break;
		case MOVE:
			m_Leg.iFrameStart = 0;
			m_Leg.iFrameEnd = 15;
			m_Leg.dwSpeed = 20;
			m_Leg.dwTime = GetTickCount();
			break;
		case PATRL:
			m_Leg.iFrameStart = 0;
			m_Leg.iFrameEnd = 15;
			m_Leg.dwSpeed = 50;
			m_Leg.dwTime = GetTickCount();
			break;
		}
		m_ePreMove = m_eCurMove;
	}
}
