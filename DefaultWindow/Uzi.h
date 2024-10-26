#pragma once
#include "Weapon.h"
class CUzi :
    public CWeapon
{
public :
    CUzi();
    virtual~CUzi();
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

