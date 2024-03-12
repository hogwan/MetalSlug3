#pragma once
#include "MT3Object.h"
class AItem
	: public AMT3Object
{
public:
	// constructor destructor
	AItem();
	~AItem();

	// delete Function
	AItem(const AItem& _Other) = delete;
	AItem(AItem&& _Other) noexcept = delete;
	AItem& operator=(const AItem& _Other) = delete;
	AItem& operator=(AItem&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UCollision* Collider = nullptr;
	UImageRenderer* Renderer = nullptr;

	float AccActive = 0.0f;
	float ActiveTime = 0.8f;

	virtual void Action();

	void GravityCheck(float _DeltaTime);
};

