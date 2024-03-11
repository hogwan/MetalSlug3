#include "BombBox.h"
#include "ContentsHelper.h"
#include "Marco.h"

BombBox::BombBox()
{
}

BombBox::~BombBox()
{
}

void BombBox::BeginPlay()
{
	AItem::BeginPlay();

	Renderer->CreateAnimation("BombBox", "BombBox.png", 0, 6, 0.08f, true);
	Renderer->ChangeAnimation("BombBox");
}

void BombBox::Tick(float _DeltaTime)
{
	AItem::Tick(_DeltaTime);
}

void BombBox::Action()
{
	AItem::Action();

	if (!UContentsHelper::Player->IsZombie)
	{
		UContentsHelper::Player->BombsCount += 10;
	}

	Destroy();
}
