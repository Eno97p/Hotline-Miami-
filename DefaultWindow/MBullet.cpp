#include "stdafx.h"
#include "MBullet.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "PngMrg.h"
MBullet::MBullet():g_fVolume(0.3f)
{
}

MBullet::~MBullet()
{
}

void MBullet::Initialize()
{
	m_tInfo.fCX = 14.f;
	m_tInfo.fCY = 5.f;

	m_fSpeed = 40.f;
	m_eRender = EFFECT;

	CSoundMgr::Get_Instance()->PlaySound(L"sndUzi.wav", SOUND_EFFECT, g_fVolume);
}

int MBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	m_tInfo.fX += m_fSpeed * cos(m_fAngle * (PI / 180.f));
	float playerfY = m_pTarget->Get_Rect().bottom - (m_pTarget->Get_Info().fCY * 0.5);
	if (m_tInfo.fY < playerfY)
	{
		m_tInfo.fY -= m_fSpeed * sin(m_fAngle * (PI / 180.f));
	}
	else if (m_tInfo.fY > playerfY)
	{
		m_tInfo.fY += m_fSpeed * sin(m_fAngle * (PI / 180.f));
	}
	__super::Update_Rect();
	
	return OBJ_NOEVENT;
}

void MBullet::Late_Update()
{
	int RenderX = m_tInfo.fX - CCameraMgr::Get_Instance()->m_fDiffX;
	int RenderY = m_tInfo.fY - CCameraMgr::Get_Instance()->m_fDiffY;
	m_fwidth = m_pTarget->Get_Info().fX - CCameraMgr::Get_Instance()->m_fDiffX - m_tInfo.fX;
	m_fheight = m_pTarget->Get_Info().fY - CCameraMgr::Get_Instance()->m_fDiffY - m_tInfo.fY;

	m_fBulletAngle = atan2(m_fheight, m_fwidth) * (180.0f / PI);
	if (m_fBulletAngle < 0.0f) {
		m_fBulletAngle += 360.0f;
	}

	if (m_tInfo.fX < 0 || WINCX < m_tInfo.fX
		|| m_tInfo.fY < 0 || WINCY < m_tInfo.fY)
	{
		m_bDead = true;
	}
}

void MBullet::Render(HDC hDC)
{
	Graphics graphics(hDC);
	graphics.TranslateTransform(m_tInfo.fX, m_tInfo.fY);
	graphics.RotateTransform(m_fBulletAngle);
	graphics.TranslateTransform(-m_tInfo.fX, -m_tInfo.fY);
	graphics.DrawImage(PngMrg::Get_Instance()->Get_Image(L"Bullet"), m_tRect.left, m_tRect.top);
}

void MBullet::Release()
{
}
