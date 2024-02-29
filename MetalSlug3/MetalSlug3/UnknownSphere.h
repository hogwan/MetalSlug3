#pragma once
#include <EngineCore/Actor.h>
class AUnknownSphere : public AActor
{
public:
	// constructor destructor
	AUnknownSphere();
	~AUnknownSphere();

	// delete Function
	AUnknownSphere(const AUnknownSphere& _Other) = delete;
	AUnknownSphere(AUnknownSphere&& _Other) noexcept = delete;
	AUnknownSphere& operator=(const AUnknownSphere& _Other) = delete;
	AUnknownSphere& operator=(AUnknownSphere&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;
};

