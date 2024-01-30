#include "Marco.h"
#include <EngineCore\EngineCore.h>
#include <EngineBase/EngineTime.h>
#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"
#include "Bomb.h"

Marco::Marco()
{
}

Marco::~Marco()
{
}

void Marco::BeginPlay()
{
	{
		UpperBodyRenderer = CreateImageRenderer(0);
		UpperBodyRenderer->SetPosition({ 0, -25 });
		UpperBodyRenderer->SetImageToScale("UpperBody_Idle_Right_0.bmp");
		// BodyRenderer->SetScale({ 80, 80 });
	}


	{
		LowerBodyRenderer = CreateImageRenderer(0);
		LowerBodyRenderer->SetPosition({ 0, 30 });
		LowerBodyRenderer->SetImageToScale("LowerBody_Idle_Right_0.bmp");
	}
	SetActorLocation({ 100, 100 });
}

void Marco::Tick(float _DeltaTime)
{
	if (true == EngineInput::IsPress(VK_LEFT))
	{
		AddActorLocation(FVector::Left * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_RIGHT))
	{
		AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_UP))
	{
		AddActorLocation(FVector::Up * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_DOWN))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsDown('A'))
	{
		ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
		FVector SpawnLocation = GetActorLocation() + FVector{ 70.0f,-10.f,0.f,0.f };
		NewBullet->SetActorLocation(SpawnLocation);
		NewBullet->SetDir(FVector::Right);
	}

	if (true == EngineInput::IsDown('S'))
	{
		Jump();
	}

	if (true == EngineInput::IsDown('D'))
	{
		ABomb* NewBomb = GetWorld()->SpawnActor<ABomb>();
		NewBomb->SetActorLocation(GetActorLocation());
		NewBomb->SetDir(FVector::Right);
	}

}


void Marco::Jump()
{
}
