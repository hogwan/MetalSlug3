#include "EliteHelicopter.h"
#include "EliteHelicopterProjectile.h"
#include "Marco.h"
#include "ContentsHelper.h"
#include "HugeExplosionEffect.h"
#include "RocketLauncher.h"
#include <EnginePlatform/EngineSound.h>
AEliteHelicopter::AEliteHelicopter()
{
	
}

AEliteHelicopter::~AEliteHelicopter()
{
	RocketLauncher* RL = GetWorld()->SpawnActor<RocketLauncher>();
	RL->SetActorLocation(GetActorLocation());

	AHugeExplosionEffect* Effect = GetWorld()->SpawnActor<AHugeExplosionEffect>();
	Effect->SetActorLocation(GetActorLocation());

	UEngineSound::SoundPlay("Destroy_1.mp3");
	PropellerSound.Off();
}

void AEliteHelicopter::BeginPlay()
{
	AEnemy::BeginPlay();
	PropellerSound = UEngineSound::SoundPlay("HelicopterPropeller.mp3");
	PropellerSound.Loop();

	Hp = 40;

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->SetImage("Flying0.png");

	Propeller = CreateImageRenderer(MT3RenderOrder::Propeller);
	Propeller->SetTransform({ {20,-110},{500,500} });
	Propeller->SetImage("Propeller.png");

	Propeller->CreateAnimation("Flying6", "Propeller.png", 0, 4, 0.08f, true);
	Propeller->CreateAnimation("Flying5", "Propeller.png", 5, 9, 0.08f, true);
	Propeller->CreateAnimation("Flying4", "Propeller.png", 10, 14, 0.08f, true);
	Propeller->CreateAnimation("Flying3", "Propeller.png", 15, 19, 0.08f, true);
	Propeller->CreateAnimation("Flying2", "Propeller.png", 20, 24, 0.08f, true);
	Propeller->CreateAnimation("Flying1", "Propeller.png", 25, 29, 0.08f, true);
	Propeller->CreateAnimation("Flying0", "Propeller.png", 30, 34, 0.08f, true);
	Propeller->ChangeAnimation("Flying0");
	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({150,150});
	Collider->SetPosition({ 0,-75 });
	Collider->SetColType(ECollisionType::Rect);

	Hp = 20;
}

void AEliteHelicopter::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);
	if (IsShooting)
	{
		AccLaunchTime += _DeltaTime;
		if (AccLaunchTime > LaunchCoolTime)
		{
			AccLaunchTime = 0.0f;
			AEliteHelicopterProjectile* Projectile = GetWorld()->SpawnActor<AEliteHelicopterProjectile>();
			Projectile->SetActorLocation(GetActorLocation());
			--Bullet;
		}


		if (Bullet <= 0)
		{
			AccLaunchTime = 0.0f;
			IsShooting = false;
			Bullet = 3;
		}
	}
	else
	{
		AccShootTime += _DeltaTime;
		if (AccShootTime > ShootCoolTime)
		{
			AccShootTime = 0.0f;
			IsShooting = true;
		}
	}



	if (Hp <= 0)
	{
		Destroy();
	}

	FVector PlayerPos = UContentsHelper::Player->GetActorLocation();
	FVector TargetVector = { PlayerPos.X, TargetY };
	FVector MoveVector = TargetVector - GetActorLocation();
	Speed = MoveVector.Size2D();
	MoveVector.Normalize2D();

	AddActorLocation(MoveVector * Speed * _DeltaTime);

	if (Speed > 50.0f)
	{
		if (MoveVector.X < 0.0f)
		{
			Renderer->SetImage("Flying0.png");
			Propeller->ChangeAnimation("Flying0",false,0,0.08f);
		}
		else
		{
			Renderer->SetImage("Flying6.png");
			Propeller->ChangeAnimation("Flying6", false, 0, 0.08f);
		}
	}
	else if (Speed > 30.0f)
	{
		if (MoveVector.X < 0.0f)
		{
			Renderer->SetImage("Flying1.png");
			Propeller->ChangeAnimation("Flying1", false, 0, 0.08f);
		}
		else
		{
			Renderer->SetImage("Flying5.png");
			Propeller->ChangeAnimation("Flying5", false, 0, 0.08f);
		}
	}
	else if (Speed > 10.0f)
	{
		if (MoveVector.X < 0.0f)
		{
			Renderer->SetImage("Flying2.png");
			Propeller->ChangeAnimation("Flying2", false, 0, 0.08f);
		}
		else
		{
			Renderer->SetImage("Flying4.png");
			Propeller->ChangeAnimation("Flying4", false, 0, 0.08f);
		}
	}
	else
	{
		Renderer->SetImage("Flying3.png");
		Propeller->ChangeAnimation("Flying3", false, 0, 0.08f);
	}
}
