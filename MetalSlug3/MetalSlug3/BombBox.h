#pragma once
#include "Item.h"
class BombBox : public AItem
{
public:
	// constructor destructor
	BombBox();
	~BombBox();

	// delete Function
	BombBox(const BombBox& _Other) = delete;
	BombBox(BombBox&& _Other) noexcept = delete;
	BombBox& operator=(const BombBox& _Other) = delete;
	BombBox& operator=(BombBox&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Action() override;
};

