#pragma once
#include "Obj.h"
class CornerMgr
{
private:
	CornerMgr();
	~CornerMgr();
public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();
	void		Picking(float _x, float _y, int _iDrawID, int _iOption);
	void		Save_C();
	void		Save_C2();
	void		Save_C3();
	void		Save_C4();
	void		Save_C5();
	void		Save_CT();
	void		Load_CT();
	void		Load_C();
	void		Load_C2();
	void		Load_C3();
	void		Load_C4();
	void		Load_C5();
public:
	static	CornerMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CornerMgr;
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
	static CornerMgr* m_pInstance;
	vector<CObj*>		m_vecCorner;

};

