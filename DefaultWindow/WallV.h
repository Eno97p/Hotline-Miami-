#pragma once
#include "Obj.h"
class WallV :
    public CObj
{
    // CObj을(를) 통해 상속됨
public :
    WallV();
    virtual~WallV();
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    int			m_iDrawID;
    int			m_iOption;
    TCHAR* m_TileKey;
};

