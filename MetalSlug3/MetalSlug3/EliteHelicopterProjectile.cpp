#include "EliteHelicopterProjectile.h"
#include "ContentsHelper.h"
#include "HugeBombExplosionEffect.h"
#include <EnginePlatform/EngineSound.h>

AEliteHelicopterProjectile::AEliteHelicopterProjectile()
{
}

AEliteHelicopterProjectile::~AEliteHelicopterProjectile()
{
	AHugeBombExplosionEffect* Effect = GetWorld()->SpawnActor<AHugeBombExplosionEffect>();
	Effect->SetActorLocation(GetActorLocation());

	UEngineSound::SoundPlay("Destroy_0.mp3");
}

void AEliteHelicopterProjectile::BeginPlay()
{
	AMT3Object::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->SetImage("EliteHelicopter_Projectile.png");
	Renderer->CreateAnimation("Projectile", "EliteHelicopter_Projectile.png", 0, 13, 0.08f, true);
	Renderer->ChangeAnimation("Projectile", false, 0, 0.08f);

	Collider = CreateCollision(MT3CollisionOrder::EnemyProjectile);
	Collider->SetScale({ 30,50 });
	Collider->SetPosition({0,-25});
	Collider->SetColType(ECollisionType::Rect);

}

void AEliteHelicopterProjectile::Tick(float _DeltaTime)
{
	AMT3Object::Tick(_DeltaTime);

	Speed += Accel * _DeltaTime;
	AddActorLocation(FVector::Down * Speed * _DeltaTime);

	FallCheck();
	HitCheck();
}

void AEliteHelicopterProjectile::FallCheck()
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		Destroy();
	}
}

void AEliteHelicopterProjectile::HitCheck()
{
	std::vector<UCollision*> Result;
	if (Collider->CollisionCheck(MT3CollisionOrder::Player, Result))
	{
		Destroy(0.001f);
	}
}
