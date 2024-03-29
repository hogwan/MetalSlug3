#include "ManZombie3.h"
#include "ManZombie3Projectile.h"

AManZombie3::AManZombie3()
{
}

AManZombie3::~AManZombie3()
{

}

void AManZombie3::BeginPlay()
{
	AZombies::BeginPlay();

	MoveSpeed = 50;
	Hp = 15;
	Range = 200.f;

	LaunchFrame = 9;
	LaunchEffectFrame = 5;
	LaunchEffectOffset_Up = { 0,0 };
	LaunchEffectoffset_Left = { 0,0 };
	LaunchEffectOffset_Right = { 40,0 };
	LaunchEffectScale = { 500,500 };

	ProjectileSpawnOffset_Height = { 0,-50 };
	ProjectileSpawnOffset_Left = { -50,0 };
	ProjectileSpawnOffset_Right = { 50,0 };

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("ManZombie3.png");
	Renderer->SetTransform({ {0,0}, {600,600} });

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({ 50,100 });
	Collider->SetPosition({ 0,-50 });

	LaunchRenderer = CreateImageRenderer(MT3RenderOrder::Particle);
	LaunchRenderer->SetImage("ManZombie3_LaunchEffect.png");

	Renderer->CreateAnimation("Idle_Right", "ManZombie3.png", 0, 6, 0.1f, true);
	Renderer->CreateAnimation("Move_Right", "ManZombie3.png", 7, 18, 0.1f, true);
	Renderer->CreateAnimation("Attack_Right", "ManZombie3.png", 19, 36, 0.1f, false);
	Renderer->CreateAnimation("Falling_Right", "ManZombie3.png", 37, 54, 0.1f, false);
	Renderer->CreateAnimation("DeathExplosion_Right", "ManZombie3.png", 55, 72, 0.1f, false);
	Renderer->CreateAnimation("Stun_Right", "ManZombie3.png", 73, 99, 0.1f, false);
	Renderer->CreateAnimation("Turn_Right", "ManZombie3.png", 100, 108, 0.1f, false);
	Renderer->CreateAnimation("Death_Right", "ManZombie1.png", 77, 91, 0.05f, false);

	Renderer->CreateAnimation("Idle_Left", "ManZombie3.png", 110, 116, 0.1f, true);
	Renderer->CreateAnimation("Move_Left", "ManZombie3.png", 117, 128, 0.1f, true);
	Renderer->CreateAnimation("Attack_Left", "ManZombie3.png", 129, 146, 0.1f, false);
	Renderer->CreateAnimation("Falling_Left", "ManZombie3.png", 147, 164, 0.1f, false);
	Renderer->CreateAnimation("DeathExplosion_Left", "ManZombie3.png", 165, 182, 0.1f, false);
	Renderer->CreateAnimation("Stun_Left", "ManZombie3.png", 183, 209, 0.1f, false);
	Renderer->CreateAnimation("Turn_Left", "ManZombie3.png", 210, 218, 0.1f, false);
	Renderer->CreateAnimation("Death_Left", "ManZombie1.png", 197, 211, 0.05f, false);

	Renderer->CreateAnimation("Lying", "ManZombie3.png", 193, 208, 0.15f, false);

	LaunchRenderer->CreateAnimation("LaunchEffect_Right", "ManZombie3_LaunchEffect.png", 0, 13, 0.1f, false);
	LaunchRenderer->CreateAnimation("LaunchEffect_Left", "ManZombie3_LaunchEffect.png", 20, 33, 0.1f, false);
	LaunchRenderer->ActiveOff();
	LaunchRenderer->ChangeAnimation("LaunchEffect_Left", true, 0, 0.1f);
}

void AManZombie3::Tick(float _DeltaTime)
{
	AZombies::Tick(_DeltaTime);
	GravityCheck(_DeltaTime);
	GroundUp();
	StateUpdate(_DeltaTime);
}

