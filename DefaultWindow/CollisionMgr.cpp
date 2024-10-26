#include "stdafx.h"
#include "CollisionMgr.h"
#include "Monster.h"
#include "Player.h"
#include "Boss.h"
#include "ScorMgr.h"
CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> Dst, list<CObj*> Src)
{
	// 1���� : ��� ���� ������ ��Ʈ�� �ּ�
	// 2, 3���� : �浹�� ������ ��Ʈ�� �ּ�

	RECT	rc{};

	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (IntersectRect(&rc, &(DstList->Get_Rect()), &(SrcList->Get_Rect())))
			{
				DstList->Set_Dead();
				SrcList->Set_Dead();
			}
		}
	}


}
#pragma optimize("", off)
void CCollisionMgr::Collision_Rect(vector<CObj*> Dst, list<CObj*> Src)
{
	RECT	rc{};

	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (IntersectRect(&rc, &(DstList->Get_Rect()), &(SrcList->Get_Rect())))
			{
				SrcList->Set_Dead();
			}
		}
	}
}
#pragma optimize("", on)

bool CCollisionMgr::Collision_Rect(CObj* Dst, list<CObj*> Src)
{
	RECT	rc{};
	for (auto& SrcList : Src)
	{
		if (IntersectRect(&rc, &(Dst->Get_Rect()), &(SrcList->Get_Rect())))
		{
			SrcList->Set_Dead();
			return true;
		}
	}
	return false;
}

bool CCollisionMgr::Collision_Boss(CObj* Dst, list<CObj*> Src)
{
	RECT	rc{};
	for (auto& SrcList : Src)
	{
		if (IntersectRect(&rc, &(Dst->Get_Rect()), &(SrcList->Get_Rect())))
		{
			SrcList->Set_Dead();
			static_cast<CBoss*>(Dst)->Minus_HP();
			return true;
		}
	}
	return false;
}

void CCollisionMgr::Collision_Rect(vector<CObj*> Src, CObj* Dst)
{
	RECT	rc{};
	for (auto& SrcList : Src)
	{
		if (IntersectRect(&rc, &(Dst->Get_Rect()), &(SrcList->Get_Rect())))
		{
			Dst->Set_Dead();
		}
	}
	
}
bool CCollisionMgr::BOMB_RECT(RECT Dst, list<CObj*> Src)
{
	RECT	rc{};
	for (auto& SrcList : Src)
	{
		if (IntersectRect(&rc, &(Dst), &(SrcList->Get_Rect())))
		{
			SrcList->Set_Dead();
			return true;
		}
	}
	return false;
}

void CCollisionMgr::BOMB_RECT2(RECT Dst, list<CObj*> Src)
{
	RECT	rc{};
	for (auto& SrcList : Src)
	{
		if (IntersectRect(&rc, &(Dst), &(SrcList->Get_Rect())))
		{
			static_cast<CMonster*>(SrcList)->Set_DEAD_State();

		}
	}
}

void CCollisionMgr::Collision_Rect_Melee(CObj* Dst, list<CObj*> Src)
{
	RECT	rc{};
	for (auto& SrcList : Src)
	{
		if (IntersectRect(&rc, &(Dst->Get_Rect()), &(SrcList->Get_Rect())))
		{
			static_cast<CMonster*>(SrcList)->Set_DEAD_State();
			
		}
	}
}

bool CCollisionMgr::Monster_Attack_to_Player(CObj* Monster, CObj* Player)
{
	RECT	rc{};
	if (IntersectRect(&rc, &(Monster->Get_Rect()), &(Player->Get_Rect())))
	{
		static_cast<CPlayer*>(Player)->Player_Die();
		return true;
	}
	return false;
}

