#include "stdafx.h"
#include "Pipe.h"
#include "PngMrg.h"
#include "CollisionMgr.h"
CPipe::CPipe()
{
	
}

CPipe::~CPipe()
{
	Release();
}

void CPipe::Initialize()
{
	m_tInfo.fCX = 61;
	m_tInfo.fCY = 61;
	/*srand(unsigned(time(NULL)));
	m_fAngle = rand() % 360;*/
	m_eRender = UI;
	m_eWeaponState = PIPE;

}

int CPipe::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();
	__super::Update_Rect_Pos();
	return OBJ_NOEVENT;
}

void CPipe::Late_Update()
{
	Change_ImageKey();
}

void CPipe::Render(HDC hDC)
{
	
	int RenderX = m_tInfo.fX - CCameraMgr::Get_Instance()->m_fDiffX;
	int RenderY = m_tInfo.fY - CCameraMgr::Get_Instance()->m_fDiffY;

	Graphics graphics(hDC);						//�̹��� ȸ�� �� ����� ���� �׷��Ƚ� ����
	graphics.TranslateTransform(RenderX, RenderY);  //��� ȸ���Լ�
	graphics.RotateTransform(m_fAngle);		//ȸ�� �Լ�
	graphics.TranslateTransform(-RenderX, -RenderY); //��� ȸ���Լ�

	
	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pFrameKey), //�׷��� �� �̹��� (��������Ʈ ��Ʈ)
		m_tRect.left, m_tRect.top,					//�׸��� ������ ��ġ
		0, 122,					//�̹����� ��𼭺��� �׸���
		(INT)m_tInfo.fCX, (INT)m_tInfo.fCY,		//�̹����� ������ �׸���
		UnitPixel);


}

void CPipe::Release()
{

}
