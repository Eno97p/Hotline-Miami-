#pragma once
#include "Weapon.h"
class CShotGun :
    public CWeapon
{
public :
    CShotGun();
    virtual~CShotGun();
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

