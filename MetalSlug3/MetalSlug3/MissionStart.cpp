#include "MissionStart.h"
#include "MissionStartChar.h"

MissionStart::MissionStart()
{
}

MissionStart::~MissionStart()
{
}

void MissionStart::BeginPlay()
{
	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { -86,-100 };
		ch->SetActorLocation({200,230});
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
		ch->SetActorLocation({ 250,355 });
		ch->SetChar("S");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { -49,100 };
		ch->SetActorLocation({ 313,355 });
		ch->SetChar("T");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = FVector::Down * 100.f;
		ch->SetActorLocation({ 370,355 });
		ch->SetChar("A");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { 30,100 };
		ch->SetActorLocation({ 432,355 });
		ch->SetChar("R");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { 49,100 };
		ch->SetActorLocation({ 492,355 });
		ch->SetChar("T");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}

	{
		MissionStartChar* ch = GetWorld()->SpawnActor<MissionStartChar>();
		FVector MoveVector = { 66, 100 };
		ch->SetActorLocation({ 555,355 });
		ch->SetChar("!");
		ch->SetMoveDir(MoveVector);
		Characters.push_back(ch);
	}
}

void MissionStart::Tick(float _DeltaTime)
{
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

void MissionStart::Blink(float _DeltaTime)
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
