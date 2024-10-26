#pragma once
class ScorMgr
{
private:
	ScorMgr();
	~ScorMgr();
public:
	void Initialize();
	void Update();
	void Render(HDC hDC);
	void Release();

public:
	static ScorMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new ScorMgr;
		}
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
public:
	void TotalScore_Calc();
	void Set_DeadCount(){ m_iPlayerDeadCount++; }
	void Set_Timer(){ m_fPlayTime = GetTickCount(); }
	int Get_ToTal_Scores() { return m_iTotalScore; }
	int Get_Total_MeleeKill() { return m_MeleeKill; }
	int Get_Total_BulletKill() { return m_BulletKill; }
	int Get_Min() {return m_iMin;}
	int Get_Sec() { return m_iSec; }
	int Get_Dead_Count() { return m_iPlayerDeadCount; }
	int Get_Swap_Count() { return m_SwapWeapon; }

	void Plus_MeleeKill() { m_MeleeKill++; }
	void Plus_BulletKill() { m_BulletKill++; }
	void Plus_Swap_Weapon() { m_SwapWeapon++; }

private:
	int m_iTotalScore;
	int m_iPlayerDeadCount;
	int m_MeleeKill;
	int m_BulletKill;
	float m_fPlayTime;
	int m_iMin;
	int m_iSec;
	int m_SwapWeapon;
	TCHAR* m_tRank;

private:
	static ScorMgr* m_pInstance;
};

