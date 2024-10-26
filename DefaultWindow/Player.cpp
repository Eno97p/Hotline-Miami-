#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"

#include "BmpMgr.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"
#include "Pipe.h"
#include "Bat.h"
#include "Knife.h"
#include "ShotGun.h"
#include "Uzi.h"
#include "Blood.h"
#include "SceneMgr.h"
#include "ScorMgr.h"
#include "WallMgr.h"
#include "VWallMgr.h"
#include "Boss.h"

float		g_fVolume(1.f);
float		g_fBVolume(0.3f);
CPlayer* CPlayer::m_pInstance = nullptr;

CPlayer::CPlayer()  : m_bJump(false), m_fPower(0.f), m_fAccelTime(0.f)
, m_eCurState(IDLE), m_ePreState(PS_END), m_bStretch(false),rotationAngle(0.0f),
m_fPlayerwidth(0), m_fPlayerheight(0), m_fPlayerDiagonal(0), m_fPlayerAngle(0.0f), m_PngKey(nullptr), m_bWeaponChange(false)
, m_CurWeapon(UNARMED) , m_eCurMove(UNMOVE), m_ePreMove(MV_END), NOMOVE(false) , iClip(0), iMxClip(0)
{
	ZeroMemory(&m_tPosin, sizeof(POINT));
	ZeroMemory(&m_Leg, sizeof(FRAME));
	
}

CPlayer::~CPlayer()
{
	Release();
	
}

void CPlayer::Initialize()
{
	m_tInfo.fCX = 40.f; /*= { 100.f, 300.f, 40.f, 40.f };*/
	m_tInfo.fCY = 40.f;
	m_fSpeed = 8.f;
	m_fDiagonal = 2.f;
	m_fPower = 20.f;
	Set_Target(CObjMgr::Get_Instance()->Get_Mouse());
	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/img/Player/sprPlayerLeg.bmp", L"Player_Leg");*/
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




	m_eCurState = IDLE;
	m_eWeaponState = UNARMED;
	m_pFrameKey = L"Player_DOWN";
	m_PngKey = L"PlayerForm";

	m_eRender = GAMEOBJECT;

	

}

int CPlayer::Update()
{
	if (m_eCurState != DEAD && !NOMOVE)
	{
		Key_Input();
		CCollisionMgr::Collision_RectEx(this, VWallMgr::Get_Instance()->Get_vector());
		CCollisionMgr::Collision_RectEx(this, WallMgr::Get_Instance()->Get_vector());
		if (!CCollisionMgr::Collision_Weapon_to_Player(this, CObjMgr::Get_Instance()->Get_List(WEAPON)))
		{
			m_eWeaponState = UNARMED;
		}
	}

	if (CCollisionMgr::Collision_Rect(this, CObjMgr::Get_Instance()->Get_List(MBULLET)))
	{
		Player_Die();
	}
	else if (m_ePreState == DEAD)
	{
		if (GetAsyncKeyState('R'))
		{
			if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE)
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE1RE);
			}
			else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE1RE)
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
			}
			else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE2)
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE2RE);
			}
			else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE2RE)
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE2);
			}
			else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE3)
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE3RE);
			}
			else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE3RE)
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE3);
			}
			else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE4)
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE4RE);
			}
			else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE4RE)
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE4);
			}
			else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE5)
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE5RE);
			}
			else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE5RE)
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE5);
			}
			

		}
	}
	__super::Update_Rect();
	__super::Update_Rect_Pos();
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	if (m_eCurState != DEAD)
	{
		int RenderX = m_tInfo.fX - CCameraMgr::Get_Instance()->m_fDiffX;
		int RenderY = m_tInfo.fY - CCameraMgr::Get_Instance()->m_fDiffY;
		m_fPlayerwidth = m_pTarget->Get_Info().fX - RenderX; // 타깃과의 밑변
		m_fPlayerheight = m_pTarget->Get_Info().fY - RenderY;	//타깃과의 높이 
		m_fPlayerDiagonal = sqrt(m_fPlayerwidth * m_fPlayerwidth + m_fPlayerheight * m_fPlayerheight); //타깃과의 빗변
		m_fPlayerAngle = atan2(m_fPlayerheight, m_fPlayerwidth) * (180.0f / PI);  //아크탄젠트 공식(그냥쓰셈)
		if (m_fPlayerAngle < 0.0f) {					//아크탄젠트 치역 계산
			m_fPlayerAngle += 360.0f;
		}
		m_fAngle = acos(m_fPlayerwidth / m_fPlayerDiagonal) * 180 / PI;
		/*if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		{
			m_fAngle *= -1.f;
		}*/
		m_tPosin.x = LONG(RenderX + m_fDiagonal * cos(m_fAngle * (PI / 180.f)));
	
		if (m_fPlayerheight < 0)
		{
			m_tPosin.y = LONG(RenderY - m_fDiagonal * sin(m_fAngle * (PI / 180.f)));
		}
		else
		{
			m_tPosin.y = LONG(RenderY + m_fDiagonal * sin(m_fAngle * (PI / 180.f)));
		}
		

		/*Offset();*/
		Melee_Weapon();
		Weapon_Check();

		Move_MotionChange();
		Move_LegFrame();
	}
	Motion_Change();
	Move_Frame();
	
	
