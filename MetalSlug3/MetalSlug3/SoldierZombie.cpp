#include "SoldierZombie.h"

ASoldierZombie::ASoldierZombie()
{
}

ASoldierZombie::~ASoldierZombie()
{
}

void ASoldierZombie::BeginPlay()
{
	AZombies::BeginPlay();

	LaunchFrame = 3;

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("SoldierZombie.png");
	Renderer->SetTransform({ {0,0}, {600,600} });

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({ 50,100 });
	Collider->SetPosition({ 0,-50 });
	Collider->SetColType(ECollisionType::Rect);

	AttackCollider = CreateCollision(MT3CollisionOrder::ZombieProjectile);
	AttackCollider->SetScale({ 60,50 });
	AttackCollider->SetPosition({ 0,-25 });
	AttackCollider->SetColType(ECollisionType::Rect);
	AttackCollider->ActiveOff();

	Renderer->CreateAnimation("Idle_Right", "SoldierZombie.png", 0, 6, 0.1f, true);
	Renderer->CreateAnimation("Move_Right", "SoldierZombie.png", 7, 22, 0.1f, true);
	Renderer->CreateAnimation("Attack_Right", "SoldierZombie.png", 23, 33, 0.1f, false);
	Renderer->CreateAnimation("DeathExplosion_Right", "SoldierZombie.png", 34, 53, 0.05f, false);
	Renderer->CreateAnimation("Stun_Right", "SoldierZombie.png", 54, 78, 0.1f, false);
	Renderer->CreateAnimation("Turn_Right", "SoldierZombie.png", 79, 87, 0.1f, false);
	Renderer->CreateAnimation("Death_Right", "ManZombie1.png", 77, 91, 0.05f, false);

	Renderer->CreateAnimation("Idle_Left", "SoldierZombie.png", 90, 96, 0.1f, true);
	Renderer->CreateAnimation("Move_Left", "SoldierZombie.png", 97, 112, 0.1f, true);
	Renderer->CreateAnimation("Attack_Left", "SoldierZombie.png", 113, 123, 0.1f, false);
	Renderer->CreateAnimation("DeathExplosion_Left", "SoldierZombie.png", 124, 143, 0.05f, false);
	Renderer->CreateAnimation("Stun_Left", "SoldierZombie.png", 144, 168, 0.1f, false);
	Renderer->CreateAnimation("Turn_Left", "SoldierZombie.png", 169, 177, 0.1f, false);

	Renderer->CreateAnimation("Death_Left", "ManZombie1.png", 197, 211, 0.05f, false);

	Renderer->CreateAnimation("Lying", "SoldierZombie.png", 158, 168, 0.15f, false);

	JumpVector.Normalize2D();
}

void ASoldierZombie::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);

	if (DirState == EActorDir::Left)
	{
		DetectCollider->SetTransform({ {-Range / 2.0f,0.0f},{Range,300.0f} });
	}
	else if (DirState == EActorDir::Right)
	{
		DetectCollider->SetTransform({ {Range / 2.0f,0.0f},{Range,300.0f} });
	}

	if (BloodEffect->IsCurAnimationEnd())
	{
		BloodEffect->ActiveOff();
	}

	if (PrevHp != Hp)
	{
		BloodEffect->ActiveOn();

		int Random = -(rand() % 70 + 30);
		int RandomEffect = rand() % 2;


		if (DirState == EActorDir::Right)
		{
			BloodEffect->SetTransform({ {-100,Random},{500,500} });
			if (RandomEffect == 0)
			{
				BloodEffect->ChangeAnimation("BloodEffect1_Right", true, 0, 0.03f);
			}
			else
			{
				BloodEffect->ChangeAnimation("BloodEffect2_Right", true, 0, 0.03f);
			}
		}
		else
		{
			BloodEffect->SetTransform({ {0,Random},{500,500} });
			if (RandomEffect == 0)
			{
				BloodEffect->ChangeAnimation("BloodEffect1_Left", true, 0, 0.03f);
			}
			else
			{
				BloodEffect->ChangeAnimation("BloodEffect2_Left", true, 0, 0.03f);
			}
		}

		PrevHp = Hp;
	}

	if (Hp <= 0)
	{
		StateChange(EnemyZombieState::Death);
	}

	if (GravityOn)
	{
		GravityCheck(_DeltaTime);
	}

	GroundUp();
	StateUpdate(_DeltaTime);
}

void ASoldierZombie::Attack(float _DeltaTime, int _LaunchFrame, int _LaunchEffectFrame)
{
	int CurFrame = Renderer->GetCurAnimationFrame();

	if (!IsDeath)
	{
		ResultVector.Y += AttackGravity * _DeltaTime;

		AddActorLocation(ResultVector * _DeltaTime);
	}

	if (PrevFrame != CurFrame && CurFrame == _LaunchFrame)
	{
		FVector Offset = { 0, -30 };
		SetActorLocation(GetActorLocation() + Offset);

		Collider->ActiveOff();
		AttackCollider->ActiveOn();

		JumpForce = 300.0f;
		AttackGravity = 500.0f;

		ResultVector = JumpVector * JumpForce;
		PrevFrame = CurFrame;
	}

	FallCheck();
	HitCheck();
}

void ASoldierZombie::AttackStart()
{
	AZombies::AttackStart();

	GravityOn = false;

	if (DirState == EActorDir::Left)
	{
		JumpVector.X = -JumpVector.X;
	}
}

void ASoldierZombie::FallCheck()
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		AttackCollider->ActiveOff();
		ResultVector = FVector::Zero;

		CurAnimName = "DeathExplosion";
		DirCheck(CurAnimName);

		Renderer->ChangeAnimation(CurAnimName, false, 0, 0.1f);
		IsDeath = true;
		Destroy(1.0f);
	}
}

void ASoldierZombie::HitCheck()
{
	std::vector<UCollision*> Result;
	if (AttackCollider->CollisionCheck(MT3CollisionOrder::Player, Result))
	{
		AttackCollider->ActiveOff();
		ResultVector = FVector::Zero;

		CurAnimName = "DeathExplosion";
		DirCheck(CurAnimName);

		Renderer->ChangeAnimation(CurAnimName, false, 0, 0.1f);
		IsDeath = true;
		Destroy(0.6f);
	}
}