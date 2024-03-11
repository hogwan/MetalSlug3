#pragma once
#include <EngineCore/Actor.h>

enum class CloudState
{
	None,
	Idle,
	Move,
	Attack,
};

class ThunderCloudObj : public AActor
{
public:
	// constructor destructor
	ThunderCloudObj();
	~ThunderCloudObj();

	// delete Function
	ThunderCloudObj(const ThunderCloudObj& _Other) = delete;
	ThunderCloudObj(ThunderCloudObj&& _Other) noexcept = delete;
	ThunderCloudObj& operator=(const ThunderCloudObj& _Other) = delete;
	ThunderCloudObj& operator=(ThunderCloudObj&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;
	UCollision* Detect = nullptr;

	int RemainLaunchNum = 30;
	float Speed = 2000.f;
	int DetectGround = 0;

	FVector TargetPos = FVector::Zero;
	FVector MoveVector = FVector::Zero;

	CloudState CurState = CloudState::None;

	void StateUpdate(float _DeltaTime);
	void StateChange(CloudState _State);

	void None(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Attack(float _DeltaTime);

	void NoneStart();
	void IdleStart();
	void MoveStart();
	void AttackStart();
};

