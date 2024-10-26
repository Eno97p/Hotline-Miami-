#include "stdafx.h"
#include "Weapon.h"

CWeapon::CWeapon()
{
}

CWeapon::~CWeapon()
{
	Release();
}

void CWeapon::Initialize()
{
	m_tInfo.fCX = 61;
	m_tInfo.fCY = 61;
	m_pFrameKey = L"Weapon";
}

int CWeapon::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CWeapon::Late_Update()
{

}

void CWeapon::Render(HDC hDC)
{

}

void CWeapon::Release()
{

}

void CWeapon::Change_ImageKey()
{
	if (m_bWeaponIntersect)
	{
		m_pFrameKey = L"Weapon_Intersect";
	}
	else
	{
		m_pFrameKey = L"Weapon";
	}
}
