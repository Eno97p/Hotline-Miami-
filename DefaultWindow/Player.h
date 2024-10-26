#pragma once

#include "Obj.h"
#include "Shield.h"
#include "PngMrg.h"
class CPlayer :	public CObj
{
	enum PLAYERSTATE { IDLE, WALK, ATTACK, SHOOT, DEAD, PS_END };
	enum MOVESTATE { UNMOVE,MOVE,MV_END};

private:
	CPlayer();
	virtual ~CPlayer();


public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
	void			Weapon_Check();
	void			Melee_Weapon();
	void			Player_Die();
	
	void			Move_LegFrame();
	void			Move_MotionChange();

	int Get_Clip() { return iClip; }
	int Get_MaxClip() { return iMxClip; }

	void Set_Clip(int _Clip, int _MaxClip);
	
	CObj* Get_Player() { return this; }
	bool		Get_State() { 
		if (m_eCurState == DEAD)
		{
			return true;
		}
		else
		{
			return false;
		}
	 }
	WEAPONSTATE Get_Using_Weapon() { return m_CurWeapon; }
	/*WEAPONSTATE Get_Real_Weapon_State() { return m_eWeaponState; }*/
	void	Set_NOMOVE(bool _move) { NOMOVE = _move; }

	void	Set_UI(WEAPONSTATE _m_CurWeapon);

private:
	void		Key_Input();

	
	void		Motion_Change();
private:
	POINT				m_tPosin;

	float				m_fDiagonal;
	
	bool				m_bJump;
	float				m_fPower;
	float				m_fAccelTime;

	PLAYERSTATE			m_ePreState;
	PLAYERSTATE			m_eCurState;

	MOVESTATE			m_ePreMove;
	MOVESTATE			m_eCurMove;
	bool				m_bStretch;
	DWORD				m_dwTime = GetTickCount();

	float rotationAngle;
	
	
	float m_fPlayerwidth;
	float m_fPlayerheight;
	float m_fPlayerDiagonal;
	float m_fPlayerAngle;

	TCHAR* m_PngKey;
	
	WEAPONSTATE			m_CurWeapon;
	bool				m_bWeaponChange;
	bool				NOMOVE;

	FRAME				m_Leg;
	
	int		iClip;
	int		iMxClip;


public:
	static	CPlayer* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CPlayer;

		return m_pInstance;
	}

	static void			Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CPlayer* m_pInstance;

};

// 포물선 공식을 이용하여 플레이어가 점프하는 상태를 만들어라

// Y = 파워 * sin(θ) * 시간 - 중력(9.8f) * 시간의 제곱 / 2

