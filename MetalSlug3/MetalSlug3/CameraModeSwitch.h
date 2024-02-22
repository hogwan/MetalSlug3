#pragma once
#include <EngineCore/Actor.h>
class ACameraModeSwitch : public AActor
{
public:
	ACameraModeSwitch();
	~ACameraModeSwitch();

	ACameraModeSwitch(const ACameraModeSwitch& _Other) = delete;
	ACameraModeSwitch(ACameraModeSwitch&& _Other) noexcept = delete;
	ACameraModeSwitch& operator=(const ACameraModeSwitch& _Other) = delete;
	ACameraModeSwitch& operator=(ACameraModeSwitch&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UCollision* Collider = nullptr;
};

