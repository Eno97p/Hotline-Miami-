#pragma once

#include "Scene.h"

class CStage : public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	bool Is_StageClear();

protected :
	float m_fVolume;
	RECT	m_rGate;
	bool	StageClear;
};

