#include "MissionComplete.h"
#include "MissionStartChar.h"

MissionComplete::MissionComplete()
{
}

MissionComplete::~MissionComplete()
{
}

void MissionComplete::BeginPlay()
{
	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { -86,-100 };
		ch->SetActorLocation({ 200,230 });
		ch->SetChar("M");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { -49,-100 };
		ch->SetActorLocation({ 250,230 });
		ch->SetChar("I");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { -32,-100 };
		ch->SetActorLocation({ 297,230 });
		ch->SetChar("S");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { -14,-100 };
		ch->SetActorLocation({ 358,230 });
		ch->SetChar("S");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { 36,-100 };
		ch->SetActorLocation({ 408,230 });
		ch->SetChar("I");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { 43,-100 };
		ch->SetActorLocation({ 455,230 });
		ch->SetChar("O");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { 57,-100 };
		ch->SetActorLocation({ 517,230 });
		ch->SetChar("N");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { 127,-100 };
		ch->SetActorLocation({ 615,230 });
		ch->SetChar("2");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { -66,100 };
		ch->SetActorLocation({ 165,355 });
		ch->SetChar("C");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { -49,100 };
		ch->SetActorLocation({ 227,355 });
		ch->SetChar("O");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = FVector::Down * 100.f;
		ch->SetActorLocation({ 289,355 });
		ch->SetChar("M");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { 30,100 };
		ch->SetActorLocation({ 351,355 });
		ch->SetChar("P");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { 49,100 };
		ch->SetActorLocation({ 407,355 });
		ch->SetChar("L");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { 66, 100 };
		ch->SetActorLocation({ 467,355 });
		ch->SetChar("E");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { 66, 100 };
		ch->SetActorLocation({ 527,355 });
		ch->SetChar("T");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { 66, 100 };
		ch->SetActorLocation({ 587,355 });
		ch->SetChar("E");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { 66, 100 };
		ch->SetActorLocation({ 640,355 });
		ch->SetChar("!");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}
}

void MissionComplete::Tick(float _DeltaTime)
{
	AccWaitTime += _DeltaTime;
	if (AccWaitTime < WaitTime) return;

	if (RemainBlink <= 0)
	{
		for (MissionStartChar* ch : Characters)
		{
			ch->MoveOn = true;
		}
	}
	else
	{
		Blink(_DeltaTime);
	}
}

void MissionComplete::Blink(float _DeltaTime)
{
	if (TurnOn)
	{
		AccTurnOff += _DeltaTime;

		if (AccTurnOff > TurnTime)
		{
			TurnOn = false;
			TurnOff = true;
			AccTurnOff = 0.0f;
			for (MissionStartChar* ch : Characters)
			{
				ch->GetRenderer()->ActiveOff();
			}
		}
	}

	if (TurnOff)
	{
		AccTurnOn += _DeltaTime;

		if (AccTurnOn > TurnTime)
		{
			TurnOn = true;
			TurnOff = false;
			AccTurnOn = 0.0f;
			--RemainBlink;
			for (MissionStartChar* ch : Characters)
			{
				ch->GetRenderer()->ActiveOn();
			}
		}
	}

}
