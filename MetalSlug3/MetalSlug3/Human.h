#pragma once
#include <EngineCore/Actor.h>
class Human : public AActor
{
public:
	// constructor destructor
	Human();
	~Human();

	// delete Function
	Human(const Human& _Other) = delete;
	Human(Human&& _Other) noexcept = delete;
	Human& operator=(const Human& _Other) = delete;
	Human& operator=(Human&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;
};