void AManZombie3::Attack(float _DeltaTime, int _LaunchFrame, int _LaunchEffectFrame)
{
	int CurFrame = Renderer->GetCurAnimationFrame();
	if (CurFrame != PrevFrame)
	{
		if (CurFrame == _LaunchFrame)
		{
			AZombiesProjectile* Projectile_0 = GetWorld()->SpawnActor<AManZombie3Projectile>();
			AZombiesProjectile* Projectile_1 = GetWorld()->SpawnActor<AManZombie3Projectile>();
			AZombiesProjectile* Projectile_2 = GetWorld()->SpawnActor<AManZombie3Projectile>();
			AZombiesProjectile* Projectile_3 = GetWorld()->SpawnActor<AManZombie3Projectile>();
			FVector SpawnLocation = FVector::Zero;

			FVector Dir0 = { 5,-4 };
			FVector Dir1 = { 174,-164 };
			FVector Dir2 = { 132,-186 };
			FVector Dir3 = { 88,-201 };

			Projectile_0->SetShootVector(Dir0);
			Projectile_1->SetShootVector(Dir1);
			Projectile_2->SetShootVector(Dir2);
			Projectile_3->SetShootVector(Dir3);

			Projectile_0->SetShootPower(300.0f);
			Projectile_1->SetShootPower(300.0f);
			Projectile_2->SetShootPower(300.0f);
			Projectile_3->SetShootPower(300.0f);


			if (DirState == EActorDir::Right)
			{
				SpawnLocation = GetActorLocation() + ProjectileSpawnOffset_Height + ProjectileSpawnOffset_Right;
				Projectile_0->SetDir(FVector::Right);
				Projectile_1->SetDir(FVector::Right);
				Projectile_2->SetDir(FVector::Right);
				Projectile_3->SetDir(FVector::Right);

				Projectile_0->SetActorLocation(SpawnLocation);
				Projectile_1->SetActorLocation(SpawnLocation);
				Projectile_2->SetActorLocation(SpawnLocation);
				Projectile_3->SetActorLocation(SpawnLocation);
				
			}
			else if (DirState == EActorDir::Left)
			{
				SpawnLocation = GetActorLocation() + ProjectileSpawnOffset_Height + ProjectileSpawnOffset_Left;
				Projectile_0->SetDir(FVector::Left);
				Projectile_1->SetDir(FVector::Left);
				Projectile_2->SetDir(FVector::Left);
				Projectile_3->SetDir(FVector::Left);

				Projectile_0->SetActorLocation(SpawnLocation);
				Projectile_1->SetActorLocation(SpawnLocation);
				Projectile_2->SetActorLocation(SpawnLocation);
				Projectile_3->SetActorLocation(SpawnLocation);
			}
			
		}

		if (CurFrame == _LaunchEffectFrame)
		{
			LaunchRenderer->ActiveOn();
			if (DirState == EActorDir::Right)
			{
				LaunchRenderer->ChangeAnimation("LaunchEffect_Right", true, 0, 0.1f);
				LaunchRenderer->SetTransform({ LaunchEffectOffset_Up + LaunchEffectOffset_Right, LaunchEffectScale });
			}
			else if (DirState == EActorDir::Left)
			{
				LaunchRenderer->ChangeAnimation("LaunchEffect_Left", true, 0, 0.1f);
				LaunchRenderer->SetTransform({ LaunchEffectOffset_Up + LaunchEffectoffset_Left, LaunchEffectScale });
			}

		}
		PrevFrame = CurFrame;
	}
	if (Renderer->IsCurAnimationEnd())
	{
		PrevFrame = -1;
		StateChange(EnemyZombieState::Idle);
		return;
	}
}

void AManZombie3::DeathStart()
{
	UEngineSound::SoundPlay("Zombie_ManDeath.mp3");
	CurAnimName = "Death";
	Collider->ActiveOff();
	DirCheck(CurAnimName);
	Renderer->ChangeAnimation(CurAnimName);
}