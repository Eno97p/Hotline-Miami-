#pragma once
#include "Obj.h"
class CWall :
    public CObj
{
public:
    CWall();
    virtual~CWall();
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void		Set_Wall(int _iDrawID, int _iOption)
    {
        m_iDrawID = _iDrawID;
        m_iOption = _iOption;
    }

private :
    int			m_iDrawID;
    int			m_iOption;
    TCHAR*      m_TileKey;
};

