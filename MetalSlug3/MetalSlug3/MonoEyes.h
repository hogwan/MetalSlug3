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

	void SetVibAngle(float _VibAngle)
	{
		VibAngle = _VibAngle;
	}
	void SetRatio(FVector _Ratio)
	{
		Ratio = _Ratio;
	}

	void SetRotSpeed(float _XRotSpeed, float _YRotSpeed)
	{
		XRotSpeed = _XRotSpeed;
		YRotSpeed = _YRotSpeed;
	}


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* LaunchRenderer = nullptr;

	ZPos CurZPos = ZPos::Back;
	FVector InitialPosition = FVector::Zero;
	FVector Ratio = FVector::Zero;
	FVector LaunchEffectOffset = { 0, -200 };
	FVector TargetPosition = FVector::Zero;
	float Speed = 300.0f;
	float amplitude = 15.0f;

	std::string CurImageName = "None";
	std::string AttachName = "None";

	void Spawn(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Launch(float _DeltaTime);

	void LaunchStart();
	void LaunchOn();

	bool IsLaunch = false;
	float LaunchCoolTime = 1.0f;
	float AccLaunch = 0.0f;

	float AccAttack = 0.0f;
	float AttackCoolTime = 3.0f;

	float RotAngle = 0.0f;
	float VibAngle = 0.0f;

	float XRotSpeed = 0.0f;
	float YRotSpeed = 0.0f;
};

