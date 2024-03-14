#include "TitleScreen.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCore.h>
#include "ContentsHelper.h"
#include <EnginePlatform/EngineSound.h>

TitleScreen::TitleScreen()
{
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::BeginPlay()
{
	Renderer = CreateImageRenderer(0);
	Renderer->SetImage("TitleScreen.bmp");
	Renderer->SetTransform({ {400,300},{800,600} });

	Message = CreateImageRenderer(1);
	Message->SetImage("TitleMessage.png");
	Message->SetTransform({ {400,470},{546,24} });

	UEngineSound::SoundPlay("MS3_Title.ogg");
}

void TitleScreen::Tick(float _DeltaTime)
{
	if (UEngineInput::IsDown(VK_RETURN))
	{
		GEngine->ChangeLevel("CharacterSelect");
		UEngineSound::SoundPlay("Select.ogg");
		UContentsHelper::BGMPlayer = UEngineSound::SoundPlay("BGM.ogg");
		UContentsHelper::BGMPlayer.Loop();
	}

	AccBlink += _DeltaTime;
	if (AccBlink > BlinkTime)
	{
		AccBlink = 0.f;
		if (BlinkNum % 2 == 0)
		{
			Message->ActiveOff();
		}
		else
		{
			Message->ActiveOn();
		}
		++BlinkNum;
	}
}
