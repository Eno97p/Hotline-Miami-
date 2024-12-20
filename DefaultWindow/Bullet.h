#pragma once
#include "Obj.h"
class CBullet :	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update();
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	
private :
	
	float	m_fBulletAngle;
	float	m_fPlayerwidth;
	float 	m_fPlayerheight;
	float	g_fVolume;

};