#/*ifdef _DEBUG

	if (m_dwTime + 1000 < GetTickCount())
	{
		cout << "스크롤 : " << iScrollX << "\t" << iScrollY << endl;
		m_dwTime = GetTickCount();
	}

#endif*/

}

void CPlayer::Render(HDC hDC)
{
	
	int RenderX = m_tInfo.fX - CCameraMgr::Get_Instance()->m_fDiffX;
	int RenderY = m_tInfo.fY - CCameraMgr::Get_Instance()->m_fDiffY;
	

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	MoveToEx(hDC, (int)RenderX, (int)RenderY, nullptr);
	LineTo(hDC, m_tPosin.x, m_tPosin.y);
	//렌더 함수에서 호출
	Graphics graphics(hDC);			
	graphics.TranslateTransform(RenderX, RenderY);  //행렬 회전함수
	graphics.RotateTransform(m_fPlayerAngle);		//회전 함수
	graphics.TranslateTransform(-RenderX, -RenderY); //행렬 회전함수//이미지 회전 및 출력을 위한 그래픽스 선언
	
	//if (m_pFrameKey == L"Player_Leg")
	//{
	//	GdiTransparentBlt(hDC,
	//		m_tRect.left,
	//		m_tRect.top,
	//		(int)m_tInfo.fCX,
	//		(int)m_tInfo.fCY,
	//		hMemDC,
	//		(int)m_tInfo.fCX * m_tFrame.iFrameStart, //소스 그림의 시작 좌표
	//		(int)m_tInfo.fCY * m_tFrame.iMotion,			//소스 그림의 시작 좌표
	//		(int)m_tInfo.fCX,
	//		(int)m_tInfo.fCY,
	//		RGB(0, 0, 255));
	//}
	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"PlayerLeg"),
		m_tRect.left+2, m_tRect.top+2,
		m_Leg.iFrameStart * 32, 0,
		32, 32,
		UnitPixel);
	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(m_PngKey), //그려야 할 이미지 (스프라이트 시트)
		m_tRect.left, m_tRect.top,					//그리기 시작할 위치
		m_tFrame.iMotion * (INT)m_tInfo.fCX, m_tFrame.iFrameStart * (INT)m_tInfo.fCY,					//이미지의 어디서부터 그릴지
			(INT)m_tInfo.fCX, (INT)m_tInfo.fCY,				//이미지의 어디까지 그릴지
			UnitPixel);
	/*L"PlayerLeg"*/
}

void CPlayer::Release()
{
}

void CPlayer::Weapon_Check()
{
	switch (m_CurWeapon)
	{
	case UNARMED :
		m_tFrame.iMotion = 0;
		break;
	case BAT:
		m_tFrame.iMotion = 1;
		break;
	case PIPE:
		m_tFrame.iMotion = 2;
		break;
	case KNIFE:
		m_tFrame.iMotion = 3;
		break;
	case UZI:
		m_tFrame.iMotion = 4;
		break;
	case SHOTGUN:
		m_tFrame.iMotion = 5;
		break;
	}

}

