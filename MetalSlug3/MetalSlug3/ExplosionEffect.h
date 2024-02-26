#pragma once
#include <EngineCore/Actor.h>
class ExplosionEffect : public AActor
{
public:
	// constructor destructor
	ExplosionEffect();
	~ExplosionEffect();

	// delete Function
	ExplosionEffect(const ExplosionEffect& _Other) = delete;
	ExplosionEffect(ExplosionEffect&& _Other) noexcept = delete;
	ExplosionEffect& operator=(const ExplosionEffect& _Other) = delete;
	ExplosionEffect& operator=(ExplosionEffect&& _Other) = delete;

	void SetSize(FVector _Size)
	{
		Size = _Size;
		Renderer->SetTransform({ {0,0},Size });
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
	FVector Size = { 500,500 };
};

