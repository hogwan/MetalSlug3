#include "EndScreen.h"
#include "MissionStartChar.h"
#include <EnginePlatform/EngineSound.h>
#include <EngineCore/EngineCore.h>

EndScreen::EndScreen()
{
}

EndScreen::~EndScreen()
{
}

void EndScreen::BeginPlay()
{
	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		ch->SetActorLocation({ 170,300 });
		ch->SetChar("T");
		ch->GetRenderer()->ActiveOff();
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		ch->SetActorLocation({ 224,300 });
		ch->SetChar("H");
		ch->GetRenderer()->ActiveOff();
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		ch->SetActorLocation({ 280,300 });
		ch->SetChar("A");
		ch->GetRenderer()->ActiveOff();
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		ch->SetActorLocation({ 338,300 });
		ch->SetChar("N");
		ch->GetRenderer()->ActiveOff();
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		ch->SetActorLocation({ 393,300 });
		ch->SetChar("K");
		ch->GetRenderer()->ActiveOff();
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		ch->SetActorLocation({ 485,300 });
		ch->SetChar("Y");
		ch->GetRenderer()->ActiveOff();
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		ch->SetActorLocation({ 542,300 });
		ch->SetChar("O");
		ch->GetRenderer()->ActiveOff();
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		ch->SetActorLocation({ 600,300 });
		ch->SetChar("U");
		ch->GetRenderer()->ActiveOff();
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		ch->SetActorLocation({ 650,300 });
		ch->SetChar("!");
		ch->GetRenderer()->ActiveOff();
		Characters.push_back(ch);
	}
}

void EndScreen::Tick(float _DeltaTime)
{
	if (!Trigger)
	{
		AccWait += _DeltaTime;
		if (AccWait > WaitTime)
		{
			AccWait = 0.f;
			UEngineSound::SoundPlay("Prisioner.mp3");

			for (MissionStartChar* ch : Characters)
			{
				ch->GetRenderer()->ActiveOn();
			}
			Trigger = true;
		}
	}

	AccEnd += _DeltaTime;
	if (AccEnd > EndTime)
	{
		AccEnd = 0.f;
		GEngine->MainWindow.Off();
	}
}
