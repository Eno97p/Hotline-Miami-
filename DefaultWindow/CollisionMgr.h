#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Rect(list<CObj*> Dst, list<CObj*> Src);
	static void	Collision_Rect(vector<CObj*> Dst, list<CObj*> Src);
	static bool	Collision_Rect(CObj* Dst, list<CObj*> Src);


	static bool Collision_Boss(CObj* Dst, list<CObj*> Src);
	static bool	BOMB_RECT(RECT Dst, list<CObj*> Src);
	static void	BOMB_RECT2(RECT Dst, list<CObj*> Src);
	static void	Collision_Rect(vector<CObj*> Src , CObj* Dst);
	static void	Collision_Rect_Melee(CObj* Dst, list<CObj*> Src);
	static bool Monster_Attack_to_Player(CObj* Monster, CObj* Player);

	static bool	Collision_Weapon_to_Player(/*list<CObj*>*/CObj* Player, list<CObj*> Src);
	static void	Collision_Weapon_Erase(/*list<CObj*>*/CObj* Player, list<CObj*> Src);
	static void	Collision_CloseAttack(/*list<CObj*>*/CObj* Player, list<CObj*> Src);
	static void	Collision_RectEx(list<CObj*> obj, vector<CObj*> wall);
	static void	Collision_RectEx(CObj* player, vector<CObj*> wall);
	static bool	Collision_Rect_Patroll(CObj* Monster, vector<CObj*> wall);


	static bool Check_Rect(float* pX, float* pY, CObj* pDst, CObj* pSrc);

	static bool	Collision_Sphere(CObj* Dst, list<CObj*> Src);
	static bool Check_Sphere(CObj* pDst, CObj* pSrc);

};


