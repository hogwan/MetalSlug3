#pragma once
#include "Human.h"
class ADoctor : public AHuman
{
public:
	// constructor destructor
	ADoctor();
	~ADoctor();

	// delete Function
	ADoctor(const ADoctor& _Other) = delete;
	ADoctor(ADoctor&& _Other) noexcept = delete;
	ADoctor& operator=(const ADoctor& _Other) = delete;
	ADoctor& operator=(ADoctor&& _Other) = delete;

	void StateChange(HumanState _State);
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);

	void None(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Run(float _DeltaTime);
	void Death(float _DeltaTime);

	void NoneStart();
	void IdleStart();
	void RunStart();
	void DeathStart();

};

