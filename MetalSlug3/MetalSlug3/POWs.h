#pragma once
#include "MT3Object.h"
enum class POWsState
{
	Tied,
	Liberate,
	Patrol,
	Compensation,
	Runaway,

};
class POWs : public AMT3Object
{
public:
	// constructor destructor
	POWs();
	~POWs();

	// delete Function
	POWs(const POWs& _Other) = delete;
	POWs(POWs&& _Other) noexcept = delete;
	POWs& operator=(const POWs& _Other) = delete;
	POWs& operator=(POWs&& _Other) = delete;

	void StateChange(POWsState _State);
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);

	void Tied(float _DeltaTime);
	void Liberate(float _DeltaTime);
	void Patrol(float _DeltaTime);
	void Compensation(float _DeltaTime);
	void RunAway(float _DeltaTime);

	void TiedStart();
	void LiberateStart();
	void PatrolStart();
	void CompensationStart();
	void RunAwayStart();

	int CompensationFrame = 8;

	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;

	POWsState CurState = POWsState::Tied;
	FVector InitialPos = FVector::Zero;
	
};

