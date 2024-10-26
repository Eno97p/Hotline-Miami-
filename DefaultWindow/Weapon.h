#pragma once
#include "Obj.h"
class CWeapon :
    public CObj
{
public :

    CWeapon();
    virtual ~CWeapon();

    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Change_ImageKey();

};