void CPlayer::Melee_Weapon()
{
	if ((m_CurWeapon == BAT || m_CurWeapon == PIPE) && m_eCurState == ATTACK)
	{
		CCollisionMgr::Collision_Rect_Melee(this, CObjMgr::Get_Instance()->Get_List(MONSTER));
	}
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE5 || CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE5RE)
	{
		if (m_CurWeapon == PIPE && m_eCurState == ATTACK)
		{
			CBoss::Get_Instance()->Set_Boss_Dead();
		}
	}

}

void CPlayer::Player_Die()
{
	if (m_eCurState != DEAD)
	{
		srand(unsigned(time(NULL)));
		CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CBlood>::Create(m_tInfo.fX + rand() % 30, m_tInfo.fY + rand() % 30, 0));
		CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CBlood>::Create(m_tInfo.fX - rand() % 30, m_tInfo.fY - rand() % 30, 0));
		CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CBlood>::Create(m_tInfo.fX + rand() % 30, m_tInfo.fY - rand() % 30, 0));
		CObjMgr::Get_Instance()->Add_Object(EFFECTS, CAbstractFactory<CBlood>::Create(m_tInfo.fX - rand() % 30, m_tInfo.fY + rand() % 30, 0));
	}
	m_PngKey = L"PlayerDead";
	/*m_tInfo.fCX = 60;
	m_tInfo.fCY = 50;*/

	m_eCurState = DEAD;
}

void CPlayer::Move_LegFrame()
{
	if (m_Leg.dwSpeed + m_Leg.dwTime < GetTickCount())
	{
		++m_Leg.iFrameStart;

		if (m_Leg.iFrameStart > m_Leg.iFrameEnd)
			m_Leg.iFrameStart = 0;

		m_Leg.dwTime = GetTickCount();
	}
}

void CPlayer::Move_MotionChange()
{
	//m_ePreMove
	//m_eCurMove

	if (m_ePreMove != m_eCurMove)
	{
		switch (m_eCurMove)
		{
		case UNMOVE :
			m_Leg.iFrameStart = 0;
			m_Leg.iFrameEnd = 0;
			m_Leg.dwSpeed = 50;
			m_Leg.dwTime = GetTickCount();
			break;
		case MOVE :
			m_Leg.iFrameStart = 0;
			m_Leg.iFrameEnd = 15;
			m_Leg.dwSpeed = 20;
			m_Leg.dwTime = GetTickCount();
			break;
		}
		m_ePreMove = m_eCurMove;
	}


}

void CPlayer::Set_Clip(int _Clip, int _MaxClip)
{
	iClip = _Clip;
	iMxClip = _MaxClip;
}



void CPlayer::Set_UI(WEAPONSTATE _m_CurWeapon)
{
	/*UNARMED, PIPE, BAT, KNIFE, UZI, SHOTGUN,*/
	switch (_m_CurWeapon)
	{
	case UZI:
		Set_Clip(35, 35);
		break;
	case SHOTGUN:
		Set_Clip(6, 6);
		break;
	default:
		Set_Clip(0, 0);
		break;
	}
}

