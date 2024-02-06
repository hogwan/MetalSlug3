#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"

enum class BodyRenderer
{
	UpperBody,
	LowerBody,
	AllBody,
	ZombieArm,
	ZombieLaunchEffect,
	ZombieProjectile,
};

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

	// 상태 보조 함수
	void GravityCheck(float _DeltaTime);
	// 각 상태마다 언제나 가장 위에 실행되어야 한다.
	void DirCheck(BodyRenderer BodyRendererType);
	void GunCheck(BodyRenderer BodyRendererType);

	void AddDirectionName(std::string& CurAnimName);
	void AddGunTypeName(std::string& CurAnimName);

	EPlayState State = EPlayState::Idle;
	EActorDir DirState = EActorDir::Right;
	EGunType GunType = EGunType::Pistol;

	void StateChange(EPlayState _State);
	void FreeMove(float _DeltaTime);
	void CameraFreeMove(float _DeltaTime);
	
	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Jump(float _DeltaTime);

	void IdleStart();
	void MoveStart();
	void JumpStart();
private:
	std::vector<UImageRenderer*> Renderer;

	std::string CurAnimationName = "None";

	FVector MoveDir = FVector::Zero;
	FVector ShootDir = FVector::Right;
	FVector PrevMoveDir = FVector::Right;

	float Run_Speed = 300.0f;
	float InAir_Speed = 100.0f;
	float Crouch_Speed = 50.0f;

	bool IsZombie = false;
	bool InAir = false;
	bool IsHeavyMachineGun = false;

	int RenderState = 0;
	int PrevRenderState = 0;

	void StateUpdate(float _DeltaTime);

	float FreeMoveSpeed = 1000.0f;

	float Gravity = 500.0f;

};

