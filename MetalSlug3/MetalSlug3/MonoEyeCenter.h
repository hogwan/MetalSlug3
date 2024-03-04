#pragma once
#include <EngineCore/Actor.h>
#include "MonoEyes.h"
class MonoEyeCenter : public AActor
{
public:
	// constructor destructor
	MonoEyeCenter();
	~MonoEyeCenter();

	// delete Function
	MonoEyeCenter(const MonoEyeCenter& _Other) = delete;
	MonoEyeCenter(MonoEyeCenter&& _Other) noexcept = delete;
	MonoEyeCenter& operator=(const MonoEyeCenter& _Other) = delete;
	MonoEyeCenter& operator=(MonoEyeCenter&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	std::vector<AMonoEyes*> MonoEyes;
};

