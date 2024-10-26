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


	Graphics graphics(hDC);						//이미지 회전 및 출력을 위한 그래픽스 선언
	graphics.TranslateTransform(RenderX, RenderY);  //행렬 회전함수
	graphics.RotateTransform(m_fAngle);		//회전 함수
	graphics.TranslateTransform(-RenderX, -RenderY); //행렬 회전함수

	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(m_pFrameKey), //그려야 할 이미지 (스프라이트 시트)
		m_tRect.left , m_tRect.top,					//그리기 시작할 위치
		0, 61,					//이미지의 어디서부터 그릴지
		(INT)m_tInfo.fCX, (INT)m_tInfo.fCY,		//이미지의 어디까지 그릴지
		UnitPixel);
}
void CShotGun::Release()
{
}
