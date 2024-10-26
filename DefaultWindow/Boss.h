#pragma once
#include "Monster.h"
class CBoss :
    public CMonster
{
private:
	CBoss();
	~CBoss();
public :
	
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	void Motion_Change();
	void Set_CutScene(bool _bool);
	CObj* Get_Boss() { return this; }
	void Minus_HP() { --iHP; }
	bool Get_GROGGY();
	void Set_Boss_Dead() { m_eBCurState = DEAD; }
	bool Get_Boss_Dead();

private :
	
	enum BOSSSTATE{ IDLE, PUNCH, HIT_DELAY, GROGGY, DEAD,STATE_END};
	BOSSSTATE m_eBPreState;
	BOSSSTATE m_eBCurState;
	bool	m_bCutScene;
	int     iHP;
	float	HitTic;
	bool	HitDelay;

public:
	static	CBoss* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CBoss;

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
	static CBoss* m_pInstance;

};

