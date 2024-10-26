#include "stdafx.h"
#include "Knife.h"

#include "PngMrg.h"
CKnife::CKnife()
{
}

CKnife::~CKnife()
{
}

void CKnife::Initialize()
{
	m_tInfo.fCX = 61;
	m_tInfo.fCY = 61;
	m_eRender = UI;
	m_eWeaponState = KNIFE;
}

int CKnife::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();
	__super::Update_Rect_Pos();
	return OBJ_NOEVENT;
}

void CKnife::Late_Update()
{
	Change_ImageKey();
}

void CKnife::Render(HDC hDC)
{
	int RenderX = m_tInfo.fX - CCameraMgr::Get_Instance()->m_fDiffX;
	int RenderY = m_tInfo.fY - CCameraMgr::Get_Instance()->m_fDiffY;
	RECT renderRect{ m_tRect.left - CCameraMgr::Get_Instance()->m_fDiffX ,
	m_tRect.top - CCameraMgr::Get_Instance()->m_fDiffY ,
	m_tRect.right - CCameraMgr::Get_Instance()->m_fDiffX ,
	m_tRect.bottom - m_tRect.top - CCameraMgr::Get_Instance()->m_fDiffY };
	Graphics graphics(hDC);						//�̹��� ȸ�� �� ����� ���� �׷��Ƚ� ����
	graphics.TranslateTransform(RenderX, RenderY);  //��� ȸ���Լ�
	graphics.RotateTransform(m_fAngle);		//ȸ�� �Լ�
	graphics.TranslateTransform(-RenderX, -RenderY); //��� ȸ���Լ�

	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pFrameKey), //�׷��� �� �̹��� (��������Ʈ ��Ʈ)
		renderRect.left, renderRect.top,					//�׸��� ������ ��ġ
		61, 0,					//�̹����� ��𼭺��� �׸���
		(INT)m_tInfo.fCX, (INT)m_tInfo.fCY,		//�̹����� ������ �׸���
		UnitPixel);
}

void CKnife::Release()
{
}
