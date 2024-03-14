#include "MetalSlug3Core.h"
#include "CharacterSelect.h"
#include "PlayLevel.h"
#include "TitleLevel.h"
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

void MetalSlug3Core::End()
{
}