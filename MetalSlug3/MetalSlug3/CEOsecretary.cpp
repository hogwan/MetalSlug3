#include "CEOsecretary.h"
#include "ContentsHelper.h"
#include "ThunderCloud.h"

CEOsecretary::CEOsecretary()
{
}

CEOsecretary::~CEOsecretary()
{
}

void CEOsecretary::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->CreateAnimation("CEOsecretary", "CEOsecretary.png", 0, 26, 0.08f, false);
	Renderer->ChangeAnimation("CEOsecretary", false, 0, 0.08f);
	Renderer->SetTransform({ {0,0},{500,500} });
}

void CEOsecretary::Tick(float _DeltaTime)
{
	int CurFrame = Renderer->GetCurAnimationFrame();

	if (CurFrame != PrevFrame && CurFrame == 11)
	{
		ThunderCloud* TC = GetWorld()->SpawnActor<ThunderCloud>();
		TC->SetActorLocation(GetActorLocation());

		PrevFrame = CurFrame;
	}

	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
	}

}
