#pragma once
#include "Enemy.h"
#include <EnginePlatform/EngineSound.h>
class AHelicopter : public AEnemy
{
public:
	// constructor destructor
	AHelicopter();
	~AHelicopter();

	// delete Function
	AHelicopter(const AHelicopter& _Other) = delete;
	AHelicopter(AHelicopter&& _Other) noexcept = delete;
	AHelicopter& operator=(const AHelicopter& _Other) = delete;
	AHelicopter& operator=(AHelicopter&& _Other) = delete;

	void StateChange(HelicopterState _State);
	FVector Offset = { 0,-300 };

	bool IsDependent = false;
	bool IsDeath = false;;

	float CP_Left = 6615.0f;
	float CP_Right = 7130.0f;
	float CP_Top = 1035.0f;
	float CP_Bottom = 1135.0f;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);
	void None(float _DeltaTime);
	virtual void Move(float _DeltaTime);
	void Aiming(float _DeltaTime);
	virtual void Shoot(float _DeltaTime);
	void Death(float _DeltaTime);

	void NoneStart();
	virtual void MoveStart();
	void AimingStart();
	virtual void ShootStart();
	void DeathStart();

	HelicopterState CurState = HelicopterState::None;
	std::string CurAnimName = "None";

	class ALeaderHelicopter* Leader = nullptr;

	FVector MoveVector = FVector::Left;
	FVector ShootVector = FVector::Zero;

	FVector AccelDir = FVector::Left;

	void DirCheck();

	float Speed = 0.0f;
	float Accel = 700.0f;
	float MaxSpeed = 500.0f;
	float ShootCoolDown = 1.0f;
	float MoveCoolDown = 1.0f;
	float AccMove = 0.0f;
	float AccAiming = 0.0f;

	int Bullet = 3;
	float BulletCoolDown = 0.1f;
	float AccBullet = 0.0f;

	float DamagedEffectTime = 0.02f;
	float DamagedEffectAcc = 0.0f;

	UEngineSoundPlayer PropellerSound;

	int PrevHp = -1;
};

