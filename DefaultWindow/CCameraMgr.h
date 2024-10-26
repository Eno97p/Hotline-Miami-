#pragma once

class CObj;

class CCameraMgr
{
private:
	CObj* m_pTarget;

public :
	static CCameraMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CCameraMgr;
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
	void	Initialize();
	void	Update();
	void	Set_Target(CObj* _target) { m_pTarget = _target; }
	float m_PosX;	//카메라가 바라볼 좌표 정 중앙
	float m_PosY;

	float m_RLSX;	//현재 클라이언트 창의 크기
	float m_RLSY;

	float m_fDiffX;
	float m_fDiffY;
private :
	static CCameraMgr* m_pInstance;
private:
	CCameraMgr();
	~CCameraMgr();
};

