#pragma once
#include "Weapon.h"
class CBat :
    public CWeapon
{
public :
    CBat();
    virtual~CBat();
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

