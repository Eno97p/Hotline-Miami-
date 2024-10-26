#pragma once
#include "Weapon.h"
class CKnife :
    public CWeapon
{
public :
    CKnife();
    virtual~CKnife();
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

