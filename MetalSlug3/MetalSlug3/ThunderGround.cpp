#include "ThunderGround.h"
#include "ContentsHelper.h"
#include "Enemy.h"
#include "ThunderCloudEffect.h"
#include <EnginePlatform/EngineSound.h>

ThunderGround::ThunderGround()
{
}

ThunderGround::~ThunderGround()
{
}

void ThunderGround::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(MT3RenderOrder::UFO_LazerGroundEffect);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->CreateAnimation("ThunderGround", "ThunderCloudObjEffect.png", 0, 10, 0.03f);
	Renderer->ChangeAnimation("ThunderGround", false, 0, 0.03f);

	Collider = CreateCollision(MT3CollisionOrder::PlayerBullet);
	Collider->SetTransform({ {0,-25},{75,50} });
	Collider->SetColType(ECollisionType::Rect);

	UEngineSound::SoundPlay("Thunder.mp3");
}

void ThunderGround::Tick(float _DeltaTime)
{
	if (!Trigger)
	{
		std::vector<UCollision*> Result;
		if (Collider->CollisionCheck(MT3CollisionOrder::Enemy, Result))
		{
			for (UCollision* Col : Result)
			{
				AEnemy* Enemy = dynamic_cast<AEnemy*>(Col->GetOwner());
				Enemy->Damaged(Damage);
			}
		}

		ThunderCloudEffect* Effect = GetWorld()->SpawnActor<ThunderCloudEffect>();
		Effect->SetActorLocation(GetActorLocation());
		Effect->ThunderSize = ThunderSize;
		
		Trigger = true;
	}

	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}
