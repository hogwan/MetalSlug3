#pragma once
#include "Human.h"
class AMan2 : public AHuman
{
public:
	// constructor destructor
	AMan2();
	~AMan2();

	// delete Function
	AMan2(const AMan2& _Other) = delete;
	AMan2(AMan2&& _Other) noexcept = delete;
	AMan2& operator=(const AMan2& _Other) = delete;
	AMan2& operator=(AMan2&& _Other) = delete;

	void StateChange(HumanState _State);
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);

	void None(float _DeltaTime);
	void Move(float _DeltaTime);
	void Run(float _DeltaTime);
	void Death(float _DeltaTime);

	void NoneStart();
	void MoveStart();
	void RunStart();
	void DeathStart();
};

