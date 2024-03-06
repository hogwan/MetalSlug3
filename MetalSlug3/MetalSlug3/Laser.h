#pragma once
#include <EngineCore/Actor.h>
class ALaser : public AActor
{
public:
	// constructor destructor
	ALaser();
	~ALaser();

	// delete Function
	ALaser(const ALaser& _Other) = delete;
	ALaser(ALaser&& _Other) noexcept = delete;
	ALaser& operator=(const ALaser& _Other) = delete;
	ALaser& operator=(ALaser&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void GroundUp();

	float Speed = 200.0f;

	UImageRenderer* Lazer = nullptr;
	UImageRenderer* GroundEffect = nullptr;
	UCollision* Collider = nullptr;
};

