#include "Door.h"
#include "DoorEffect.h"
#include "Marco_Idle.h"

Door::Door()
{
}

Door::~Door()
{
}

void Door::BeginPlay()
{
	Renderer = CreateImageRenderer(3);
	Renderer->SetImage("Door.png");
	Renderer->SetTransform({ { 0,0 }, { 170, 325 } });

	SetActorLocation({ 133.0f, 100.0f });

	MI = GetWorld()->SpawnActor<Marco_Idle>();
}

void Door::Tick(float _DeltaTime)
{
	MI->SetActorLocation({ GetActorLocation().X + 10.f, GetActorLocation().Y + 100.f });


	Speed += Accel * _DeltaTime;
	if (GetActorLocation().Y < 355.f)
	{
		AddActorLocation(FVector::Down * Speed * _DeltaTime);
	}
	else if (!Trigger)
	{
		MI->AnimStart = true;
		DoorEffect* Effect = GetWorld()->SpawnActor<DoorEffect>();
		Effect->SetActorLocation({ GetActorLocation().X,GetActorLocation().Y + 160.f });
		Trigger = true;
	}
}
