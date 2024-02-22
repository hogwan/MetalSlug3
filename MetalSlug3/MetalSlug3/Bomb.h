#pragma once
#include <EngineCore/Actor.h>
class ABomb : public AActor
{
public:
	// constructor destructor
	ABomb();
	~ABomb();

	ABomb(FVector _Force);

	// delete Function
	ABomb(const ABomb& _Other) = delete;
	ABomb(ABomb&& _Other) noexcept = delete;
	ABomb& operator=(const ABomb& _Other) = delete;
	ABomb& operator=(ABomb&& _Other) = delete;

	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

	void SetMoveVector(FVector _MoveVector)
	{
		MoveVector = _MoveVector;
	}

	int GetDamage()
	{
		return Damage;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;

	void GravityCheck(float _DeltaTime);
	void ReflectionCheck();

	void HitCheck();
	int Damage = 10;

private:
	FVector Dir = FVector::Zero;
	FVector Force = FVector::Zero;
	FVector MoveVector = FVector::Zero;
	FVector Gravity = { 0.0f,800.0f };

	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;

};

