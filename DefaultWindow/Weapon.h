#pragma once
#include "Obj.h"
class CWeapon :
    public CObj
{
public :

    CWeapon();
    virtual ~CWeapon();

    // CObj��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Change_ImageKey();

};

