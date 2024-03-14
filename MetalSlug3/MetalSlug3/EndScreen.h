#pragma once
#include <EngineCore/Actor.h>
class EndScreen : public AActor
{
public:
	// constructor destructor
	EndScreen();
	~EndScreen();

	// delete Function
	EndScreen(const EndScreen& _Other) = delete;
	EndScreen(EndScreen&& _Other) noexcept = delete;
	EndScreen& operator=(const EndScreen& _Other) = delete;
	EndScreen& operator=(EndScreen&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	std::vector<class MissionStartChar*> Characters;

	float AccWait = 0.f;
	float WaitTime = 1.f;

	float AccEnd = 0.0f;
	float EndTime = 5.f;

	bool Trigger = false;
};

