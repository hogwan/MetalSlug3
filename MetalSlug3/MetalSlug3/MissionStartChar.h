#pragma once
#include "UIBase.h"
class MissionStartChar : public AUIBase
{
public:
	// constructor destructor
	MissionStartChar();
	~MissionStartChar();

	// delete Function
	MissionStartChar(const MissionStartChar& _Other) = delete;
	MissionStartChar(MissionStartChar&& _Other) noexcept = delete;
	MissionStartChar& operator=(const MissionStartChar& _Other) = delete;
	MissionStartChar& operator=(MissionStartChar&& _Other) = delete;

	void SetChar(std::string c)
	{
		S = c;
	}

	bool MoveOn = false;

	UImageRenderer* GetRenderer()
	{
		return Renderer;
	}

	void SetMoveDir(FVector _MoveDir)
	{
		MoveDir = _MoveDir;
	}
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;

	FVector MoveDir = FVector::Zero;

	std::string S = "";
};

