#include "LeaderHelicopter.h"
#include "HelicopterBullet.h"
#include "ExplosionEffect.h"
#include "FlameShot.h"

std::list<AHelicopter*> ALeaderHelicopter::HeliList;

ALeaderHelicopter::ALeaderHelicopter()
{
	
}

ALeaderHelicopter::~ALeaderHelicopter()
{
	FlameShot* FS = GetWorld()->SpawnActor<FlameShot>();
	FS->SetActorLocation(GetActorLocation());
	
	std::list<AHelicopter*>::iterator iter = HeliList.begin();
	for (int i = 1; iter != HeliList.end(); ++iter,++i)
	{
		(*iter)->Destroy(i * 0.3f);
		(*iter) = nullptr;
	}

	AExplosionEffect* Explosion = GetWorld()->SpawnActor<AExplosionEffect>();
	Explosion->SetActorLocation(GetActorLocation());
	Explosion->SetSize(FVector{ 800,800 });

}

void ALeaderHelicopter::BeginPlay()
{
	AEnemy::BeginPlay();

	Hp = 30;

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ {0,0}, {500,500} });
	Renderer->SetImage("Helicopter.png");
	Renderer->CreateAnimation("Speed7_Right", "LeaderHelicopter.png", 0, 5, 0.08f, true);
	Renderer->CreateAnimation("Speed6_Right", "LeaderHelicopter.png", 6, 11, 0.08f, true);
	Renderer->CreateAnimation("Speed5_Right", "LeaderHelicopter.png", 12, 17, 0.08f, true);
	Renderer->CreateAnimation("Speed4_Right", "LeaderHelicopter.png", 18, 23, 0.08f, true);
	Renderer->CreateAnimation("Speed3_Right", "LeaderHelicopter.png", 24, 29, 0.08f, true);
	Renderer->CreateAnimation("Speed2_Right", "LeaderHelicopter.png", 30, 35, 0.08f, true);
	Renderer->CreateAnimation("Speed1_Right", "LeaderHelicopter.png", 36, 41, 0.08f, true);
	Renderer->CreateAnimation("Speed0_Right", "LeaderHelicopter.png", 42, 47, 0.08f, true);

	Renderer->CreateAnimation("Aiming1_Right", "LeaderHelicopter.png", 36, 41, 0.08f, true);
	Renderer->CreateAnimation("Aiming0_Right", "LeaderHelicopter.png", 42, 47, 0.08f, true);
	Renderer->CreateAnimation("TurnLeftToCenter", "LeaderHelicopter.png", 48, 55, 0.08f, false);

	Renderer->CreateAnimation("Speed7_Left", "LeaderHelicopter.png", 60, 65, 0.08f, true);
	Renderer->CreateAnimation("Speed6_Left", "LeaderHelicopter.png", 66, 71, 0.08f, true);
	Renderer->CreateAnimation("Speed5_Left", "LeaderHelicopter.png", 72, 77, 0.08f, true);
	Renderer->CreateAnimation("Speed4_Left", "LeaderHelicopter.png", 78, 83, 0.08f, true);
	Renderer->CreateAnimation("Speed3_Left", "LeaderHelicopter.png", 84, 89, 0.08f, true);
	Renderer->CreateAnimation("Speed2_Left", "LeaderHelicopter.png", 90, 95, 0.08f, true);
	Renderer->CreateAnimation("Speed1_Left", "LeaderHelicopter.png", 96, 101, 0.08f, true);
	Renderer->CreateAnimation("Speed0_Left", "LeaderHelicopter.png", 102, 107, 0.08f, true);

	Renderer->CreateAnimation("Aiming1_Left", "LeaderHelicopter.png", 96, 101, 0.08f, true);
	Renderer->CreateAnimation("Aiming0_Left", "LeaderHelicopter.png", 102, 107, 0.08f, true);
	Renderer->CreateAnimation("TurnRightToCenter", "LeaderHelicopter.png", 108, 115, 0.08f, false);

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({ 100,100 });
	Collider->SetPosition({ 0,-100 });
	Collider->SetColType(ECollisionType::Rect);

	StateChange(HelicopterState::Move);
	Renderer->ChangeAnimation("Speed4_Right");

	BulletCoolDown = 0.5f;
	AccBullet = 0.0f;
	Bullet = 6;

	Hp = 20;
}

