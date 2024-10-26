#pragma once
#include "Obj.h"
class Go :
    public CObj
{

public:
    Go();
    virtual~Go();
    // CObj��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    TCHAR* m_PngKey;

};

