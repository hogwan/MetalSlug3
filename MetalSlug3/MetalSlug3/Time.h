#pragma once
#include "UIBase.h"
class ATime : public AUIBase
{
public:
	// constructor destructor
	ATime();
	~ATime();

	// delete Function
	ATime(const ATime& _Other) = delete;
	ATime(ATime&& _Other) noexcept = delete;
	ATime& operator=(const ATime& _Other) = delete;
	ATime& operator=(ATime&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Units = nullptr;
	UImageRenderer* Tens = nullptr;

	float RemainTime = 60.0f;
};

