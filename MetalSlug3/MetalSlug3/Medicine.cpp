#include "Medicine.h"
#include "ContentsHelper.h"
#include "Marco.h"

Medicine::Medicine()
{
}

Medicine::~Medicine()
{
}

void Medicine::BeginPlay()
{
	AItem::BeginPlay();
	Renderer->CreateAnimation("Medicine", "Medicine.png", 0, 32, 0.08f, true);
	Renderer->ChangeAnimation("Medicine");
}

void Medicine::Tick(float _DeltaTime)
{
	AItem::Tick(_DeltaTime);

}

void Medicine::Action()
{
	AItem::Action();

	if (UContentsHelper::Player->IsZombie)
	{
		UContentsHelper::Player->ZombieToHuman();
	}
	Destroy();
}
