#include "VomitLauncher.h"
#include "ContentsHelper.h"
#include "Marco.h"
#include "ZombieVomitProjectile.h"
#include "Enemy.h"
#include "ExplosionEffect.h"
#include "VomitExplosionEffect.h"
#include <EnginePlatform/EngineSound.h>
AVomitLauncher::AVomitLauncher()
{
}

AVomitLauncher::~AVomitLauncher()
{
	for (AZombieVomitProjectile* Projectile : VomitProjectiles)
	{
		Projectile->IsDeath = true;
	}
}

void AVomitLauncher::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->SetTransform({ { 0,0 }, { 500, 500 } });

	if (UContentsHelper::Player->DirState == EActorDir::Right)
	{
		Renderer->CreateAnimation("Launch_Right", "Marco_VomitLaunchEffect.png", 0, 43, 0.03f, false);
		InitialShootVector = { 12.f,10.f };
		LastShootVector = { 12.f,-37.f };
		Renderer->ChangeAnimation("Launch_Right");

	}
	else if (UContentsHelper::Player->DirState == EActorDir::Left)
	{
		Renderer->CreateAnimation("Launch_Left", "Marco_VomitLaunchEffect.png", 50, 93, 0.03f, false);
		InitialShootVector = { -12.f,10.f };
		LastShootVector = { -12.f,-37.f };
		Renderer->ChangeAnimation("Launch_Left");
	}

	InitialShootVector.Normalize2D();
	LastShootVector.Normalize2D();
	ShootVector = InitialShootVector;

	UEngineSound::SoundPlay("Zombie_Marco_Vomit.mp3");
}

void AVomitLauncher::Tick(float _DeltaTime)
{
	int CurFrame = Renderer->GetCurAnimationFrame();
	EActorDir PlayerDir = UContentsHelper::Player->DirState;
	if (CurFrame < 24)
	{
		if (PlayerDir == EActorDir::Right)
		{
			ShootVector.RotationZToDeg(-120.f * _DeltaTime);
		}
		else
		{
			ShootVector.RotationZToDeg(120.f * _DeltaTime);
		}
	}
	else
	{
		IsEnd = true;
		if (PlayerDir == EActorDir::Right)
		{
			ShootVector.RotationZToDeg(25.f * _DeltaTime);
		}
		else
		{
			ShootVector.RotationZToDeg(-25.f * _DeltaTime);
		}

		if (Renderer->IsCurAnimationEnd())
		{
			Destroy();
		}
	}

	AccTime += _DeltaTime;
	if (AccTime > CoolTime)
	{
		AccTime = 0.0f;
		for (AZombieVomitProjectile* Projectile : VomitProjectiles)
		{
			Projectile->Destroy();
			Projectile = nullptr;
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
		
		int CurFrame = Renderer->GetCurAnimationFrame();
		if (CurFrame > 23)
		{
			VomitProjectile->RendererEnd = true;
			VomitProjectile->SetEndFrame(CurFrame - 24);
		}

		FVector ProjectilePosition = FVector::Zero;
		ProjectilePosition.X = InitialVelocity.X/2.f * (t+1);
		ProjectilePosition.Y = InitialVelocity.Y/2.f * (t+1) + 0.5f * Gravity * static_cast<float>(pow((t+1), 2));

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

			AExplosionEffect* Effect = GetWorld()->SpawnActor<AVomitExplosionEffect>();
			Effect->SetActorLocation(VomitProjectile->GetActorLocation());
			break;
		}

		Color8Bit Color = UContentsHelper::ColMapImage->GetColor(VomitProjectile->GetActorLocation().iX(), VomitProjectile->GetActorLocation().iY(), Color8Bit::MagentaA);
		if (Color == Color8Bit(255, 0, 255, 0))
		{
			AExplosionEffect* Effect = GetWorld()->SpawnActor<AVomitExplosionEffect>();
			Effect->SetActorLocation(VomitProjectile->GetActorLocation());
			break;
		}
	}
}
