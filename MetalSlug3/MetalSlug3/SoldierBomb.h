#pragma once
#include <EngineCore/Actor.h>
class ASoldierBomb : public AActor
{
public:
	// constructor destructor
	ASoldierBomb();
	~ASoldierBomb();

	// delete Function
	ASoldierBomb(const ASoldierBomb& _Other) = delete;
	ASoldierBomb(ASoldierBomb&& _Other) noexcept = delete;
	ASoldierBomb& operator=(const ASoldierBomb& _Other) = delete;
	ASoldierBomb& operator=(ASoldierBomb&& _Other) = delete;

	void SetMoveVector(FVector _MoveVector)
	{
		MoveVector = _MoveVector;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void GravityCheck(float _DeltaTime);
		 
	void FallCheck();
		 
	void HitCheck();

private:
	FVector Dir = FVector::Zero;
	FVector MoveVector = FVector::Zero;
	FVector Gravity = { 0.0f,800.0f };

	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;

};

