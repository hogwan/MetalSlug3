#include "HeavyMachineGun.h"
#include "ContentsHelper.h"
#include "Marco.h"

HeavyMachineGun::HeavyMachineGun()
{
}

HeavyMachineGun::~HeavyMachineGun()
{
}

void HeavyMachineGun::BeginPlay()
{
	AItem::BeginPlay();

	Renderer->SetImage("HeavyMachineGun.png");
}

void HeavyMachineGun::Tick(float _DeltaTime)
{
	AItem::Tick(_DeltaTime);
}

void HeavyMachineGun::Action()
{
	AItem::Action();

	UEngineSound::SoundPlay("WeaponEquip.mp3");
	UEngineSound::SoundPlay("HeavyMachineGun.mp3");

	if (!UContentsHelper::Player->IsZombie)
	{
		UContentsHelper::Player->Gun = EGunList::HeavyMachineGun;
		UContentsHelper::Player->GunType = EGunType::Rifle;
		UContentsHelper::Player->ArmsCount = 200;
	}

	Destroy();
}
