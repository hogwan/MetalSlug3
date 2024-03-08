#pragma once
#include "POWs.h"
class ACEO : public APOWs
{
public:
	// constructor destructor
	ACEO();
	~ACEO();

	// delete Function
	ACEO(const ACEO& _Other) = delete;
	ACEO(ACEO&& _Other) noexcept = delete;
	ACEO& operator=(const ACEO& _Other) = delete;
	ACEO& operator=(ACEO&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Tied(float _DeltaTime) override;
	void Liberate(float _DeltaTime) override;
	void Patrol(float _DeltaTime) override;
	void Compensation(float _DeltaTime) override;
	void RunAway(float _DeltaTime) override;

	void TiedStart() override;
	void LiberateStart() override;
	void PatrolStart() override;
	void CompensationStart() override;
	void RunAwayStart() override;
};

