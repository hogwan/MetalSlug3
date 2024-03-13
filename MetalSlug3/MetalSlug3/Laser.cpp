#include "Laser.h"
#include "ContentsHelper.h"
#include "Marco.h"
#include "Monoliths.h"
#include <EnginePlatform/EngineSound.h>

ALaser::ALaser()
{
	UEngineSound::SoundPlay("MonoEyes_UFO_Lazer.mp3");
}

ALaser::~ALaser()
{
	FVector CameraPos = GetWorld()->GetCameraPos();

	std::vector<float> SpawnX;
	float Interval = 800.f / 7.f;
	float Initial = 0.f;
	for (int i = 0; i < 7; i++)
	{
		float X = 0.f;
		if (i == 0)
		{
			X = CameraPos.X + Interval/2.f;
			Initial = X;
		}
		else
		{
			X = Initial + Interval * i;
		}

		SpawnX.push_back(X);
	}

	int SpawnNum = 0;
	if (GetActorLocation().X > CameraPos.X + Interval * 6.f)
	{
		SpawnNum = 6;
	}
	else if (GetActorLocation().X > CameraPos.X + Interval * 5.f)
	{
		SpawnNum = 5;
	}
	else if (GetActorLocation().X > CameraPos.X + Interval * 4.f)
	{
		SpawnNum = 4;
	}
	else if (GetActorLocation().X > CameraPos.X + Interval * 3.f)
	{
		SpawnNum = 3;
	}
	else if (GetActorLocation().X > CameraPos.X + Interval * 2.f)
	{
		SpawnNum = 2;
	}
	else if (GetActorLocation().X > CameraPos.X + Interval * 1.f)
	{
		SpawnNum = 1;
	}
	else
	{
		SpawnNum = 0;
	}

	AMonoliths* Monoliths = GetWorld()->SpawnActor<AMonoliths>();
	Monoliths->SetActorLocation({ SpawnX[SpawnNum],CameraPos.Y + 1});
	Monoliths->GetRenderer()->SetOrder(static_cast<MT3RenderOrder>(SpawnNum + 11));
}

void ALaser::BeginPlay()
{
	FVector PlayerPos = UContentsHelper::Player->GetActorLocation();
	SetActorLocation({ PlayerPos.X, 2400.f });

	Lazer = CreateImageRenderer(MT3RenderOrder::UFO_Lazer);
	Lazer->SetTransform({ {0,0},{500,3000} });
	Lazer->CreateAnimation("Lazer", "LazerAiming.png", 0, 2, 0.01f, true);
	Lazer->ChangeAnimation("Lazer", false, 0, 0.02f);

	GroundEffect = CreateImageRenderer(MT3RenderOrder::UFO_LazerGroundEffect);
	GroundEffect->SetTransform({ {0,0},{500,500} });
	GroundEffect->CreateAnimation("GroundEffect", "LazerAiming_GroundEffect.png", 0, 5, 0.03f, true);
	GroundEffect->ChangeAnimation("GroundEffect", false, 0, 0.02f);

	Collider = CreateCollision(MT3CollisionOrder::Lazer);
	Collider->SetScale({ 10,20 });
	Collider->SetPosition({ 0,-10 });
	Collider->SetColType(ECollisionType::Rect);

	Destroy(2.4f);
}

void ALaser::Tick(float _DeltaTime)
{
	FVector PlayerPos = UContentsHelper::Player->GetActorLocation();

	if (abs(PlayerPos.X - GetActorLocation().X) > 1.0f)
	{
		if (GetActorLocation().X < PlayerPos.X)
		{
			AddActorLocation(FVector::Right * Speed * _DeltaTime);
		}
		else
		{
			AddActorLocation(FVector::Left * Speed * _DeltaTime);
		}
	}

	GroundUp();
	AirCheck();
}

void ALaser::GroundUp()
{
	while (true)
	{
		Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 15, Color8Bit::MagentaA);
		std::vector<UCollision*> Result;

		if (Color == Color8Bit(255, 0, 255, 0) || Collider->CollisionCheck(MT3CollisionOrder::Monoliths, Result))
		{
			AddActorLocation(FVector::Up);
		}
		else
		{
			break;
		}
	}
}

void ALaser::AirCheck()
{
	while (true)
	{
		Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 15, Color8Bit::MagentaA);
		std::vector<UCollision*> Result;
		if (Color != Color8Bit(255, 0, 255, 0) && !(Collider->CollisionCheck(MT3CollisionOrder::Monoliths, Result)))
		{
			AddActorLocation(FVector::Down);
		}
		else break;
	}
}
