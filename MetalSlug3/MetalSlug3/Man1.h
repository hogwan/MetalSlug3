#pragma once
#include "Human.h"
class AMan1 : public AHuman
{
public:
	// constructor destructor
	AMan1();
	~AMan1();

	// delete Function
	AMan1(const AMan1& _Other) = delete;
	AMan1(AMan1&& _Other) noexcept = delete;
	AMan1& operator=(const AMan1& _Other) = delete;
	AMan1& operator=(AMan1&& _Other) = delete;

	void StateChange(HumanState _State);
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);

	void None(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Shock(float _DeltaTime);
	void Death(float _DeltaTime);

	void NoneStart();
	void IdleStart();
	void ShockStart();
	void DeathStart();
};

