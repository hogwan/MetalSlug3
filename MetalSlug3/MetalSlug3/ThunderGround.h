#pragma once
#include <EngineCore/Actor.h>
class ThunderGround : public AActor
{
public:
	// constructor destructor
	ThunderGround();
	~ThunderGround();

	// delete Function
	ThunderGround(const ThunderGround& _Other) = delete;
	ThunderGround(ThunderGround&& _Other) noexcept = delete;
	ThunderGround& operator=(const ThunderGround& _Other) = delete;
	ThunderGround& operator=(ThunderGround&& _Other) = delete;

	int ThunderSize = 0;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	int Damage = 3;
	bool Trigger = false;

	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;
};

