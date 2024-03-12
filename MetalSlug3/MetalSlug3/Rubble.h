#pragma once
#include <EngineCore/Actor.h>

class Rubble : public AActor
{
public:
	// constructor destructor
	Rubble();
	~Rubble();

	// delete Function
	Rubble(const Rubble& _Other) = delete;
	Rubble(Rubble&& _Other) noexcept = delete;
	Rubble& operator=(const Rubble& _Other) = delete;
	Rubble& operator=(Rubble&& _Other) = delete;

	void SetVector(FVector DirVector, float Force)
	{
		CurVector = DirVector * Force;
	}

	UImageRenderer* GetRenderer()
	{
		return Renderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;

	FVector CurVector = FVector::Zero;
	FVector Gravity = FVector::Zero;
	float GravityAccel = 700.0f;
	FVector ResultVector = FVector::Zero;
};

