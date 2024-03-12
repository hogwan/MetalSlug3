#include "Door.h"
#include "DoorEffect.h"

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
}

void Door::Tick(float _DeltaTime)
{
	Speed += Accel * _DeltaTime;
	if (GetActorLocation().Y < 355.f)
	{
		AddActorLocation(FVector::Down * Speed * _DeltaTime);
	}
	else if (!Trigger)
	{
		DoorEffect* Effect = GetWorld()->SpawnActor<DoorEffect>();
		Effect->SetActorLocation({ GetActorLocation().X,GetActorLocation().Y + 160.f });
		Trigger = true;
	}
}
