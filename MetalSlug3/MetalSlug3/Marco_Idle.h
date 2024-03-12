#pragma once
#include <EngineCore/Actor.h>
class Marco_Idle : public AActor
{
public:
	// constructor destructor
	Marco_Idle();
	~Marco_Idle();

	// delete Function
	Marco_Idle(const Marco_Idle& _Other) = delete;
	Marco_Idle(Marco_Idle&& _Other) noexcept = delete;
	Marco_Idle& operator=(const Marco_Idle& _Other) = delete;
	Marco_Idle& operator=(Marco_Idle&& _Other) = delete;

	bool AnimStart = false;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


	UImageRenderer* Renderer = nullptr;

};

