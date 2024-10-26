#pragma once
#include "Obj.h"
class Corner :
    public CObj
{
public:
    void		Set_Tile(int _iDrawID, int _iOption)
    {
        m_iXNum = _iDrawID;
        m_iYNum = _iOption;
    }
    int		Get_DrawID() { return m_iXNum; }
    int		Get_Option() { return m_iYNum; }
public:
    Corner();
    virtual~Corner();
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    int			m_iXNum;
    int			m_iYNum;
    TCHAR* m_TileKey;
};

