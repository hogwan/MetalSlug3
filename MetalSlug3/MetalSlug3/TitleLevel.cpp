#include "TitleLevel.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EnginePlatform/EngineSound.h>
#include "TitleScreen.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::BeginPlay()
{
	UEngineDirectory NewPath;
	NewPath.MoveParent();
	NewPath.Move("MT3Resource");
	NewPath.Move("TitleLevel");

	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}
}

void TitleLevel::Tick(float _DeltaTime)
{
	if (!Trigger)
	{
		AccWait += _DeltaTime;
		if (AccWait > WaitTime)
		{
			SpawnActor<TitleScreen>();
			Trigger = true;
		}
	}
}
