#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, float _fAngle)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		return pObj;
	}

	static CObj*		 Create(float _fX, float _fY, float _fAngle ,CObj* pTarget)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Set_Target(pTarget);
		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fAngle, WEAPONSTATE _weaponstate)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Set_WeaponState(_weaponstate);
		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fAngle, WEAPONSTATE _weaponstate , MONSTERSTATE _monsterstate)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Set_WeaponState(_weaponstate);
		static_cast<CMonster*>(pObj)->Set_MONSTERSTATE(_monsterstate);
		return pObj;
	}

	static CObj*		Create(CObj* pTarget)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Target(pTarget);

		return pObj;
	}

public:
	CAbstractFactory(){}
	~CAbstractFactory(){}
};

