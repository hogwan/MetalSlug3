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

	void SetOriginTargetVector(FVector _Origin, FVector _Target, bool _ClockDir)
	{
		OriginVector = _Origin;
		TargetVector = _Target;

		InitialVector = (GetActorLocation() - OriginVector).Normalize2DReturn();
		LastVector = (GetActorLocation() - TargetVector).Normalize2DReturn();
		MidVector = (InitialVector + LastVector).Normalize2DReturn();

		ClockDir = _ClockDir;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	float Speed = 0.0f;
	float Accel = 10.0f;

	float AccSpawnTime = 0.0f;
	float SpawnCoolTime = 0.2f;

	FVector OriginVector = FVector::Zero;
	FVector TargetVector = FVector::Zero;

	FVector InitialVector = FVector::Zero;
	FVector LastVector = FVector::Zero;
	FVector MidVector = FVector::Zero;
	FVector RotateVector = FVector::Zero;

	bool ClockDir = false;
};

