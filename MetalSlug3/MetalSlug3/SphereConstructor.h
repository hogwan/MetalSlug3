#pragma once
#include <EngineCore/Actor.h>
class ASphereConstructor : public AActor
{
public:
	// constructor destructor
	ASphereConstructor();
	~ASphereConstructor();

	// delete Function
	ASphereConstructor(const ASphereConstructor& _Other) = delete;
	ASphereConstructor(ASphereConstructor&& _Other) noexcept = delete;
	ASphereConstructor& operator=(const ASphereConstructor& _Other) = delete;
	ASphereConstructor& operator=(ASphereConstructor&& _Other) = delete;

	void SetTarget(FVector _FirstTarget, FVector _SecondTarget)
	{
		FirstTarget = _FirstTarget;
		SecondTarget = _SecondTarget;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	float Speed = 0.0f;
	float Accel = 100.0f;

	float AccSpawnTime = 0.0f;
	float SpawnCoolTime = 0.2f;

	FVector FirstTarget = FVector::Zero;
	FVector SecondTarget = FVector::Zero;

	bool FirstStep = false;
	bool SecondStep = false;

};

