#include "MetalSlug3Core.h"
#include "CharacterSelect.h"
#include "PlayLevel.h"
#include "TitleLevel.h"
#include "EndLevel.h"
#include <EngineCore\EngineResourcesManager.h>

MetalSlug3Core::MetalSlug3Core()
{
}

MetalSlug3Core::~MetalSlug3Core()
{
}

void MetalSlug3Core::BeginPlay()
{
	MainWindow.SetWindowScale({ 800,600 });
	CreateLevel<TitleLevel>("Title");
	CreateLevel<CharacterSelect>("CharacterSelect");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndLevel>("End");

	ChangeLevel("Title");
}

void MetalSlug3Core::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
	
	if (true == UEngineInput::IsDown(VK_F10))
	{
		GEngine->EngineDebugSwitch();
	}
}