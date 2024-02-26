#include "Helicopter.h"
#include "Marco.h"
#include "HelicopterBullet.h"
#include "ExplosionEffect.h"

AHelicopter::AHelicopter()
{
}

AHelicopter::~AHelicopter()
{
	ExplosionEffect* Explosion = GetWorld()->SpawnActor<ExplosionEffect>();
	Explosion->SetActorLocation(GetActorLocation());
	Explosion->SetSize(FVector{ 800,800 });
}


void AHelicopter::BeginPlay()
{
	AEnemy::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ {0,0}, {500,500} });
	Renderer->SetImage("Helicopter.png");
	Renderer->CreateAnimation("Speed1_Right", "Helicopter.png", 0, 5, 0.08f, true);
	Renderer->CreateAnimation("Speed2_Right", "Helicopter.png", 6, 11, 0.08f, true);
	Renderer->CreateAnimation("Speed3_Right", "Helicopter.png", 12, 17, 0.08f, true);
	Renderer->CreateAnimation("Speed4_Right", "Helicopter.png", 18, 23, 0.08f, true);
	Renderer->CreateAnimation("Speed5_Right", "Helicopter.png", 24, 29, 0.08f, true);
	Renderer->CreateAnimation("Speed0_Right", "Helicopter.png", 30, 35, 0.08f, true);
	Renderer->CreateAnimation("Aiming1_Right", "Helicopter.png", 36, 41, 0.08f, true);
	Renderer->CreateAnimation("Aiming0_Right", "Helicopter.png", 42, 47, 0.08f, true);

	Renderer->CreateAnimation("Speed1_Left", "Helicopter.png", 60, 65, 0.08f, true);
	Renderer->CreateAnimation("Speed2_Left", "Helicopter.png", 66, 71, 0.08f, true);
	Renderer->CreateAnimation("Speed3_Left", "Helicopter.png", 72, 77, 0.08f, true);
	Renderer->CreateAnimation("Speed4_Left", "Helicopter.png", 78, 83, 0.08f, true);
	Renderer->CreateAnimation("Speed5_Left", "Helicopter.png", 84, 89, 0.08f, true);
	Renderer->CreateAnimation("Speed0_Left", "Helicopter.png", 90, 95, 0.08f, true);
	Renderer->CreateAnimation("Aiming1_Left", "Helicopter.png", 96, 101, 0.08f, true);
	Renderer->CreateAnimation("Aiming0_Left", "Helicopter.png", 102, 107, 0.08f, true);

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({ 100,100 });
	Collider->SetPosition({ 0,-100 });
	Collider->SetColType(ECollisionType::Rect);

	StateChange(HelicopterState::Move);
	Renderer->ChangeAnimation("Speed4_Right");

	Hp = 20;
}

void AHelicopter::Tick(float _DeltaTime)
{
	AEnemy::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);

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
}

void AHelicopter::StateUpdate(float _DeltaTime)
{
	switch (CurState)
	{
	case HelicopterState::None:
		None(_DeltaTime);
		break;
	case HelicopterState::Move:
		Move(_DeltaTime);
		break;;
	case HelicopterState::Aiming:
		Aiming(_DeltaTime);
		break;
	case HelicopterState::Shoot:
		Shoot(_DeltaTime);
		break;
	case HelicopterState::Death:
		Death(_DeltaTime);
		break;
	default:
		break;
	}
}

