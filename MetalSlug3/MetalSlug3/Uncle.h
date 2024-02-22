#pragma once
#include "Human.h"
class AUncle : public AHuman
{
public:
	// constructor destructor
	AUncle();
	~AUncle();

	// delete Function
	AUncle(const AUncle& _Other) = delete;
	AUncle(AUncle&& _Other) noexcept = delete;
	AUncle& operator=(const AUncle& _Other) = delete;
	AUncle& operator=(AUncle&& _Other) = delete;

	void StateChange(HumanState _State);
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);

	void None(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Death(float _DeltaTime);

	void NoneStart();
	void IdleStart();
	void DeathStart();
};

