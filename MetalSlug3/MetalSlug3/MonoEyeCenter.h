#pragma once
#include <EngineCore/Actor.h>
#include "MonoEyes.h"

enum class MonoEyesPattern
{
	None,
	Pattern0,
	Pattern1,
	Pattern2,
	Pattern3,
	Pattern4,
};

class AMonoEyeCenter : public AActor
{
public:
	// constructor destructor
	AMonoEyeCenter();
	~AMonoEyeCenter();

	// delete Function
	AMonoEyeCenter(const AMonoEyeCenter& _Other) = delete;
	AMonoEyeCenter(AMonoEyeCenter&& _Other) noexcept = delete;
	AMonoEyeCenter& operator=(const AMonoEyeCenter& _Other) = delete;
	AMonoEyeCenter& operator=(AMonoEyeCenter&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void PatternUpdate(float _DeltaTime);
	void ChangePattern(MonoEyesPattern _Pattern);

	MonoEyesPattern CurPattern = MonoEyesPattern::None;

	void Pattern0(float _DeltaTime);
	void Pattern1(float _DeltaTime);
	void Pattern2(float _DeltaTime);

	void Pattern0Start();
	void Pattern1Start();
	void Pattern2Start();

	int turn = 0;

	float AccPattern = 0.0f;
	float PatternCoolTime = 3.0f;

	float MoveSpeed = 200.0f;
	float XTargetPosition = 14150.0f;

	FVector Center = { 14150,2050 };

	std::vector<AMonoEyes*> MonoEyes;
};