void AHelicopter::StateChange(HelicopterState _State)
{
	if (CurState != _State)
	{
		switch (_State)
		{
		case HelicopterState::None:
			NoneStart();
			break;
		case HelicopterState::Move:
			MoveStart();
			break;;
		case HelicopterState::Aiming:
			AimingStart();
			break;
		case HelicopterState::Shoot:
			ShootStart();
			break;
		case HelicopterState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	CurState = _State;
}

void AHelicopter::None(float _DeltaTime)
{
	StateChange(HelicopterState::Move);
	return;
}

void AHelicopter::Move(float _DeltaTime)
{

	FVector Offset = { 0,-300 };
	TargetVector = (UContentsHelper::Player->GetActorLocation() + Offset) - GetActorLocation();
	MoveVector = TargetVector;
	AddActorLocation(MoveVector * _DeltaTime);

	if (MoveVector.Size2D() > 300.0f)
	{
		CurAnimName = "Speed5";
	}
	else if (MoveVector.Size2D() > 250.0f)
	{
		CurAnimName = "Speed4";
	}
	else if (MoveVector.Size2D() > 200.0f)
	{
		CurAnimName = "Speed3";
	}
	else if (MoveVector.Size2D() > 150.0f)
	{
		CurAnimName = "Speed2";
	}
	else if (MoveVector.Size2D() > 100.0f)
	{
		CurAnimName = "Speed1";
	}
	else
	{
		CurAnimName = "Speed0";
	}
	DirCheck();

	FVector AimVector = UContentsHelper::Player->GetActorLocation() - GetActorLocation();
	AimVector.Normalize2D();

	if (abs(AimVector.X) < 0.58f)
	{
		AccMove = 0.0f;
		StateChange(HelicopterState::Aiming);
		return;
	}
}

void AHelicopter::Aiming(float _DeltaTime)
{
	AccAiming += _DeltaTime;
	FVector AimVector = UContentsHelper::Player->GetActorLocation() - GetActorLocation();
	AimVector.Normalize2D();
	DirCheck();

	if (abs(AimVector.X) < 0.17f)
	{
		CurAnimName = "Aiming0";
	}
	else if (abs(AimVector.X) < 0.58f)
	{
		CurAnimName = "Aiming1";
	}
	else
	{
		AccAiming = 0.0f;
		StateChange(HelicopterState::Move);
		return;
	}

	if (AccAiming > ShootCoolDown)
	{
		AccAiming = 0.0f;
		StateChange(HelicopterState::Shoot);
		return;
	}

}

void AHelicopter::Shoot(float _DeltaTime)
{
	AccBullet += _DeltaTime;
	if (AccBullet > BulletCoolDown && Bullet > 0)
	{
		AHelicopterBullet* BulletPtr = GetWorld()->SpawnActor<AHelicopterBullet>();
		BulletPtr->SetDir(ShootVector);
		BulletPtr->SetActorLocation(GetActorLocation());
		--Bullet;
		AccBullet = 0.0f;
	}

	if (Bullet == 0)
	{
		AccMove += _DeltaTime;
		if (AccMove > MoveCoolDown)
		{
			AccMove = 0.0f;
			Bullet = 3;
			StateChange(HelicopterState::Aiming);
			return;
		}
	}
}

void AHelicopter::Death(float _DeltaTime)
{
	AddActorLocation(FVector::Down * 600.0f* _DeltaTime);
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		Destroy();
	}
}

void AHelicopter::NoneStart()
{
}

void AHelicopter::MoveStart()
{
	TargetVector = (UContentsHelper::Player->GetActorLocation() + Offset) - GetActorLocation();
	MoveVector.X = TargetVector.X / 2.0f;
	if (abs(MoveVector.X) > 300.0f)
	{
		CurAnimName = "Speed5";
	}
	else if (abs(MoveVector.X) > 250.0f)
	{
		CurAnimName = "Speed4";
	}
	else if (abs(MoveVector.X) > 200.0f)
	{
		CurAnimName = "Speed3";
	}
	else if (abs(MoveVector.X) > 150.0f)
	{
		CurAnimName = "Speed2";
	}
	else if (abs(MoveVector.X) > 100.0f)
	{
		CurAnimName = "Speed1";
	}
	else
	{
		CurAnimName = "Speed0";
	}
	DirCheck();
}

void AHelicopter::AimingStart()
{
}

void AHelicopter::ShootStart()
{
	FVector AimVector = UContentsHelper::Player->GetActorLocation() - GetActorLocation();
	AimVector.Normalize2D();
	if (abs(AimVector.X) < 0.17f)
	{
		ShootVector = FVector::Down;
		ShootVector.Normalize2D();
	}
	else
	{
		if (AimVector.X > 0.0f)
		{
			ShootVector = { 41.0f,60.0f };
		}
		else
		{
			ShootVector = { -41.0f,60.0f };
		}
		ShootVector.Normalize2D();
	}
}

void AHelicopter::DeathStart()
{
	Collider->ActiveOff();
}

void AHelicopter::DirCheck()
{
	FVector AimVector = UContentsHelper::Player->GetActorLocation() - GetActorLocation();
	AimVector.Normalize2D();
	std::string DirCheckedName = CurAnimName;
	if (AimVector.X < 0.0f)
	{
		DirCheckedName += "_Left";
	}
	else
	{
		DirCheckedName += "_Right";
	}

	if (nullptr == Renderer->GetCurAnimation())
	{
		Renderer->ChangeAnimation(DirCheckedName, false, 0, 0.08f);
	}
	else
	{
		int CurFrame = Renderer->GetCurAnimationFrame();
		Renderer->ChangeAnimation(DirCheckedName, false, CurFrame, 0.08f);
	}
}
