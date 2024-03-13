#include "RocketLauncher.h"
#include "ContentsHelper.h"
#include "Marco.h"

RocketLauncher::RocketLauncher()
{
}

RocketLauncher::~RocketLauncher()
{
}

void RocketLauncher::BeginPlay()
{
	AItem::BeginPlay();
	Renderer->SetImage("RocketLauncher.png");
}

void RocketLauncher::Tick(float _DeltaTime)
{
	AItem::Tick(_DeltaTime);
}

void RocketLauncher::Action()
{
	AItem::Action();

	UEngineSound::SoundPlay("WeaponEquip.mp3");
	UEngineSound::SoundPlay("RocketLauncher.mp3");

	if (!UContentsHelper::Player->IsZombie)
	{
		UContentsHelper::Player->ArmsCount = 30;
		UContentsHelper::Player->GunType = EGunType::Rifle;
		UContentsHelper::Player->Gun = EGunList::RocketLauncher;
	}

	Destroy();
}
