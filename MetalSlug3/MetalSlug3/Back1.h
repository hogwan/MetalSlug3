#pragma once
#include "BackMap.h"
class ABack1 : public ABackMap
{
public:
	// constructor destructor
	ABack1();
	~ABack1();

	// delete Function
	ABack1(const ABack1& _Other) = delete;
	ABack1(ABack1&& _Other) noexcept = delete;
	ABack1& operator=(const ABack1& _Other) = delete;
	ABack1& operator=(ABack1&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

