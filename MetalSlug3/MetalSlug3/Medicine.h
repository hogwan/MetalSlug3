#pragma once
#include "Item.h"
class Medicine : public AItem
{
public:
	// constructor destructor
	Medicine();
	~Medicine();

	// delete Function
	Medicine(const Medicine& _Other) = delete;
	Medicine(Medicine&& _Other) noexcept = delete;
	Medicine& operator=(const Medicine& _Other) = delete;
	Medicine& operator=(Medicine&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Action() override;
};