bool CCollisionMgr::Collision_Weapon_to_Player(/*list<CObj*>*/CObj* Player, list<CObj*> Src)
{
	RECT	rc{};
	for (auto& SrcList : Src)
	{
		if (IntersectRect(&rc, &(Player->Get_Rect()), &(SrcList->Get_Rect())))
		{
			SrcList->Set_Intersect(true);
			Player->Set_WeaponState(SrcList->Get_WeaponState());
			/*if(SrcList->Get_WeaponState())*/

			/*static_cast<CPlayer*>(Player)->Set_Clip()*/
			return true;
		}
		else
		{
			SrcList->Set_Intersect(false);
		}
	}
	return false;
}

void CCollisionMgr::Collision_Weapon_Erase(CObj* Player, list<CObj*> Src)
{
	RECT	rc{};
	for (auto& SrcList : Src)
	{
		if (IntersectRect(&rc, &(Player->Get_Rect()), &(SrcList->Get_Rect())))
		{
			SrcList->Set_Dead();
		}
	}
}

void CCollisionMgr::Collision_CloseAttack(CObj* Player, list<CObj*> Src)
{

}

void CCollisionMgr::Collision_RectEx(list<CObj*> Walllist, vector<CObj*> Movelist)
{
	float fX = 0.f, fY = 0.f;

	for (auto& Dst : Walllist)
	{
		for (auto& Src : Movelist)
		{
			if (Check_Rect(&fX, &fY, Dst, Src))
			{
				if (fX > fY)	// ���� �浹
				{
					// �� �浹
					if (Dst->Get_Info().fY < Src->Get_Info().fY)
						Dst->Set_PosY(-fY);
					// �� �浹
					else
						Dst->Set_PosY(fY);
				}
				else			// �¿� �浹	
				{
					// �� �浹
					if (Dst->Get_Info().fX < Src->Get_Info().fX)
						Dst->Set_PosX(-fX);
					// �� �浹
					else
						Dst->Set_PosX(fX);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(CObj* player, vector<CObj*> wall)
{
	float fX = 0.f, fY = 0.f;

		for (auto& Src : wall)
		{
			if (Check_Rect(&fX, &fY, player, Src))
			{
				if (fX > fY)	// ���� �浹
				{
					// �� �浹
				if (player->Get_Info().fY < Src->Get_Info().fY)
					player->Set_PosY(-fY);
					// �� �浹
				else
					player->Set_PosY(fY);
			}
			else			// �¿� �浹	
			{
					// �� �浹
				if (player->Get_Info().fX < Src->Get_Info().fX)
					player->Set_PosX(-fX);
					// �� �浹
				else
					player->Set_PosX(fX);
			}
		}
	}
	
}

bool CCollisionMgr::Collision_Rect_Patroll(CObj* Monster, vector<CObj*> wall)
{

	float fX = 0.f, fY = 0.f;

	for (auto& Src : wall)
	{
		if (Check_Rect(&fX, &fY, Monster, Src))
		{
			if (fX > fY)	// ���� �浹
			{
				// �� �浹
				if (Monster->Get_Info().fY < Src->Get_Info().fY)
				{
					Monster->Set_PosY(-fY);
					return true;
				}
				// �� �浹
				else
				{
					Monster->Set_PosY(fY);
					return true;
				}
			}
			else			// �¿� �浹	
			{
				// �� �浹
				if (Monster->Get_Info().fX < Src->Get_Info().fX)
				{
					Monster->Set_PosX(-fX);
					return true;
				}
				// �� �浹
				else
				{
					Monster->Set_PosX(fX);
					return true;
				}
			}
		}
	}
	return false;
}

bool CCollisionMgr::Check_Rect(float * pX, float * pY, CObj * pDst, CObj * pSrc)
{
	float		fWidth  = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float		fRadiusX = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (pDst->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}


	return false;
}

bool CCollisionMgr::Collision_Sphere(CObj* Dst, list<CObj*> Src)
{
	for (auto& SrcList : Src)
	{
		if (Check_Sphere(Dst, SrcList))
		{
			return true;
			SrcList->Set_Dead();
		}
	}
	return false;
}

bool CCollisionMgr::Check_Sphere(CObj * pDst, CObj * pSrc)
{
	float		fWidth  = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float		fDistance = sqrt(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	
	return fRadius >= fDistance;
}
