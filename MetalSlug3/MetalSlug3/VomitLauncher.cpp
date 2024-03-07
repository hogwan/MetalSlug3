#include "VomitLauncher.h"
#include "ContentsHelper.h"
#include "Marco.h"
#include "ZombieVomitProjectile.h"
#include "Enemy.h"
#include "ExplosionEffect.h"

AVomitLauncher::AVomitLauncher()
{
}

AVomitLauncher::~AVomitLauncher()
{
}

void AVomitLauncher::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->SetTransform({ { 0,0 }, { 500, 500 } });

	if (UContentsHelper::Player->DirState == EActorDir::Right)
	{
		Renderer->CreateAnimation("Launch_Right", "Marco_VomitLaunchEffect.png", 0, 38, 0.08f, false);
		InitialShootVector = { 12.f,10.f };
		LastShootVector = { 12.f,-37.f };
		Renderer->ChangeAnimation("Launch_Right");

	}
	else if (UContentsHelper::Player->DirState == EActorDir::Left)
	{
		Renderer->CreateAnimation("Launch_Left", "Marco_VomitLaunchEffect.png", 40, 78, 0.08f, false);
		InitialShootVector = { -12.f,10.f };
		LastShootVector = { -12.f,-37.f };
		Renderer->ChangeAnimation("Launch_Left");
	}

	InitialShootVector.Normalize2D();
	LastShootVector.Normalize2D();
	ShootVector = InitialShootVector;

}

void AVomitLauncher::Tick(float _DeltaTime)
{
	ShootVector.RotationZToDeg(-10.f * _DeltaTime);

	AccTime += _DeltaTime;
	if (AccTime > CoolTime)
	{
		AccTime = 0.0f;
		for (AZombieVomitProjectile* Projectile : VomitProjectiles)
		{
			Projectile->Destroy();
		}
		VomitProjectiles.clear();

		LaunchLogic();
	}
}

void AVomitLauncher::LaunchLogic()
{
	InitialPosition = GetActorLocation();
	InitialVelocity = ShootVector * ShootPower;

	for (int t = 0; t < 15; t++)
	{
		AZombieVomitProjectile* VomitProjectile = GetWorld()->SpawnActor<AZombieVomitProjectile>();
		VomitProjectiles.push_back(VomitProjectile);

		FVector ProjectilePosition = FVector::Zero;
		ProjectilePosition.X = InitialVelocity.X * t;
		ProjectilePosition.Y = InitialVelocity.Y * t + 0.5f * Gravity * pow(t, 2);

		VomitProjectile->SetActorLocation(GetActorLocation() + ProjectilePosition);
		VomitProjectile->SetNumber(t);

		if (t == 0)
		{
			VomitProjectile->SetDir(ShootVector);
		}
		else
		{
			FVector PrevProjectilePosition = VomitProjectiles[t - 1]->GetActorLocation();
			FVector DirVector = VomitProjectile->GetActorLocation() - PrevProjectilePosition;
			DirVector.Normalize2D();
			VomitProjectile->SetDir(DirVector);
		}

		std::vector<UCollision*> Result;
		if (VomitProjectile->GetCollider()->CollisionCheck(MT3CollisionOrder::Enemy, Result)
			|| VomitProjectile->GetCollider()->CollisionCheck(MT3CollisionOrder::Boss, Result))
		{
			AEnemy* Enemy = dynamic_cast<AEnemy*>(Result[0]->GetOwner());
			Enemy->Damaged(Damage);

			AExplosionEffect* Effect = GetWorld()->SpawnActor<AExplosionEffect>();
			Effect->SetActorLocation(VomitProjectile->GetActorLocation());
			break;
		}

		Color8Bit Color = UContentsHelper::ColMapImage->GetColor(VomitProjectile->GetActorLocation().iX(), VomitProjectile->GetActorLocation().iY(), Color8Bit::MagentaA);
		if (Color == Color8Bit(255, 0, 255, 0))
		{
			AExplosionEffect* Effect = GetWorld()->SpawnActor<AExplosionEffect>();
			Effect->SetActorLocation(VomitProjectile->GetActorLocation());
			break;
		}
	}
}

void AVomitLauncher::DamageLogic()
{
}

