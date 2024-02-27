#include "ZombiesProjectile.h"
#include "ContentsHelper.h"

AZombiesProjectile::AZombiesProjectile()
{
}

AZombiesProjectile::~AZombiesProjectile()
{
}

void AZombiesProjectile::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	StateUpdate(_DeltaTime);
	if (Dir.X < 0.0f)
	{
		FVector ReverseVector = { -ResultVector.X, ResultVector.Y };
		AddActorLocation(ReverseVector * _DeltaTime);
	}
	else if (Dir.X > 0.0f)
	{
		AddActorLocation(ResultVector * _DeltaTime);
	}
}

void AZombiesProjectile::BeginPlay()
{
	AActor::BeginPlay();

	Collider = CreateCollision(MT3CollisionOrder::ZombieProjectile);
	Collider->SetScale({ 30,30 });
	Collider->SetPosition({ 0,-30 });
	Collider->SetColType(ECollisionType::Rect);

	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->SetImage("Zombies_Projectile.png");
	Renderer->SetTransform({ { 0,0 }, { 500,500 } });

	Renderer->CreateAnimation("Flying_Right", "Zombies_Projectile.png", 0, 13,0.08f, false);
	Renderer->CreateAnimation("CollideGround_Right", "Zombies_Projectile.png", 14, 32, 0.08f, false);
	Renderer->CreateAnimation("CollideObject_Right", "Zombies_Projectile.png", 33, 48, 0.08f, false);

	Renderer->CreateAnimation("Flying_Left", "Zombies_Projectile.png", 50, 63, 0.08f, false);
	Renderer->CreateAnimation("CollideGround_Left", "Zombies_Projectile.png", 64, 82, 0.08f, false);
	Renderer->CreateAnimation("CollideObject_Left", "Zombies_Projectile.png", 83, 98, 0.08f, false);

	StateChange(State::None);
}

void AZombiesProjectile::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		ResultVector += Gravity * _DeltaTime;
	}
}

std::string AZombiesProjectile::DirCheck(std::string _Name)
{
	std::string DirName = "";
	if (Dir.X < 0.0f)
	{
		DirName = "_Left";
	}
	else if (Dir.X > 0.0f)
	{
		DirName = "_Right";
	}

	_Name += DirName;
	return _Name;
}

void AZombiesProjectile::StateUpdate(float _DeltaTime)
{
	switch (CurState)
	{
	case State::None:
		None(_DeltaTime);
		break;
	case State::Flying:
		Flying(_DeltaTime);
		break;
	case State::CollideGround:
		CollideGround(_DeltaTime);
		break;
	case State::CollideObject:
		CollideObject(_DeltaTime);
		break;
	}
}

void AZombiesProjectile::StateChange(State _State)
{
	if (CurState != _State)
	{
		switch (_State)
		{
		case State::None:
			NoneStart();
			break;
		case State::Flying:
			FlyingStart();
			break;
		case State::CollideGround:
			CollideGroundStart();
			break;
		case State::CollideObject:
			CollideObjectStart();
			break;
		}
	}
	CurState = _State;
}

void AZombiesProjectile::None(float _DeltaTime)
{
	StateChange(State::Flying);
}

void AZombiesProjectile::Flying(float _DeltaTime)
{
	GravityCheck(_DeltaTime);

	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		ResultVector = FVector::Zero;
		StateChange(State::CollideGround);
		return;
	}

	std::vector<UCollision*> Result;
	if (true == Collider->CollisionCheck(MT3CollisionOrder::Player, Result)
		||true == Collider->CollisionCheck(MT3CollisionOrder::Human,Result))
	{
		ResultVector = FVector::Zero;
		StateChange(State::CollideObject);
		return;
	}
}

void AZombiesProjectile::CollideGround(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

void AZombiesProjectile::CollideObject(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

void AZombiesProjectile::NoneStart()
{
	CurAnimName = "None";
}

void AZombiesProjectile::FlyingStart()
{
	CurAnimName = "Flying";
	std::string DirectedName = DirCheck(CurAnimName);
	Renderer->ChangeAnimation(DirectedName);

	ShootVector.Normalize2D();
	ResultVector = ShootVector * ShootPower;
}

void AZombiesProjectile::CollideGroundStart()
{
	Collider->ActiveOff();
	CurAnimName = "CollideGround";
	std::string DirectedName = DirCheck(CurAnimName);
	Renderer->ChangeAnimation(DirectedName);
}

void AZombiesProjectile::CollideObjectStart()
{
	Collider->ActiveOff();
	CurAnimName = "CollideObject";
	std::string DirectedName = DirCheck(CurAnimName);
	Renderer->ChangeAnimation(DirectedName);
}
