#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{

public:
	CMonster();
	virtual ~CMonster();
public:

	/*enum MONSTERSTATE {IDLE,WALK,ATTACK,DEAD,PATROLL,MS_END};*/
	enum DETECT { UNDETECT,ISDETECT,DEND};
	enum MOSTERMOVE {UNMOVE,MOVE,PATRL,MV_END};

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	void Caculate_PlayerTargetAngle();
	void Weapon_Check();
	void Motion_Change();
	void Initializing_Blood();
	void Drop_Weapon();
	void Detect_Delay();
	void Player_Chase();
	void Set_DEAD_State();
	void Patroll();
	void Set_MONSTERSTATE(MONSTERSTATE _data) { m_eCurState = _data; }

	void			Move_LegFrame();
	void			Move_MotionChange();

	bool IS_MONSTERDEAD() { 
		if (m_eCurState == DEAD)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
protected:
	
	MONSTERSTATE			m_ePreState;
	MONSTERSTATE			m_eCurState;

	float m_fWidth;
	float m_fHeight;
	float m_fDiagonal;
	float m_fTargetAngle;
	TCHAR* m_PngKey;
	RECT m_rDetect;
	RECT m_rCloseRange;
	bool m_bActive;
	bool isGunLoaded;
	float m_fBulletAngle;
	POINT				m_tPosin;
	float				m_Posinlength;
	float		g_fVolume;
	
	DETECT curdetect;
	DETECT predetect;
	float m_DetectTic;

	FRAME				m_Leg;
	MOSTERMOVE 			m_ePreMove;
	MOSTERMOVE		    m_eCurMove;
	TCHAR* LegKey;
	float m_fPatrollspeed;
};

