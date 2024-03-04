#pragma once
#include "Enemy.h"

class AMonoEyes : public AEnemy
{
public:
	// constructor destructor
	AMonoEyes();
	~AMonoEyes();

	// delete Function
	AMonoEyes(const AMonoEyes& _Other) = delete;
	AMonoEyes(AMonoEyes&& _Other) noexcept = delete;
	AMonoEyes& operator=(const AMonoEyes& _Other) = delete;
	AMonoEyes& operator=(AMonoEyes&& _Other) = delete;

	void SetZPos(ZPos _ZPos)
	{
		CurZPos = _ZPos;
	}

	void SetInitialPos(FVector _InitialPos)
	{
		InitialPosition = _InitialPos;
	}

	void SetRotAngle(float _Angle)
	{
		RotAngle = _Angle;
	}

	void SetRatio(FVector _Ratio)
	{
		Ratio = _Ratio;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	ZPos CurZPos = ZPos::Back;
	FVector InitialPosition = FVector::Zero;
	FVector Ratio = FVector::Zero;

	std::string CurImageName = "None";
	std::string AttachName = "None";

	void Spawn(float _DeltaTime);
	void Idle(float _DeltaTime);

	float Speed = 800.0f;
	float AccAttack = 0.0f;
	float AttackCoolTime = 3.0f;

	float RotAngle = 0.0f;
};

