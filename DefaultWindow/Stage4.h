#pragma once
#include "Scene.h"
class Stage4 :
    public CScene
{
    enum CsceneState { NOTBOMB, EXPLOSION, BOMBEND, EVENT_END };
public:
    Stage4();
    virtual~Stage4();
    // CScene을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    bool Is_StageClear();
    void BombEvent();
    void SC_Motion_Change();

private:

    RECT	m_rGate;
    RECT    m_rEventRT;
    RECT    m_rBombRect;
    bool	StageClear;
    float   m_fVol;
    CsceneState PreCS;
    CsceneState CurCS;
    float   fFrame;
    int     iExXNum;
    int     iExYNum;

};
