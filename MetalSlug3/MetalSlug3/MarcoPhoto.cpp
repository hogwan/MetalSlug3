#include "MarcoPhoto.h"
#include <EngineCore\EngineCore.h>
#include <EngineBase/EngineTime.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineSound.h>
#include "Door.h"
#include "ContentsHelper.h"

MarcoPhoto::MarcoPhoto()
{
}

MarcoPhoto::~MarcoPhoto()
{
}

void MarcoPhoto::BeginPlay()
{
	ThisRenderer = CreateImageRenderer(2);
	ThisRenderer->SetImage("MarcoSelectedAnim.png");
	ThisRenderer->SetTransform({ {0,0} , {170, 325} });
	ThisRenderer->SetImageCuttingTransform({ {0,0}, {64, 120} });
	ThisRenderer->CreateAnimation("Marco_Selected", "MarcoSelectedAnim.png", 0, 1, 0.08f, false);

	SetActorLocation({ 133.0f, 355.0f });
}

void MarcoPhoto::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (NextTime < 0.0f)
	{
		GEngine->ChangeLevel("Play");
		UContentsHelper::BGMPlayer.Off();
		UContentsHelper::BGMPlayer = UEngineSound::SoundPlay("MainBGM.mp3");
		UContentsHelper::BGMPlayer.Loop();
		UEngineSound::SoundPlay("Mission2Start.mp3");
	}

	if (isEntered)
	{
		NextTime -= _DeltaTime;
	}
	else
	{
		if (true == UEngineInput::IsDown(VK_RETURN))
		{
			UEngineSound::SoundPlay("Marco.mp3");
			ThisRenderer->ChangeAnimation("Marco_Selected");
			GetWorld()->SpawnActor<Door>();
			isEntered = true;
		}
	}
}