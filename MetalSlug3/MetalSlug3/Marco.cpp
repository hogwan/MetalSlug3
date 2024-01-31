#include "Marco.h"
#include <EngineCore\EngineCore.h>
#include <EngineBase/EngineTime.h>
#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"
#include "Bomb.h"
#include "MarcoStatus.h"




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
		UpdateStatus |= (1 << Move);
		AddActorLocation(FVector::Left * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_RIGHT))
	{
		UpdateStatus |= (1 << Move);
		AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_UP))
	{
		UpdateStatus |= (1 << AimingUp);
	}

	if (true == EngineInput::IsPress(VK_DOWN))
	{
		if (UpdateStatus & (1 << InAir))
		{
			UpdateStatus |= AimingDown;
		}
		else
		{
			UpdateStatus |= Crouch;
		}
	}

	if (true == EngineInput::IsDown('A'))
	{
		UpdateStatus |= Attack;

		ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
		FVector SpawnLocation = GetActorLocation() + FVector{ 70.0f,-10.f,0.f,0.f };
		NewBullet->SetActorLocation(SpawnLocation);
		NewBullet->SetDir(FVector::Right);
	}

	if (true == EngineInput::IsDown('S'))
	{
		if (!InAir)
		{
			InAir = true;
			//점프
		}
	}

	if (true == EngineInput::IsDown('D'))
	{
		UpdateStatus |= Throwing;
		//폭탄던지기
		ABomb* NewBomb = GetWorld()->SpawnActor<ABomb>();
		NewBomb->SetActorLocation(GetActorLocation());
		NewBomb->SetDir(FVector::Right);
	}


	////////////////////////////////////////////////////////
	//                랜더처리                            //
	////////////////////////////////////////////////////////


	UpdateStatus = 0

}