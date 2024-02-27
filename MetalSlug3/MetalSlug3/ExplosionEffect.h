#pragma once
#include <EngineCore/Actor.h>
class AExplosionEffect : public AActor
{
public:
	// constructor destructor
	AExplosionEffect();
	~AExplosionEffect();

	// delete Function
	AExplosionEffect(const AExplosionEffect& _Other) = delete;
	AExplosionEffect(AExplosionEffect&& _Other) noexcept = delete;
	AExplosionEffect& operator=(const AExplosionEffect& _Other) = delete;
	AExplosionEffect& operator=(AExplosionEffect&& _Other) = delete;

	void SetSize(FVector _Size)
	{
		Size = _Size;
		Renderer->SetTransform({ {0,0},Size });
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;
	FVector Size = { 500,500 };
};

