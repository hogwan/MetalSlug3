#pragma once
#include <EngineCore/Actor.h>
class CEOsecretary : public AActor
{
public:
	// constructor destructor
	CEOsecretary();
	~CEOsecretary();

	// delete Function
	CEOsecretary(const CEOsecretary& _Other) = delete;
	CEOsecretary(CEOsecretary&& _Other) noexcept = delete;
	CEOsecretary& operator=(const CEOsecretary& _Other) = delete;
	CEOsecretary& operator=(CEOsecretary&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	int PrevFrame = -1;

	UImageRenderer* Renderer = nullptr;
};

