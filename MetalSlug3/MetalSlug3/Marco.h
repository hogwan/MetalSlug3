#pragma once
#include <EngineCore\Actor.h>
class Marco : public AActor
{
public:
	// constructor destructor
	Marco();
	~Marco();

	// delete Function
	Marco(const Marco& _Other) = delete;
	Marco(Marco&& _Other) noexcept = delete;
	Marco& operator=(const Marco& _Other) = delete;
	Marco& operator=(Marco&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* UpperBodyRenderer = nullptr;
	UImageRenderer* LowerBodyRenderer = nullptr;
	UImageRenderer* AllBodyRenderer = nullptr;
	UImageRenderer* ZombieArmRenderer = nullptr;
	UImageRenderer* ZombieLaunchEffectRenderer = nullptr;
	UImageRenderer* ZombieProjectileRenderer = nullptr;

	FVector MoveDir = FVector::Zero;
	FVector ShootDir = FVector::Right;
	FVector PrevMoveDir = FVector::Right;

	float Run_Speed = 300.0f;
	float InAir_Speed = 100.0f;
	float Crouch_Speed = 50.0f;

	bool IsZombie = false;
	bool InAir = false;
	bool IsRifle = false;
	bool IsHeavyMachineGun = false;

	int RenderState = 0;
	int PrevRenderState = 0;

	void LeftKeyDownLogic(float _DeltaTime);
	void LeftKeyPressLogic(float _DeltaTime);
	void LeftKeyUpLogic(float _DeltaTime);

	void RightKeyDownLogic(float _DeltaTime);
	void RightKeyPressLogic(float _DeltaTime);
	void RightKeyUpLogic(float _DeltaTime);

	void UpKeyDownLogic(float _DeltaTime);
	void UpKeyPressLogic(float _DeltaTime);
	void UpKeyUpLogic(float _DeltaTime);

	void DownKeyDownLogic(float _DeltaTime);
	void DownKeyPressLogic(float _DeltaTime);
	void DownKeyUpLogic(float _DeltaTime);

	void Shoot();
	void Jump();
	void Throw();
};

