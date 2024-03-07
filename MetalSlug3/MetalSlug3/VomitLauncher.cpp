#include "VomitLauncher.h"
#include "ContentsHelper.h"
#include "Marco.h"
#include "ZombieVomitProjectile.h"

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
		LastShootVector = { 12.f,37.f };
		Renderer->ChangeAnimation("Launch_Right");

	}
	else if (UContentsHelper::Player->DirState == EActorDir::Left)
	{
		Renderer->CreateAnimation("Launch_Left", "Marco_VomitLaunchEffect.png", 40, 78, 0.08f, false);
		InitialShootVector = { -12.f,10.f };
		LastShootVector = { -12.f,37.f };
		Renderer->ChangeAnimation("Launch_Left");
	}

	InitialShootVector.Normalize2D();
	LastShootVector.Normalize2D();
	ShootVector = InitialShootVector;

}

void AVomitLauncher::Tick(float _DeltaTime)
{
	ShootVector.RotationZToDeg(1.f * _DeltaTime);

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

	for (int t = 0; t < 30; t++)
	{
		AZombieVomitProjectile* VomitProjectile = GetWorld()->SpawnActor<AZombieVomitProjectile>();
		VomitProjectiles.push_back(VomitProjectile);

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

		FVector ProjectilePosition = FVector::Zero;
		ProjectilePosition.X = 50 * t;

		float tanTheta = ShootVector.Y / ShootVector.X;
		ProjectilePosition.Y = (((gravity * pow(t, 2)) / (2 * pow(InitialVelocity.X, 2)))) - tanTheta * t;

		VomitProjectile->SetActorLocation(GetActorLocation() + ProjectilePosition);

		std::vector<UCollision*> Result;
		if (VomitProjectile->GetCollider()->CollisionCheck(MT3CollisionOrder::Enemy, Result)
			|| VomitProjectile->GetCollider()->CollisionCheck(MT3CollisionOrder::Boss, Result))
		{
			DamageLogic();
			break;
		}
	}
}

void AVomitLauncher::DamageLogic()
{
}

