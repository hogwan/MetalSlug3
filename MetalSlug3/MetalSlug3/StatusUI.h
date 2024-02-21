#pragma once
#include "UIBase.h"
class AStatusUI : public AUIBase
{
public:
	// constructor destructor
	AStatusUI();
	~AStatusUI();

	// delete Function
	AStatusUI(const AStatusUI& _Other) = delete;
	AStatusUI(AStatusUI&& _Other) noexcept = delete;
	AStatusUI& operator=(const AStatusUI& _Other) = delete;
	AStatusUI& operator=(AStatusUI&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DecideNumber(int _Count, UImageRenderer* _UnitsRenderer, UImageRenderer* _TensRenderer, UImageRenderer* _HundredsRenderer = nullptr);
	void SwitchNumber(int _Count, UImageRenderer* _Renderer);
	
	UImageRenderer* StatusPanel= nullptr;
	UImageRenderer* Arms_Units = nullptr;
	UImageRenderer* Arms_Tens = nullptr;
	UImageRenderer* Arms_Hundreds = nullptr;
	UImageRenderer* Bombs_Units = nullptr;
	UImageRenderer* Bombs_Tens = nullptr;
	UImageRenderer* Arms_Pistol = nullptr;
};

