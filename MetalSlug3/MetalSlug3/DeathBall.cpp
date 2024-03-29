#include "DeathBall.h"
#include "ContentsHelper.h"
#include "DeathBallExplosion.h"
#include <EnginePlatform/EngineSound.h>

ADeathBall::ADeathBall()
{
}

ADeathBall::~ADeathBall()
{
	ADeathBallExplosion* Explosion = GetWorld()->SpawnActor<ADeathBallExplosion>();
	Explosion->SetActorLocation(GetActorLocation());

	UEngineSound::SoundPlay("RocketLauncher_Hit.mp3");
}

void ADeathBall::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->SetImage("DeathBall.png");
	Renderer->CreateAnimation("DeathBall", "DeathBall.png", 0, 7,0.05f, true);
	Renderer->ChangeAnimation("DeathBall", false, 0, 0.05f);

	Collider = CreateCollision(MT3CollisionOrder::EnemyProjectile);
	Collider->SetTransform({ {0,0},{50,50} });
	Collider->SetColType(ECollisionType::Rect);
}

void ADeathBall::Tick(float _DeltaTime)
{
	AddActorLocation(DirVector * Speed * _DeltaTime);

	std::vector<UCollision*> Result;
	if (Collider->CollisionCheck(MT3CollisionOrder::Player, Result))
	{
		Destroy();
	}

	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		Destroy();
	}
}
