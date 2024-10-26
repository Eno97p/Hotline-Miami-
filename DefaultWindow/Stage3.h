#pragma once
#include "Scene.h"
class Stage3 :
    public CScene
{

public:
    Stage3();
    virtual~Stage3();
    // CScene��(��) ���� ��ӵ�
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    bool Is_StageClear();

protected:
    RECT	m_rGate;
    bool	StageClear;
};

