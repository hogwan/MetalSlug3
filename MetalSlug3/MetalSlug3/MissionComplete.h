#pragma once
#include "UIBase.h"
class MissionComplete : public AUIBase
{
public:
	// constructor destructor
	MissionComplete();
	~MissionComplete();

	// delete Function
	MissionComplete(const MissionComplete& _Other) = delete;
	MissionComplete(MissionComplete&& _Other) noexcept = delete;
	MissionComplete& operator=(const MissionComplete& _Other) = delete;
	MissionComplete& operator=(MissionComplete&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	std::vector<class MissionStartChar*> Characters;

	int RemainBlink = 2;

	void Blink(float _DeltaTime);

	bool TurnOn = true;
	bool TurnOff = false;

	float TurnTime = 0.5f;
	float AccTurnOff = 0.0f;
	float AccTurnOn = 0.0f;

	float AccWaitTime = 0.0f;
	float WaitTime = 2.0f;
};

