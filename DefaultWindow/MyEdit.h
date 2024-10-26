#pragma once
#include "Scene.h"

class CObj;
class CMyEdit :	public CScene
{
	
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	virtual void	Initialize(void);
	virtual void	Update();
	virtual void	Late_Update();
	virtual void	Render(HDC hDC);
	virtual void	Release();

private:
	void		Key_Input();
	int			m_xInput;
	int			m_yInput;
	int		    Walltype_Switch;
	DWORD				m_dwTime = GetTickCount();
	float		m_fSpeed;
	CObj*		 mssss;
	bool		m_tilmode;


};

