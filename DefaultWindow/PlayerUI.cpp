#include "stdafx.h"
#include "PlayerUI.h"
#include "Player.h"
#include <string>

CPlayerUI::CPlayerUI() :iClip(0), iMxClip(0), m_bIsGun(false)
{
    ZeroMemory(&Slash, sizeof(RECT));
    ZeroMemory(&mxClip, sizeof(RECT));
}

CPlayerUI::~CPlayerUI()
{
    m_pTarget = nullptr;
}

void CPlayerUI::Initialize()
{
    Set_Target(CPlayer::Get_Instance()->Get_Player());

    m_tInfo.fX = 80.f;
    m_tInfo.fY = 50.f;
    m_tInfo.fCX = 120.f;
    m_tInfo.fCY = 50.f;

    hFont = CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Tahoma");
}

int CPlayerUI::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    Set_UIClip(static_cast<CPlayer*>(m_pTarget)->Get_Clip(), static_cast<CPlayer*>(m_pTarget)->Get_MaxClip());
    Set_WeaponState(static_cast<CPlayer*>(m_pTarget)->Get_Using_Weapon());
    WeaponState_Output(m_eWeaponState);

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CPlayerUI::Late_Update()
{
}

void CPlayerUI::Render(HDC hDC)
{
    mxClip = { m_tRect.right - 30, m_tRect.top, m_tRect.right + 40, m_tRect.bottom };
    Slash = { m_tRect.right - 30,m_tRect.top,m_tRect.right - 20,  m_tRect.bottom };
    hOldFont = (HFONT)SelectObject(hDC, hFont);
    /*Graphics graphic(hDC);*/
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 255, 255));
    if (m_bIsGun)
    {
        wstring wsClip = to_wstring(iClip);
        wstring wsMxClip = to_wstring(iMxClip);

        DrawText(hDC, wsClip.c_str(), -1, &m_tRect, DT_CENTER | DT_VCENTER);
        DrawText(hDC, TEXT("/"), -1, &Slash, DT_CENTER | DT_VCENTER);
        DrawText(hDC, wsMxClip.c_str(), -1, &mxClip, DT_CENTER | DT_VCENTER);
    }
    else
    {
        DrawText(hDC, TEXT("NO GUN!"), -1, &m_tRect, DT_CENTER | DT_VCENTER);
    }



    /*if (hFont) {
        SelectObject(hDC, hOldFont);
        DeleteObject(hFont);
    }*/
}

void CPlayerUI::Release()
{
}

void CPlayerUI::Set_UIClip(int _iClip, int _iMxClip)
{
    iClip = _iClip;
    iMxClip = _iMxClip;
}

void CPlayerUI::WeaponState_Output(WEAPONSTATE _Weaponstate)
{
    switch (_Weaponstate)
    {
    case UZI:
        m_bIsGun = true;
        break;
    case SHOTGUN:
        m_bIsGun = true;
        break;
    default:
        m_bIsGun = false;
        break;
    }
}
