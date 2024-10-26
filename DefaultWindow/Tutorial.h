#pragma once
#include "Scene.h"
class Tutorial :
    public CScene
{

public:
    Tutorial();
    virtual~Tutorial();
    // CScene��(��) ���� ��ӵ�
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Move_Frame();

private:
    float m_fVol;
    float m_fPhoneCalltime;
    bool  isPhonecall;
    bool  CloseEvent;
    RECT	m_rGate;
    RECT    m_rPhone;

    int ImageNum;

    FRAME m_TFrame;
};

