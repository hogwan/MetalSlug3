#pragma once
#include "Human.h"
class AWoman : public AHuman
{
public:
	// constructor destructor
	AWoman();
	~AWoman();

	// delete Function
	AWoman(const AWoman& _Other) = delete;
	AWoman(AWoman&& _Other) noexcept = delete;
	AWoman& operator=(const AWoman& _Other) = delete;
	AWoman& operator=(AWoman&& _Other) = delete;

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

