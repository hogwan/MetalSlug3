#include "FlameShot.h"
#include "ContentsHelper.h"
#include "Marco.h"

FlameShot::FlameShot()
{
}

FlameShot::~FlameShot()
{
}

void FlameShot::BeginPlay()
{
	AItem::BeginPlay();

	Renderer->SetImage("FlameShot.png");
}

void FlameShot::Tick(float _DeltaTime)
{
	AItem::Tick(_DeltaTime);
}

void FlameShot::Action()
{
	AItem::Action();

	if (!UContentsHelper::Player->IsZombie)
	{
		UContentsHelper::Player->ArmsCount = 30;
		UContentsHelper::Player->GunType = EGunType::Rifle;
		UContentsHelper::Player->Gun = EGunList::FlameShot;
	}

	Destroy();
}
