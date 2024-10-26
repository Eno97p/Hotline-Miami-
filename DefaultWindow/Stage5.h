#pragma once
#include "Scene.h"
class Stage5 :
    public CScene
{

    enum BOSSTAGESCENE { NON_START,BOSS_GROGGY,BOSS_DIE,SCENE_END};
public:
    Stage5();
    virtual~Stage5();

    // CScene을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Scene_Motion_Change();
    void Is_Boss_Groggy();
    void Is_Boss_Die();

private:
    RECT	m_rGate;
    bool	StageClear;
    float   m_fVol;
    float   m_fLoudVol;
    int m_5Num;
    bool EventStart;
    bool CloseEvent;

    float m_fBloodpooltic;
    int m_iBloodPool;
    bool m_bGroggyText;
  

    BOSSTAGESCENE m_ePreB;
    BOSSTAGESCENE m_eCurB;
};

