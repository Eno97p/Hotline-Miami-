#pragma once
#include "Obj.h"
class CFurniture :
    public CObj
{

public:

    enum FUR_ID {};
    CFurniture();
    virtual ~CFurniture();
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    int			m_iDrawID;
    int			m_iOption;
    TCHAR*      m_TileKey;


};

