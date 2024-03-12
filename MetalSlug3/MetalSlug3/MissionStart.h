#pragma once
#include "UIBase.h"
class MissionStart : public AUIBase
{
public:
	// constructor destructor
	MissionStart();
	~MissionStart();

	// delete Function
	MissionStart(const MissionStart& _Other) = delete;
	MissionStart(MissionStart&& _Other) noexcept = delete;
	MissionStart& operator=(const MissionStart& _Other) = delete;
	MissionStart& operator=(MissionStart&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	std::vector<class MissionStartChar*> Characters;

	int RemainBlink = 3;

	void Blink(float _DeltaTime);
	
	bool TurnOn = true;
	bool TurnOff = false;

	float TurnTime = 0.5f;
	float AccTurnOff = 0.0f;
	float AccTurnOn = 0.0f;
};

