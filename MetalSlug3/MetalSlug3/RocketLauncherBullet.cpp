#include "RocketLauncherBullet.h"
#include "Enemy.h"
#include "Monoliths.h"
#include "HugeExplosionEffect.h"
#include "RocketLauncher_LaunchEffect.h"
#include <EnginePlatform/EngineSound.h>

RocketLauncherBullet::RocketLauncherBullet()
{
}

RocketLauncherBullet::~RocketLauncherBullet()
{
	UEngineSound::SoundPlay("RocketLauncher_Hit.mp3");
}

void RocketLauncherBullet::BeginPlay()
{
	ABullet::BeginPlay();

	Speed = 700.0f;
	Damage = 5;

	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->CreateAnimation("Right", "RocketLauncher_Right.png", 0, 6, 0.08f, false);
	Renderer->CreateAnimation("Left", "RocketLauncher_Left.png", 0, 6, 0.08f, false);
	Renderer->CreateAnimation("Up", "RocketLauncher_Up.png", 0, 6, 0.08f, false);
	Renderer->CreateAnimation("Down", "RocketLauncher_Down.png", 0, 6, 0.08f, false);

	Collider = CreateCollision(MT3CollisionOrder::PlayerBullet);
	Collider->SetTransform({ {0,0},{100,20} });

}

void RocketLauncherBullet::Tick(float _DeltaTime)
{
	AMT3Object::Tick(_DeltaTime);

	if (!Trigger)
	{
		RocketLauncher_LaunchEffect* Effect = GetWorld()->SpawnActor<RocketLauncher_LaunchEffect>();
		Effect->SetActorLocation(GetActorLocation());
		Trigger = true;
	}


	if (Dir.X > 0.f)
	{
		Renderer->ChangeAnimation("Right", false, 0, 0.08f);
	}
	else if (Dir.X < 0.f)
	{
		Renderer->ChangeAnimation("Left", false, 0, 0.08f);
	}
	else if (Dir.Y > 0)
	{
		Renderer->ChangeAnimation("Down", false, 0, 0.08f);
	}
	else {
		Renderer->ChangeAnimation("Up", false, 0, 0.08f);
	}


	AddActorLocation(Dir * Speed * _DeltaTime);

	{
		std::vector<UCollision*> Result;
		if (true == Collider->CollisionCheck(MT3CollisionOrder::Enemy, Result)
			|| true == Collider->CollisionCheck(MT3CollisionOrder::Boss, Result))
		{
			AEnemy* Enemy = dynamic_cast<AEnemy*>(Result[0]->GetOwner());
			Enemy->Damaged(Damage);

			AExplosionEffect* Effect = GetWorld()->SpawnActor<AHugeExplosionEffect>();
			Effect->SetActorLocation(GetActorLocation());

			Destroy();
		}
	}

	{
		std::vector<UCollision*> Result;
		if (true == Collider->CollisionCheck(MT3CollisionOrder::Monoliths, Result))
		{
			AMonoliths* Monoliths = dynamic_cast<AMonoliths*>(Result[0]->GetOwner());
			Monoliths->GoDown();

			AExplosionEffect* Effect = GetWorld()->SpawnActor<AExplosionEffect>();
			Effect->SetActorLocation(GetActorLocation());

			Destroy();
		}
	}
}
