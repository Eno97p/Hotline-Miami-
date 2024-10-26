#pragma once
#include "Scene.h"
class Stage2 :
    public CScene
{
public:
    Stage2();
    virtual~Stage2();
    // CScene��(��) ���� ��ӵ�
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    bool Is_StageClear();
protected:
    float m_fVolume;
    RECT	m_rGate;
    bool	StageClear;
};

