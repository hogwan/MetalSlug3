#pragma once
#include "Item.h"
class FlameShot : public AItem
{
public:
	// constructor destructor
	FlameShot();
	~FlameShot();

	// delete Function
	FlameShot(const FlameShot& _Other) = delete;
	FlameShot(FlameShot&& _Other) noexcept = delete;
	FlameShot& operator=(const FlameShot& _Other) = delete;
	FlameShot& operator=(FlameShot&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Action() override;
};

