#include "stdafx.h"
#include "ShotGun.h"

#include "PngMrg.h"
CShotGun::CShotGun()
{
	
}

CShotGun::~CShotGun()
{
	Release();
}

void CShotGun::Initialize()
{
	m_tInfo.fCX = 61;
	m_tInfo.fCY = 61;
	m_eRender = UI;
	m_eWeaponState = SHOTGUN;
}

int CShotGun::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();
	__super::Update_Rect_Pos();
	return OBJ_NOEVENT;
}

void CShotGun::Late_Update()
{
	Change_ImageKey();
}

void CShotGun::Render(HDC hDC)
{
	
	int RenderX = m_tInfo.fX - CCameraMgr::Get_Instance()->m_fDiffX;
	int RenderY = m_tInfo.fY - CCameraMgr::Get_Instance()->m_fDiffY;


	Graphics graphics(hDC);						//�̹��� ȸ�� �� ����� ���� �׷��Ƚ� ����
	graphics.TranslateTransform(RenderX, RenderY);  //��� ȸ���Լ�
	graphics.RotateTransform(m_fAngle);		//ȸ�� �Լ�
	graphics.TranslateTransform(-RenderX, -RenderY); //��� ȸ���Լ�

	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pFrameKey), //�׷��� �� �̹��� (��������Ʈ ��Ʈ)
		m_tRect.left , m_tRect.top,					//�׸��� ������ ��ġ
		0, 61,					//�̹����� ��𼭺��� �׸���
		(INT)m_tInfo.fCX, (INT)m_tInfo.fCY,		//�̹����� ������ �׸���
		UnitPixel);
}
void CShotGun::Release()
{
}
