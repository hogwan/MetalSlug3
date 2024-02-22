#pragma once
#include "UIBase.h"
class ASlugEnergyBar : public AUIBase
{
public:
	// constructor destructor
	ASlugEnergyBar();
	~ASlugEnergyBar();

	// delete Function
	ASlugEnergyBar(const ASlugEnergyBar& _Other) = delete;
	ASlugEnergyBar(ASlugEnergyBar&& _Other) noexcept = delete;
	ASlugEnergyBar& operator=(const ASlugEnergyBar& _Other) = delete;
	ASlugEnergyBar& operator=(ASlugEnergyBar&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
};

