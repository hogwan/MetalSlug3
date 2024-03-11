#include "FlameShotBullet.h"
#include "Enemy.h"
#include "Monoliths.h"

AFlameShotBullet::AFlameShotBullet()
{
}

AFlameShotBullet::~AFlameShotBullet()
{
}

void AFlameShotBullet::BeginPlay()
{
	AMT3Object::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::Projectile);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->CreateAnimation("Right","FlameShot_Right.png", 0, 25, 0.04f, false);
	Renderer->CreateAnimation("Left", "FlameShot_Left.png", 0, 25, 0.04f, false);
	Renderer->CreateAnimation("Up", "FlameShot_Up.png", 0, 25, 0.04f, false);
	Renderer->CreateAnimation("Down", "FlameShot_Down.png", 0, 25, 0.04f, false);

	Collider = CreateCollision(MT3CollisionOrder::Flame);
	Collider->SetTransform({ {0,0},{50,50} });

	Speed = 300.0f;
}

void AFlameShotBullet::Tick(float _DeltaTime)
{
	AMT3Object::Tick(_DeltaTime);

	if (Dir.X > 0.f)
	{
		Renderer->ChangeAnimation("Right", false, 0, 0.04f);
	}
	else if (Dir.X < 0.f)
	{
		Renderer->ChangeAnimation("Left", false, 0, 0.04f);
	}
	else if (Dir.Y > 0)
	{
		Renderer->ChangeAnimation("Down", false, 0, 0.04f);
	}
	else {
		Renderer->ChangeAnimation("Up", false, 0, 0.04f);
	}

	AddActorLocation(Dir * Speed * _DeltaTime);

	AccDamageTick += _DeltaTime;
	if (AccDamageTick > DamageTick)
	{
		AccDamageTick = 0.0f;

		{
			std::vector<UCollision*> Result;
			if (true == Collider->CollisionCheck(MT3CollisionOrder::Enemy, Result)
				|| true == Collider->CollisionCheck(MT3CollisionOrder::Boss, Result))
			{
				AEnemy* Enemy = dynamic_cast<AEnemy*>(Result[0]->GetOwner());
				Enemy->Damaged(Damage);
			}
		}

		{
			std::vector<UCollision*> Result;
			if (true == Collider->CollisionCheck(MT3CollisionOrder::Monoliths, Result))
			{
				AMonoliths* Monoliths = dynamic_cast<AMonoliths*>(Result[0]->GetOwner());
				Monoliths->GoDown();
			}
		}
	}

	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

