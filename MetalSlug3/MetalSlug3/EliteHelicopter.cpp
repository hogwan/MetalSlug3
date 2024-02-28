#include "EliteHelicopter.h"
#include "EliteHelicopterProjectile.h"
#include "Marco.h"
#include "ContentsHelper.h"

AEliteHelicopter::AEliteHelicopter()
{
}

AEliteHelicopter::~AEliteHelicopter()
{
}

void AEliteHelicopter::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->SetImage("Flying0.png");

	Propeller = CreateImageRenderer(MT3RenderOrder::Propeller);
	Propeller->SetTransform({ {0,-20},{500,500} });
	Propeller->SetImage("Propeller.png");

	Propeller->CreateAnimation("Flying6", "Propeller.png", 0, 4, 0.08f, true);
	Propeller->CreateAnimation("Flying5", "Propeller.png", 5, 9, 0.08f, true);
	Propeller->CreateAnimation("Flying4", "Propeller.png", 10, 14, 0.08f, true);
	Propeller->CreateAnimation("Flying3", "Propeller.png", 15, 19, 0.08f, true);
	Propeller->CreateAnimation("Flying2", "Propeller.png", 20, 24, 0.08f, true);
	Propeller->CreateAnimation("Flying1", "Propeller.png", 25, 29, 0.08f, true);
	Propeller->CreateAnimation("Flying0", "Propeller.png", 30, 34, 0.08f, true);

	Collider = CreateCollision(MT3CollisionOrder::Enemy);
	Collider->SetScale({150,150});
	Collider->SetPosition({ 0,-75 });
	Collider->SetColType(ECollisionType::Rect);
}

void AEliteHelicopter::Tick(float _DeltaTime)
{
	FVector PlayerPos = UContentsHelper::Player->GetActorLocation();
	FVector TargetVector = { PlayerPos.X, TargetY };
	FVector MoveVector = TargetVector - GetActorLocation();
	Speed = MoveVector.Size2D() / 2;
	MoveVector.Normalize2D();

	AddActorLocation(MoveVector * Speed * _DeltaTime);

	if (Speed > 50.0f)
	{
		if (MoveVector.X < 0.0f)
		{
			Renderer->SetImage("Flying0.png");
			Propeller->ChangeAnimation("Flying0");
		}
		else
		{
			Renderer->SetImage("Flying6.png");
			Propeller->ChangeAnimation("Flying6");
		}
	}
	else if (Speed > 30.0f)
	{
		if (MoveVector.X < 0.0f)
		{
			Renderer->SetImage("Flying1.png");
			Propeller->ChangeAnimation("Flying1");
		}
		else
		{
			Renderer->SetImage("Flying5.png");
			Propeller->ChangeAnimation("Flying5");
		}
	}
	else if (Speed > 10.0f)
	{
		if (MoveVector.X < 0.0f)
		{
			Renderer->SetImage("Flying2.png");
			Propeller->ChangeAnimation("Flying2");
		}
		else
		{
			Renderer->SetImage("Flying4.png");
			Propeller->ChangeAnimation("Flying4");
		}
	}
	else
	{
		Renderer->SetImage("Flying3.png");
		Propeller->ChangeAnimation("Flying3");
	}
}
