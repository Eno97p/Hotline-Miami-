#pragma once
#include "Weapon.h"
class CPipe :
    public CWeapon
{

public :
    CPipe();
    virtual~CPipe();
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

