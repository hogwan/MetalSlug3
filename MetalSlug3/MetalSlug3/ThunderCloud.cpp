#include "ThunderCloud.h"
#include "ContentsHelper.h"
#include "Marco.h"
#include "ThunderCloudObj.h"

ThunderCloud::ThunderCloud()
{
}

ThunderCloud::~ThunderCloud()
{
}

void ThunderCloud::BeginPlay()
{
	AItem::BeginPlay();
	Renderer->CreateAnimation("ThunderCloud", "ThunderCloud.png", 0, 17, 0.08f, true);
	Renderer->ChangeAnimation("ThunderCloud");
}

void ThunderCloud::Tick(float _DeltaTime)
{
	AItem::Tick(_DeltaTime);
}

void ThunderCloud::Action()
{
	AItem:: Action();

	UEngineSound::SoundPlay("WeaponEquip.mp3");
	UEngineSound::SoundPlay("ThunderCloud.mp3");

	if (!UContentsHelper::Player->IsZombie)
	{
		ThunderCloudObj* TCO = GetWorld()->SpawnActor<ThunderCloudObj>();
		TCO->SetActorLocation(GetActorLocation());
	}

	Destroy();
}
