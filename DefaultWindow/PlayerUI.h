#pragma once
#include "Obj.h"
class CPlayerUI :
    public CObj
{
    // CObj을(를) 통해 상속됨
public:
    CPlayerUI();
    virtual~CPlayerUI();

    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Set_UIClip(int _iClip, int _iMxClip);
    void WeaponState_Output(WEAPONSTATE _Weaponstate);

private:
    int		iClip;
    int		iMxClip;
    HFONT   hFont;
    HFONT   hOldFont;
    bool    m_bIsGun;
    RECT    mxClip;
    RECT    Slash;
};