void ALeaderHelicopter::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);

	MoveVector.Normalize2D();
	AddActorLocation(MoveVector * abs(Speed) * _DeltaTime);

	DamagedEffectAcc += _DeltaTime;
	if (DamagedEffectAcc > DamagedEffectTime)
	{
		Renderer->SetAlpha(1.0f);
	}

	if (Hp != PrevHp)
	{
		DamagedEffectAcc = 0.0f;
		Renderer->SetAlpha(0.5f);
		PrevHp = Hp;
	}

	if (Hp <= 0)
	{
		StateChange(HelicopterState::Death);
		return;
	}

	if (Speed < 0.0f)
	{
		MoveVector = FVector::Left;
	}
	else
	{
		MoveVector = FVector::Right;
	}

	if (AccelDir.X < 0.0f)
	{
		if (Speed > -300.0f)
		{
			Speed -= Accel * _DeltaTime;
		}


		if (GetActorLocation().Y < CP_Bottom)
		{
			AddActorLocation(FVector::Down * 200.0f * _DeltaTime);
		}
	}
	else
	{
		if (Speed < 300.0f)
		{
			Speed += Accel * _DeltaTime;
		}
		if (GetActorLocation().Y > CP_Top)
		{
			AddActorLocation(FVector::Up * 200.0f * _DeltaTime);
		}
	}

	if (GetActorLocation().X < CP_Left && AccelDir.X < 0.0f)
	{
		AccelDir = FVector::Right;
	}
	else if (GetActorLocation().X > CP_Right && AccelDir.X > 0.0f)
	{
		AccelDir = FVector::Left;
	}
}

void ALeaderHelicopter::Shoot(float _DeltaTime)
{
	AccBullet += _DeltaTime;
	if (AccBullet > BulletCoolDown)
	{
		AHelicopterBullet* BulletPtr = GetWorld()->SpawnActor<AHelicopterBullet>();
		BulletPtr->SetActorLocation(GetActorLocation());
		BulletPtr->SetDir(FVector::Down);
		AccBullet = 0.0f;
		--Bullet;
	}

	if (Bullet <= 0)
	{
		Bullet = 6;
		AccBullet = 0.0f;
		StateChange(HelicopterState::Move);
		return;
	}
}

void ALeaderHelicopter::ShootStart()
{
	CurAnimName = "Aiming0";
	DirCheck();
}

void ALeaderHelicopter::Move(float _DeltaTime)
{
	AccAttack += _DeltaTime;

	if (AccAttack > AttackCoolTime)
	{
		AccAttack = 0.0f;
		StateChange(HelicopterState::Shoot);
		return;
	}

	if (abs(Speed) > 250.0f)
	{
		CurAnimName = "Speed7";
	}
	else if (abs(Speed) > 200.0f)
	{
		CurAnimName = "Speed6";
	}
	else if (abs(Speed) > 150.0f)
	{
		CurAnimName = "Speed5";
	}
	else if (abs(Speed) > 100.0f)
	{
		CurAnimName = "Speed4";
	}
	else if (abs(Speed) > 50.0f)
	{
		CurAnimName = "Speed3";
	}
	else if (abs(Speed) > 30.0f)
	{
		CurAnimName = "Speed2";
	}
	else if (abs(Speed) > 10.0f)
	{
		CurAnimName = "Speed1";
	}
	else
	{
		CurAnimName = "Speed0";
	}
	DirCheck();
}

void ALeaderHelicopter::MoveStart()
{
	if (abs(Speed) > 250.0f)
	{
		CurAnimName = "Speed7";
	}
	else if (abs(Speed) > 200.0f)
	{
		CurAnimName = "Speed6";
	}
	else if (abs(Speed) > 150.0f)
	{
		CurAnimName = "Speed5";
	}
	else if (abs(Speed) > 100.0f)
	{
		CurAnimName = "Speed4";
	}
	else if (abs(Speed) > 50.0f)
	{
		CurAnimName = "Speed3";
	}
	else if (abs(Speed) > 30.0f)
	{
		CurAnimName = "Speed2";
	}
	else if (abs(Speed) > 10.0f)
	{
		CurAnimName = "Speed1";
	}
	else
	{
		CurAnimName = "Speed0";
	}
	DirCheck();
}
