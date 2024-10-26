#include "stdafx.h"
#include "VWallMgr.h"
#include "WallV.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Boss.h"
VWallMgr* VWallMgr::m_pInstance = nullptr;
VWallMgr::VWallMgr()
{
}

VWallMgr::~VWallMgr()
{
	Release();
}

void VWallMgr::Initialize()
{
	m_vecWallVV.reserve(10);
}

void VWallMgr::Update()
{
	for (auto& iter : m_vecWallVV)
		iter->Update();
	CCollisionMgr::Collision_Rect(m_vecWallVV, CObjMgr::Get_Instance()->Get_List(BULLET));
	CCollisionMgr::Collision_Rect(m_vecWallVV, CObjMgr::Get_Instance()->Get_List(MBULLET));
}

void VWallMgr::Late_Update()
{
	for (auto& iter : m_vecWallVV)
	{
		iter->Late_Update();
		
	}
	/*CCollisionMgr::Collision_RectEx(CObjMgr::Get_Instance()->Get_List(MONSTER), m_vecWallVV);*/
	/*CCollisionMgr::Collision_RectEx(CPlayer::Get_Instance()->Get_Player(), m_vecWallVV);*/
	/*CCollisionMgr::Collision_RectEx(CBoss::Get_Instance()->Get_Boss(), m_vecWallVV);*/
	
	
	
}

void VWallMgr::Render(HDC hDC)
{
	int CameraX = CCameraMgr::Get_Instance()->m_PosX;
	int CameraY = CCameraMgr::Get_Instance()->m_PosY;
	int		iMaxX = CameraX + WINCX / 2 /*+ 8*/;
	int		iMaxY = CameraY + WINCY / 2 /*+ 32*/;

	int		iCullX = CameraX - WINCX / 2 + 8;
	int		iCullY = CameraY - WINCY / 2 + 32;

	for (auto& iter : m_vecWallVV)
	{
		if (iCullX < iter->Get_Info().fX && iter->Get_Info().fX < iMaxX
			&& iCullY < iter->Get_Info().fY && iter->Get_Info().fY < iMaxY)
		{
			iter->Render(hDC);
		}
	}
}

void VWallMgr::Release()
{
	for_each(m_vecWallVV.begin(), m_vecWallVV.end(), CDeleteObj());
	m_vecWallVV.clear();
	m_vecWallVV.shrink_to_fit();
}

void VWallMgr::Picking(float _x, float _y, int _iDrawID, int _iOption)
{
	int x = _x;
	int y = _y;
	int XX = x % 8;
	int YY = y % 32;
	CObj* wallV = CAbstractFactory<WallV>::Create(x - XX, y - YY, 0);
	m_vecWallVV.push_back(wallV);
}

