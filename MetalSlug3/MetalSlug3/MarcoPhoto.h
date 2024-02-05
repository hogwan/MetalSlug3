#pragma once
#include <EngineCore/Actor.h>
class MarcoPhoto : public AActor
{
public:
	// constructor destructor
	MarcoPhoto();
	~MarcoPhoto();

	// delete Function
	MarcoPhoto(const MarcoPhoto& _Other) = delete;
	MarcoPhoto(MarcoPhoto&& _Other) noexcept = delete;
	MarcoPhoto& operator=(const MarcoPhoto& _Other) = delete;
	MarcoPhoto& operator=(MarcoPhoto&& _Other) = delete;

	void BeginPlay() override;

private:
	UImageRenderer* ThisRenderer = nullptr;
};

