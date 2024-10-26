#pragma once
#include "Obj.h"
class MBullet :
    public CObj
{
public:
    MBullet();
    virtual~MBullet();
    // CObj��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private :
    float	m_fBulletAngle;
    float	m_fwidth;
    float 	m_fheight;
    float	g_fVolume;
};

