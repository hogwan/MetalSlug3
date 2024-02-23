#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"
class AHuman : public AActor
{
public:
	// constructor destructor
	AHuman();
	~AHuman();

	// delete Function
	AHuman(const AHuman& _Other) = delete;
	AHuman(AHuman&& _Other) noexcept = delete;
	AHuman& operator=(const AHuman& _Other) = delete;
	AHuman& operator=(AHuman&& _Other) = delete;

	void SetHumanState(HumanState _State)
	{
		CurState = _State;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;
	UCollision* DetectCollider = nullptr;
	HumanState CurState = HumanState::None;
	bool IsDeath = false;
	float MoveSpeed = 25.0f;
	float RunSpeed = 100.0f;

	float DetectRange = 150.0f;

	FVector CollisionScale = { 70,70 };
	FVector CollisionPosition = { 0, -35 };

	void GravityCheck(float _DeltaTime);
	void GroundUp();

};

