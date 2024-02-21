#pragma once
#include <EngineCore/Actor.h>
class AScreenCollision : public AActor
{
public:
	// constructor destructor
	AScreenCollision();
	~AScreenCollision();

	// delete Function
	AScreenCollision(const AScreenCollision& _Other) = delete;
	AScreenCollision(AScreenCollision&& _Other) noexcept = delete;
	AScreenCollision& operator=(const AScreenCollision& _Other) = delete;
	AScreenCollision& operator=(AScreenCollision&& _Other) = delete;

	UCollision* GetCollider()
	{
		return Collider;
	}
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* Collider = nullptr;
};

