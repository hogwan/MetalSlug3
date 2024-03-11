#pragma once
#include "Item.h"
class RocketLauncher : public AItem
{
public:
	// constructor destructor
	RocketLauncher();
	~RocketLauncher();

	// delete Function
	RocketLauncher(const RocketLauncher& _Other) = delete;
	RocketLauncher(RocketLauncher&& _Other) noexcept = delete;
	RocketLauncher& operator=(const RocketLauncher& _Other) = delete;
	RocketLauncher& operator=(RocketLauncher&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Action() override;
};