void CPlayer::Key_Input()
{
	/*else
	{
		m_eCurState = IDLE;
		m_PngKey = L"Player_IDLE";
		m_pFrameKey = nullptr;
	}*/
	if (GetAsyncKeyState('A'))
	{
		m_tInfo.fX -= m_fSpeed;
		m_eCurState = WALK;
		m_eCurMove = MOVE;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		m_tInfo.fX += m_fSpeed;
		m_eCurState = WALK;
		m_eCurMove = MOVE;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
	{
		m_tInfo.fY -= m_fSpeed;
		m_eCurState = WALK;
		m_eCurMove = MOVE;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing('S'))
	{
		m_tInfo.fY += m_fSpeed;
		m_eCurState = WALK;
		m_eCurMove = MOVE;
	}
	if(!CKeyMgr::Get_Instance()->Key_Pressing('A') &&
		!CKeyMgr::Get_Instance()->Key_Pressing('D')&&
		!CKeyMgr::Get_Instance()->Key_Pressing('W')&&
		!CKeyMgr::Get_Instance()->Key_Pressing('S'))
	{
		m_eCurMove = UNMOVE;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		m_eCurState = ATTACK;
		if (m_CurWeapon == UZI && m_tFrame.iFrameStart == 1 && iClip > 0)
		{
			CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle, this));
			--iClip;
		}
		else if (m_CurWeapon == UZI && m_tFrame.iFrameStart == 1 && iClip == 0)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Unload.wav", SOUND_EFFECT, g_fVolume);
		}
		else if (m_CurWeapon == SHOTGUN && m_tFrame.iFrameStart == 1 && iClip == 0)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Unload.wav", SOUND_EFFECT, g_fVolume);
		}
		if (m_CurWeapon == PIPE || m_CurWeapon == BAT)
		{
			if (m_tFrame.iFrameStart == 3)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"sndSwing1.wav", SOUND_EFFECT, g_fVolume);
			}

		}
	}
	if (!CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		m_eCurState = IDLE;
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_RBUTTON))
	{
		
		if (m_CurWeapon != UNARMED)
		{
			switch (m_CurWeapon)
			{
			case PIPE:
				CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CPipe>::Create(m_tInfo.fX, m_tInfo.fY, rand() % 360));
				break;
			case BAT:
				CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CBat>::Create(m_tInfo.fX, m_tInfo.fY, rand() % 360));
				break;
			case KNIFE:
				CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CKnife>::Create(m_tInfo.fX, m_tInfo.fY, rand() % 360));
				break;
			case UZI :
				CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CUzi>::Create(m_tInfo.fX, m_tInfo.fY, rand() % 360));
				break;
			case SHOTGUN :
				CObjMgr::Get_Instance()->Add_Object(WEAPON, CAbstractFactory<CShotGun>::Create(m_tInfo.fX, m_tInfo.fY, rand() % 360));
				break;
			}
		}
		CCollisionMgr::Collision_Weapon_Erase(this, CObjMgr::Get_Instance()->Get_List(WEAPON));
		CSoundMgr::Get_Instance()->PlaySound(L"PickUpWeapon.wav", SOUND_EFFECT, g_fVolume);
		ScorMgr::Get_Instance()->Plus_Swap_Weapon();
		m_CurWeapon = m_eWeaponState;
		//함수 하나 드가자
		Set_UI(m_CurWeapon);
	}

}





void CPlayer::Motion_Change()
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
		case WALK:
			m_tFrame.iFrameStart = 0;
			/*m_tFrame.iFrameEnd = 16;*/
			/*m_tFrame.iMotion = 0;*/
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK :
			m_tFrame.iFrameStart = 0;
			switch (m_CurWeapon)
			{
			case UNARMED :
				m_tFrame.iFrameEnd = 6;
				m_tFrame.dwSpeed = 50;
				break;
			case BAT :
				/*sndSwing1*/
				m_tFrame.iFrameEnd = 5;
				m_tFrame.dwSpeed = 40;
				break;
			case PIPE :
				m_tFrame.iFrameEnd = 8;
				m_tFrame.dwSpeed = 20;
				break;
			case KNIFE :
				m_tFrame.iFrameEnd = 5;
				m_tFrame.dwSpeed = 40;
				break;
			case UZI :
				/*CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle,this));*/
				m_tFrame.iFrameEnd = 1;
				m_tFrame.dwSpeed = 40;
				break;
			case SHOTGUN :
				m_tFrame.iFrameEnd = 2;
				m_tFrame.dwSpeed = 40;
				if (iClip > 0)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"ShotGun.wav", SOUND_EFFECT, g_fBVolume);
					CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle, this));
					CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle + 1.f, this));
					CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle - 1.f, this));
					CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle - 2.f, this));
					CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle + 2.f, this));
					--iClip;
				}
				break;
			}
			m_tFrame.dwTime = GetTickCount();
			break;
		case DEAD:
			CSoundMgr::Get_Instance()->PlaySound(L"sndHit1.wav", SOUND_EFFECT, g_fVolume);
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_tInfo.fCX = 60;
			m_tInfo.fCY = 50;
			ScorMgr::Get_Instance()->Set_DeadCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}


