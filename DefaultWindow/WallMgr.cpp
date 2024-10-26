#include "stdafx.h"
#include "WallMgr.h"
#include "Wall.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Boss.h"
WallMgr* WallMgr::m_pInstance = nullptr;

WallMgr::WallMgr()
{
}

WallMgr::~WallMgr()
{
	Release();
}

void WallMgr::Initialize()
{
	m_vecWall.reserve(10);

}

void WallMgr::Update()
{
	for (auto& iter : m_vecWall)
		iter->Update();
	CCollisionMgr::Collision_Rect(m_vecWall, CObjMgr::Get_Instance()->Get_List(BULLET));
	CCollisionMgr::Collision_Rect(m_vecWall, CObjMgr::Get_Instance()->Get_List(MBULLET));
	
}

void WallMgr::Late_Update()
{
	for (auto& iter : m_vecWall)
	{
		iter->Late_Update();
	}
	/*CCollisionMgr::Collision_RectEx(CObjMgr::Get_Instance()->Get_List(MONSTER), m_vecWall);*/
	/*CCollisionMgr::Collision_RectEx(CPlayer::Get_Instance()->Get_Player(), m_vecWall);*/
	/*CCollisionMgr::Collision_RectEx(CBoss::Get_Instance()->Get_Boss(), m_vecWall);*/
	

}

void WallMgr::Render(HDC hDC)
{
	int CameraX = CCameraMgr::Get_Instance()->m_PosX;
	int CameraY = CCameraMgr::Get_Instance()->m_PosY;
	int		iMaxX = CameraX + WINCX / 2 /*+ 32*/;
	int		iMaxY = CameraY + WINCY / 2 /*+ 8*/;

	int		iCullX = CameraX - WINCX / 2 + 32;
	int		iCullY = CameraY - WINCY / 2 + 8;
	for (auto& iter : m_vecWall)
	{
		if (iCullX < iter->Get_Info().fX && iter->Get_Info().fX < iMaxX
			&& iCullY < iter->Get_Info().fY && iter->Get_Info().fY < iMaxY)
		{
			iter->Render(hDC);
		}
	}
	
}

void WallMgr::Release()
{
	for_each(m_vecWall.begin(), m_vecWall.end(), CDeleteObj());
	m_vecWall.clear();
	m_vecWall.shrink_to_fit();
	
}

void WallMgr::Picking(float _x, float _y, int _iDrawID, int _iOption)
{
	int x = _x;
	int y = _y;
	
	int XX = x % 32;
	int YY = y % 8;
	CObj* wall = CAbstractFactory<CWall>::Create(x - XX, y - YY, 0);
	m_vecWall.push_back(wall);
	
}

void WallMgr::Save_H()
{
	HANDLE	hFile = CreateFile(L"../Data/1SWall.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	DWORD	dwByte(0);;
	for (auto& iter : m_vecWall)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"己傍", MB_OK);
}

void WallMgr::Save_H2()
{
	HANDLE	hFile = CreateFile(L"../Data/2SWall.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	DWORD	dwByte(0);;
	for (auto& iter : m_vecWall)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"己傍", MB_OK);
}

void WallMgr::Save_H3()
{
	HANDLE	hFile = CreateFile(L"../Data/3SWall.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	DWORD	dwByte(0);;
	for (auto& iter : m_vecWall)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"己傍", MB_OK);
}

void WallMgr::Save_H4()
{
	HANDLE	hFile = CreateFile(L"../Data/4SWall.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	DWORD	dwByte(0);;
	for (auto& iter : m_vecWall)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"己傍", MB_OK);
}

void WallMgr::Save_H5()
{
	HANDLE	hFile = CreateFile(L"../Data/5SWall.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	DWORD	dwByte(0);;
	for (auto& iter : m_vecWall)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"己傍", MB_OK);
}

void WallMgr::Save_HT()
{
	HANDLE	hFile = CreateFile(L"../Data/TSWall.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	DWORD	dwByte(0);;
	for (auto& iter : m_vecWall)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"己傍", MB_OK);
}

void WallMgr::Load_HT()
{
	HANDLE	hFile = CreateFile(L"../Data/TSWall.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	DWORD	dwByte(0);
	Release();
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		if (0 == dwByte)
			break;
		CObj* pObj = CAbstractFactory<CWall>::Create(tInfo.fX, tInfo.fY, 0.f);
		m_vecWall.push_back(pObj);
	}
	CloseHandle(hFile);
}


void WallMgr::Load_H()
{
	HANDLE	hFile = CreateFile(L"../Data/1SWall.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	DWORD	dwByte(0);
	Release();
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		if (0 == dwByte)
			break;
		CObj* pObj = CAbstractFactory<CWall>::Create(tInfo.fX, tInfo.fY, 0.f);
		m_vecWall.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Wall Load", L"己傍", MB_OK);*/
}

void WallMgr::Load_H2()
{
	HANDLE	hFile = CreateFile(L"../Data/2SWall.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	DWORD	dwByte(0);
	Release();
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		if (0 == dwByte)
			break;
		CObj* pObj = CAbstractFactory<CWall>::Create(tInfo.fX, tInfo.fY, 0.f);
		m_vecWall.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Wall Load", L"己傍", MB_OK);*/
}

void WallMgr::Load_H3()
{
	HANDLE	hFile = CreateFile(L"../Data/3SWall.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	DWORD	dwByte(0);
	Release();
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		if (0 == dwByte)
			break;
		CObj* pObj = CAbstractFactory<CWall>::Create(tInfo.fX, tInfo.fY, 0.f);
		m_vecWall.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Wall Load", L"己傍", MB_OK);*/
}

void WallMgr::Load_H4()
{
	HANDLE	hFile = CreateFile(L"../Data/4SWall.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	DWORD	dwByte(0);
	Release();
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		if (0 == dwByte)
			break;
		CObj* pObj = CAbstractFactory<CWall>::Create(tInfo.fX, tInfo.fY, 0.f);
		m_vecWall.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Wall Load", L"己傍", MB_OK);*/
}

void WallMgr::Load_H5()
{
	HANDLE	hFile = CreateFile(L"../Data/5SWall.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	DWORD	dwByte(0);
	Release();
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		if (0 == dwByte)
			break;
		CObj* pObj = CAbstractFactory<CWall>::Create(tInfo.fX, tInfo.fY, 0.f);
		m_vecWall.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Wall Load", L"己傍", MB_OK);*/
}

