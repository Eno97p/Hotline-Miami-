#pragma once
#include "Obj.h"
class Go :
    public CObj
{

public:
    Go();
    virtual~Go();
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    TCHAR* m_PngKey;

};

