#include "stdafx.h"
#include "SceneMgr.h"



CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(SC_LOGO), m_ePreScene(SC_END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{

		case SC_TUTO:
			m_pScene = new Tutorial;
			break;

		case SC_LOGO:
			m_pScene = new CLogo;
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_EDIT:
			m_pScene = new CMyEdit;
			break;

		case SC_STAGE:
			m_pScene = new CStage;
			break;

		case SC_STAGE1RE:
			m_pScene = new CStage;
			break;

		case SC_STAGE2:
			m_pScene = new Stage2;
			break;

		case SC_STAGE2RE:
			m_pScene = new Stage2;
			break;

		case SC_STAGE3:
			m_pScene = new Stage3;
			break;

		case SC_STAGE3RE:
			m_pScene = new Stage3;
			break;

		case SC_STAGE4:
			m_pScene = new Stage4;
			break;

		case SC_STAGE4RE:
			m_pScene = new Stage4;
			break;

		case SC_STAGE5:
			m_pScene = new Stage5;
			break;

		case SC_STAGE5RE:
			m_pScene = new Stage5;
			break;

		case SCORE_SCENE:
			m_pScene = new CScoreBoard;
			break;

		/*case SC_STAGE5RER:
			m_pScene = new BossStage;
			break;*/
		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}

}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
