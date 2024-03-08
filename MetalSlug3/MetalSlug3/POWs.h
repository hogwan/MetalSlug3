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
class APOWs : public AMT3Object
{
public:
	// constructor destructor
	APOWs();
	~APOWs();

	// delete Function
	APOWs(const APOWs& _Other) = delete;
	APOWs(APOWs&& _Other) noexcept = delete;
	APOWs& operator=(const APOWs& _Other) = delete;
	APOWs& operator=(APOWs&& _Other) = delete;

	void StateChange(POWsState _State);
	void SetInitialPos(FVector _Pos)
	{
		InitialPos = _Pos;
	}
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);

	virtual void Tied(float _DeltaTime);
	virtual void Liberate(float _DeltaTime);
	virtual void Patrol(float _DeltaTime);
	virtual void Compensation(float _DeltaTime);
	virtual void RunAway(float _DeltaTime);

	virtual void TiedStart();
	virtual void LiberateStart();
	virtual void PatrolStart();
	virtual void CompensationStart();
	virtual void RunAwayStart();

	int CompensationFrame = 8;
	int PrevFrame = -1;

	UImageRenderer* Renderer = nullptr;
	UCollision* Collider = nullptr;

	POWsState CurState = POWsState::Tied;
	FVector InitialPos = FVector::Zero;
	FVector MoveVector = FVector::Left;

	float MoveRange = 50.f;
	float MoveSpeed = 100.f;

	void GravityCheck(float _DeltaTime);
	void GroundUp();
	
};

