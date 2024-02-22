#include "Bullet.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>
#include "Enemy.h"

ABullet::ABullet()
{
}

ABullet::~ABullet()
{
}


void ABullet::BeginPlay()
{
	
}

void ABullet::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);
	if (IsDestroy && Renderer->IsCurAnimationEnd())
	{
		Destroy();
	}

	std::vector<UCollision*> Result;
	if (true == Collider->CollisionCheck(MT3CollisionOrder::Enemy, Result))
	{
		AEnemy* Enemy = dynamic_cast<AEnemy*>(Result[0]->GetOwner());
		Enemy->Damaged(Damage);

		Speed = 0.0f;
		IsDestroy = true;
		Collider->Destroy();
		Renderer->SetImage("BulletDestroy.png");
		Renderer->ChangeAnimation("Destroy");
		Renderer->SetTransform({ {0,0}, {30,30} });
	}
}