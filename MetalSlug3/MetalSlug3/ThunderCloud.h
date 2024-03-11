#pragma once
#include "Item.h"
class ThunderCloud : public AItem
{
public:
	// constructor destructor
	ThunderCloud();
	~ThunderCloud();

	// delete Function
	ThunderCloud(const ThunderCloud& _Other) = delete;
	ThunderCloud(ThunderCloud&& _Other) noexcept = delete;
	ThunderCloud& operator=(const ThunderCloud& _Other) = delete;
	ThunderCloud& operator=(ThunderCloud&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Action() override;
};

