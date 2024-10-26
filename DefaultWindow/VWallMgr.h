#pragma once
#include "Obj.h"
class VWallMgr
{
private:
	VWallMgr();
	~VWallMgr();
public :
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();
	void		Picking(float _x, float _y, int _iDrawID, int _iOption);
	void		Save_V();
	void		Save_V2();
	void		Save_V3();
	void		Save_V4();
	void		Save_V5();
	void		Save_VT();
	void		Load_VT();
	void		Load_V();
	void		Load_V2();
	void		Load_V3();
	void		Load_V4();
	void		Load_V5();

	vector<CObj*>		Get_vector() { return m_vecWallVV; }
public:
	static	VWallMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new VWallMgr;
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
	static VWallMgr* m_pInstance;
	vector<CObj*>		m_vecWallVV;


};

