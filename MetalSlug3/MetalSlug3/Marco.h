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
	UImageRenderer* UpperBodyRenderer;
	UImageRenderer* LowerBodyRenderer;
	UImageRenderer* AllBodyRenderer;
	UImageRenderer* ZombieArmRenderer;
	UImageRenderer* ZombieLaunchEffectRenderer;
	UImageRenderer* ZombieProjectileRenderer;

	void Shoot();
	void Jump();
	void Throw();

	bool isRight = true;

	FVector Dir = FVector::Zero;
	float Speed = 300.0f;
};

