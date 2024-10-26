#pragma once
#include "Obj.h"
class WallMgr
{


private:
	WallMgr();
	~WallMgr();
public :
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();
	void		Picking(float _x, float _y, int _iDrawID, int _iOption);
	void		Save_H();
	void		Save_H2();
	void		Save_H3();
	void		Save_H4();
	void		Save_H5();
	void		Save_HT();
	void		Load_HT();
	void		Load_H();
	void		Load_H2();
	void		Load_H3();
	void		Load_H4();
	void		Load_H5();

	vector<CObj*>		Get_vector() { return m_vecWall; }
public:
	static	WallMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new WallMgr;
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
	static WallMgr* m_pInstance;
	vector<CObj*>		m_vecWall;
};

