#pragma once
#include "Obj.h"

class CBlood :
    public CObj
{
    // CObj��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};
