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
	float m_PosX;	//ī�޶� �ٶ� ��ǥ �� �߾�
	float m_PosY;

	float m_RLSX;	//���� Ŭ���̾�Ʈ â�� ũ��
	float m_RLSY;

	float m_fDiffX;
	float m_fDiffY;
private :
	static CCameraMgr* m_pInstance;
private:
	CCameraMgr();
	~CCameraMgr();
};

