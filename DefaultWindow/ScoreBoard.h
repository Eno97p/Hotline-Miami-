#pragma once
#include "Scene.h"
class CScoreBoard :
    public CScene
{

    enum ScoreBoardState{ MINSCORE,SECSCORE,MKillSCORE, BKillSCORE,SWAPSCORE,DEADSCORE,RANK,SCORE_END};
public:
    CScoreBoard();
    virtual~CScoreBoard();

public:
    // CScene을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void SCMotion_Change();
    void TimeCalc();

private:
    ScoreBoardState PreScore;
    ScoreBoardState CurScore;
    float ScoreTic;
    int iFrame;

    int m_iTotalScore;
    int m_iPlayerDeadCount;
    int m_MeleeKill;
    int m_BulletKill;

    int m_iMin;
    int m_iSec;
    int m_SwapWeapon;

    RECT MeleeKill;
    RECT BulletKill;
    RECT Min;
    RECT Sec;
    RECT DEADCOUNT;
    RECT SwapWeapon;
    RECT Rank;
    RECT Total;


    float m_fVVol;
};

