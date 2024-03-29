#include "Van.h"
#include "Soldier.h"
#include "HugeExplosionEffect.h"
#include "ManZombie3.h"
#include <EnginePlatform/EngineSound.h>

AVan::AVan()
{
}

AVan::~AVan()
{
	AHugeExplosionEffect* HugeExplosionEffect = GetWorld()->SpawnActor<AHugeExplosionEffect>();
	HugeExplosionEffect->SetActorLocation(GetActorLocation());

	AManZombie3* Zombie = GetWorld()->SpawnActor<AManZombie3>();
	Zombie->SetActorLocation(GetActorLocation());
	Zombie->StateChange(EnemyZombieState::Idle);

	UEngineSound::SoundPlay("Destroy_0.mp3");
}

void AVan::BeginPlay()
{
	AEnemy::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Van);
	Renderer->SetImage("Van_Idle.png");
	Renderer->SetTransform({ {0,0},{500,500} });

	SoldierSpawnRenderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	SoldierSpawnRenderer->SetImage("Van_SoldierSpawn.png");
	SoldierSpawnRenderer->SetTransform({ {2,-20},{500,500} });
	SoldierSpawnRenderer->CreateAnimation("SoldierSpawn", "Van_SoldierSpawn.png", 0, 8, 0.2f, false);
	SoldierSpawnRenderer->ChangeAnimation("SoldierSpawn");
	SoldierSpawnRenderer->ActiveOff();

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetColType(ECollisionType::Rect);
	Collider->SetScale({ 150,150 });
	Collider->SetPosition({ 0,-75 });

	Hp = MaxHp;
}

void AVan::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);

	if (Spawning)
	{
		int CurFrame = SoldierSpawnRenderer->GetCurAnimationFrame();
		if (PrevFrame != CurFrame && SoldierSpawnRenderer->IsCurAnimationEnd())
		{
			Spawning = false;
			ASoldier* Soldier = GetWorld()->SpawnActor<ASoldier>();
			FVector Offset = { 30.0f,-20.0f };
			Soldier->SetActorLocation(GetActorLocation() + Offset);
			Soldier->StateChange(SoldierState::Idle);
			Soldier->SetPattern(SoldierPattern::Throw);
			SoldierSpawnRenderer->ActiveOff();
			CurFrame = PrevFrame;
		}
	}
	else
	{
		PrevFrame = -1;
		AccSpawnTime += _DeltaTime;
		if (AccSpawnTime > SpawnCoolTime)
		{
			Spawning = true;
			AccSpawnTime = 0.0f;
			SoldierSpawnRenderer->ChangeAnimation("SoldierSpawn", true, 0, 0.2f);
			SoldierSpawnRenderer->ActiveOn();
		}
	}


	if (Hp <= MaxHp / 2)
	{
		Renderer->SetImage("Van_Damaged.png");
	}

	if (Hp <= 0)
	{
		Destroy();
	}
}
