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
	//배경색 153,217,234
	{
		UpperBodyRenderer = CreateImageRenderer(1);
		UpperBodyRenderer->SetImage("UpperBody_Idle_Right_0.bmp");
		UpperBodyRenderer->SetTransform({ { 0,-25 }, { 100, 100 } });
		UpperBodyRenderer->SetImageCuttingTransform({ {0,0}, {100, 100} });
	}


	{
		LowerBodyRenderer = CreateImageRenderer(0);
		LowerBodyRenderer->SetImage("LowerBody_Idle_Right_0.bmp");
		LowerBodyRenderer->SetTransform({ { 0,50 }, { 100, 100 } });
		LowerBodyRenderer->SetImageCuttingTransform({ {0,0}, {100, 100} });
	}
	SetActorLocation({ 100, 100 });
}

void Marco::Tick(float _DeltaTime)
{
	if (true == EngineInput::IsPress(VK_LEFT))
	{
		UpdateStatus |= Move;
		AddActorLocation(FVector::Left * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_RIGHT))
	{
		UpdateStatus |= Move;
		AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_UP))
	{
		UpdateStatus |= AimingUp;
	}

	if (true == EngineInput::IsPress(VK_DOWN))
	{
		if (InAir)
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
	//                랜더상태처리(애니메이션)            //
	////////////////////////////////////////////////////////


	UpdateStatus = 0;
}