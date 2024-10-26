#include "stdafx.h"
#include "CornerMgr.h"
#include "Corner.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Boss.h"
CornerMgr* CornerMgr::m_pInstance = nullptr;

CornerMgr::CornerMgr()
{
}

CornerMgr::~CornerMgr()
{
	Release();
}

void CornerMgr::Initialize()
{
	m_vecCorner.reserve(10);
}

void CornerMgr::Update()
{
	for (auto& iter : m_vecCorner)
		iter->Update();
	CCollisionMgr::Collision_Rect(m_vecCorner, CObjMgr::Get_Instance()->Get_List(BULLET));
	CCollisionMgr::Collision_Rect(m_vecCorner, CObjMgr::Get_Instance()->Get_List(MBULLET));
}

void CornerMgr::Late_Update()
{
	for (auto& iter : m_vecCorner)
	{
		iter->Late_Update();
	}
	/*CCollisionMgr::Collision_RectEx(CObjMgr::Get_Instance()->Get_List(MONSTER), m_vecCorner);*/
	/*CCollisionMgr::Collision_RectEx(CPlayer::Get_Instance()->Get_Player(), m_vecCorner);*/
	/*CCollisionMgr::Collision_RectEx(CBoss::Get_Instance()->Get_Boss(), m_vecCorner);*/


}

void CornerMgr::Render(HDC hDC)
{
	int CameraX = CCameraMgr::Get_Instance()->m_PosX;
	int CameraY = CCameraMgr::Get_Instance()->m_PosY;
	int		iMaxX = CameraX + WINCX / 2 /*+ 8*/;
	int		iMaxY = CameraY + WINCY / 2/* + 8*/;

	int		iCullX = CameraX - WINCX / 2 + 8;
	int		iCullY = CameraY - WINCY / 2 + 8;
	for (auto& iter : m_vecCorner)
	{
		if (iCullX < iter->Get_Info().fX && iter->Get_Info().fX < iMaxX
			&& iCullY < iter->Get_Info().fY && iter->Get_Info().fY < iMaxY)
		{
			iter->Render(hDC);
		}
	}

}

void CornerMgr::Release()
{
	for_each(m_vecCorner.begin(), m_vecCorner.end(), CDeleteObj());
	m_vecCorner.clear();
	m_vecCorner.shrink_to_fit();
}

void CornerMgr::Picking(float _x, float _y, int _iDrawID, int _iOption)
{
	int x = _x;
	int y = _y;
	int XX = x % 8;
	int YY = y % 8;
	CObj* corner = CAbstractFactory<Corner>::Create(x - XX, y - YY, 0);
	static_cast<Corner*>(corner)->Set_Tile(_iDrawID, _iOption);
	m_vecCorner.push_back(corner);
}

void CornerMgr::Save_C()
{
	HANDLE	hFile = CreateFile(L"../Data/1Corner.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);
	for (auto& iter : m_vecCorner)
	{
		m_iXNum = dynamic_cast<Corner*>(iter)->Get_DrawID();
		m_iYNum = dynamic_cast<Corner*>(iter)->Get_Option();
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Corner Save", L"己傍", MB_OK);
}

void CornerMgr::Save_C2()
{
	HANDLE	hFile = CreateFile(L"../Data/2Corner.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);
	for (auto& iter : m_vecCorner)
	{
		m_iXNum = dynamic_cast<Corner*>(iter)->Get_DrawID();
		m_iYNum = dynamic_cast<Corner*>(iter)->Get_Option();
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Corner Save", L"己傍", MB_OK);
}

void CornerMgr::Save_C3()
{
	HANDLE	hFile = CreateFile(L"../Data/3Corner.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);
	for (auto& iter : m_vecCorner)
	{
		m_iXNum = dynamic_cast<Corner*>(iter)->Get_DrawID();
		m_iYNum = dynamic_cast<Corner*>(iter)->Get_Option();
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Corner Save", L"己傍", MB_OK);
}

void CornerMgr::Save_C4()
{
	HANDLE	hFile = CreateFile(L"../Data/4Corner.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);
	for (auto& iter : m_vecCorner)
	{
		m_iXNum = dynamic_cast<Corner*>(iter)->Get_DrawID();
		m_iYNum = dynamic_cast<Corner*>(iter)->Get_Option();
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Corner Save", L"己傍", MB_OK);
}

void CornerMgr::Save_C5()
{
	HANDLE	hFile = CreateFile(L"../Data/5Corner.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);
	for (auto& iter : m_vecCorner)
	{
		m_iXNum = dynamic_cast<Corner*>(iter)->Get_DrawID();
		m_iYNum = dynamic_cast<Corner*>(iter)->Get_Option();
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Corner Save", L"己傍", MB_OK);
}

void CornerMgr::Save_CT()
{
	HANDLE	hFile = CreateFile(L"../Data/TCorner.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);
	for (auto& iter : m_vecCorner)
	{
		m_iXNum = dynamic_cast<Corner*>(iter)->Get_DrawID();
		m_iYNum = dynamic_cast<Corner*>(iter)->Get_Option();
		WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Corner Save", L"己傍", MB_OK);
}

void CornerMgr::Load_CT()
{
	HANDLE	hFile = CreateFile(L"../Data/TCorner.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<Corner>::Create(tInfo.fX, tInfo.fY, 0.f);
		dynamic_cast<Corner*>(pObj)->Set_Tile(m_iXNum, m_iYNum);
		m_vecCorner.push_back(pObj);
	}
	CloseHandle(hFile);
}

void CornerMgr::Load_C()
{
	HANDLE	hFile = CreateFile(L"../Data/1Corner.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<Corner>::Create(tInfo.fX, tInfo.fY, 0.f);
		dynamic_cast<Corner*>(pObj)->Set_Tile(m_iXNum, m_iYNum);
		m_vecCorner.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Corner Load", L"己傍", MB_OK);*/
}

void CornerMgr::Load_C2()
{
	HANDLE	hFile = CreateFile(L"../Data/2Corner.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<Corner>::Create(tInfo.fX, tInfo.fY, 0.f);
		dynamic_cast<Corner*>(pObj)->Set_Tile(m_iXNum, m_iYNum);
		m_vecCorner.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Corner Load", L"己傍", MB_OK);*/
}

void CornerMgr::Load_C3()
{
	HANDLE	hFile = CreateFile(L"../Data/3Corner.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<Corner>::Create(tInfo.fX, tInfo.fY, 0.f);
		dynamic_cast<Corner*>(pObj)->Set_Tile(m_iXNum, m_iYNum);
		m_vecCorner.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Corner Load", L"己傍", MB_OK);*/
}

void CornerMgr::Load_C4()
{
	HANDLE	hFile = CreateFile(L"../Data/4Corner.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<Corner>::Create(tInfo.fX, tInfo.fY, 0.f);
		dynamic_cast<Corner*>(pObj)->Set_Tile(m_iXNum, m_iYNum);
		m_vecCorner.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Corner Load", L"己傍", MB_OK);*/
}

void CornerMgr::Load_C5()
{
	HANDLE	hFile = CreateFile(L"../Data/5Corner.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;
	INFO	tInfo{};
	int		m_iXNum(0), m_iYNum(0);
	DWORD	dwByte(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &m_iXNum, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &m_iYNum, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<Corner>::Create(tInfo.fX, tInfo.fY, 0.f);
		dynamic_cast<Corner*>(pObj)->Set_Tile(m_iXNum, m_iYNum);
		m_vecCorner.push_back(pObj);
	}
	CloseHandle(hFile);
	/*MessageBox(g_hWnd, L"Corner Load", L"己傍", MB_OK);*/
}
