#include "DeathBall.h"
#include "ContentsHelper.h"
#include "DeathBallExplosion.h"

ADeathBall::ADeathBall()
{
}

ADeathBall::~ADeathBall()
{
	ADeathBallExplosion* Explosion = GetWorld()->SpawnActor<ADeathBallExplosion>();
	Explosion->SetActorLocation(GetActorLocation());
}

void ADeathBall::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->SetImage("DeathBall.png");
	Renderer->CreateAnimation("DeathBall", "DeathBall.png", 0, 7,0.5f, true);

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
}