void VWallMgr::Save_V()
{
	HANDLE	vFile = CreateFile(L"../Data/1SVall.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == vFile)
		return;
	DWORD	vByte(0);;
	for (auto& iter : m_vecWallVV)
	{
		WriteFile(vFile, &(iter->Get_Info()), sizeof(INFO), &vByte, nullptr);
	}
	CloseHandle(vFile);
	MessageBox(g_hWnd, L"VTile Save", L"己傍", MB_OK);
}

void VWallMgr::Save_V2()
{
	HANDLE	vFile = CreateFile(L"../Data/2SVall.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == vFile)
		return;
	DWORD	vByte(0);;
	for (auto& iter : m_vecWallVV)
	{
		WriteFile(vFile, &(iter->Get_Info()), sizeof(INFO), &vByte, nullptr);
	}
	CloseHandle(vFile);
	MessageBox(g_hWnd, L"VTile Save", L"己傍", MB_OK);
}

void VWallMgr::Save_V3()
{
	HANDLE	vFile = CreateFile(L"../Data/3SVall.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == vFile)
		return;
	DWORD	vByte(0);;
	for (auto& iter : m_vecWallVV)
	{
		WriteFile(vFile, &(iter->Get_Info()), sizeof(INFO), &vByte, nullptr);
	}
	CloseHandle(vFile);
	MessageBox(g_hWnd, L"VTile Save", L"己傍", MB_OK);
}

void VWallMgr::Save_V4()
{
	HANDLE	vFile = CreateFile(L"../Data/4SVall.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == vFile)
		return;
	DWORD	vByte(0);;
	for (auto& iter : m_vecWallVV)
	{
		WriteFile(vFile, &(iter->Get_Info()), sizeof(INFO), &vByte, nullptr);
	}
	CloseHandle(vFile);
	MessageBox(g_hWnd, L"VTile Save", L"己傍", MB_OK);
}

void VWallMgr::Save_V5()
{
	HANDLE	vFile = CreateFile(L"../Data/5SVall.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == vFile)
		return;
	DWORD	vByte(0);;
	for (auto& iter : m_vecWallVV)
	{
		WriteFile(vFile, &(iter->Get_Info()), sizeof(INFO), &vByte, nullptr);
	}
	CloseHandle(vFile);
	MessageBox(g_hWnd, L"VTile Save", L"己傍", MB_OK);
}

void VWallMgr::Save_VT()
{
	HANDLE	vFile = CreateFile(L"../Data/TSVall.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == vFile)
		return;
	DWORD	vByte(0);;
	for (auto& iter : m_vecWallVV)
	{
		WriteFile(vFile, &(iter->Get_Info()), sizeof(INFO), &vByte, nullptr);
	}
	CloseHandle(vFile);
	MessageBox(g_hWnd, L"VTile Save", L"己傍", MB_OK);
}

void VWallMgr::Load_VT()
{
	HANDLE	vFile = CreateFile(L"../Data/TSVall.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == vFile)
		return;
	INFO	vInfo{};
	DWORD	vByte(0);
	Release();
	while (true)
	{
		ReadFile(vFile, &vInfo, sizeof(INFO), &vByte, nullptr);
		if (0 == vByte)
			break;
		CObj* vObj = CAbstractFactory<WallV>::Create(vInfo.fX, vInfo.fY, 0.f);
		m_vecWallVV.push_back(vObj);
	}
	CloseHandle(vFile);
}

void VWallMgr::Load_V()
{
	HANDLE	vFile = CreateFile(L"../Data/1SVall.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == vFile)
		return;
	INFO	vInfo{};
	DWORD	vByte(0);
	Release();
	while (true)
	{
		ReadFile(vFile, &vInfo, sizeof(INFO), &vByte, nullptr);
		if (0 == vByte)
			break;
		CObj* vObj = CAbstractFactory<WallV>::Create(vInfo.fX, vInfo.fY, 0.f);
		m_vecWallVV.push_back(vObj);
	}
	CloseHandle(vFile);
	/*MessageBox(g_hWnd, L"VWall Load", L"己傍", MB_OK);*/
}

void VWallMgr::Load_V2()
{
	HANDLE	vFile = CreateFile(L"../Data/2SVall.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == vFile)
		return;
	INFO	vInfo{};
	DWORD	vByte(0);
	Release();
	while (true)
	{
		ReadFile(vFile, &vInfo, sizeof(INFO), &vByte, nullptr);
		if (0 == vByte)
			break;
		CObj* vObj = CAbstractFactory<WallV>::Create(vInfo.fX, vInfo.fY, 0.f);
		m_vecWallVV.push_back(vObj);
	}
	CloseHandle(vFile);
	/*MessageBox(g_hWnd, L"VWall Load", L"己傍", MB_OK);*/
}

void VWallMgr::Load_V3()
{
	HANDLE	vFile = CreateFile(L"../Data/3SVall.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == vFile)
		return;
	INFO	vInfo{};
	DWORD	vByte(0);
	Release();
	while (true)
	{
		ReadFile(vFile, &vInfo, sizeof(INFO), &vByte, nullptr);
		if (0 == vByte)
			break;
		CObj* vObj = CAbstractFactory<WallV>::Create(vInfo.fX, vInfo.fY, 0.f);
		m_vecWallVV.push_back(vObj);
	}
	CloseHandle(vFile);
	/*MessageBox(g_hWnd, L"VWall Load", L"己傍", MB_OK);*/
}

void VWallMgr::Load_V4()
{
	HANDLE	vFile = CreateFile(L"../Data/4SVall.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == vFile)
		return;
	INFO	vInfo{};
	DWORD	vByte(0);
	Release();
	while (true)
	{
		ReadFile(vFile, &vInfo, sizeof(INFO), &vByte, nullptr);
		if (0 == vByte)
			break;
		CObj* vObj = CAbstractFactory<WallV>::Create(vInfo.fX, vInfo.fY, 0.f);
		m_vecWallVV.push_back(vObj);
	}
	CloseHandle(vFile);
	/*MessageBox(g_hWnd, L"VWall Load", L"己傍", MB_OK);*/
}

void VWallMgr::Load_V5()
{
	HANDLE	vFile = CreateFile(L"../Data/5SVall.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == vFile)
		return;
	INFO	vInfo{};
	DWORD	vByte(0);
	Release();
	while (true)
	{
		ReadFile(vFile, &vInfo, sizeof(INFO), &vByte, nullptr);
		if (0 == vByte)
			break;
		CObj* vObj = CAbstractFactory<WallV>::Create(vInfo.fX, vInfo.fY, 0.f);
		m_vecWallVV.push_back(vObj);
	}
	CloseHandle(vFile);
	/*MessageBox(g_hWnd, L"VWall Load", L"己傍", MB_OK);*/
}
