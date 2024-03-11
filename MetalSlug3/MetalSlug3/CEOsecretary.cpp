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
	Renderer->CreateAnimation("CEOsecretary", "CEOsecretary.png");
	Renderer->ChangeAnimation("CEOsecretary");
}

void CEOsecretary::Tick(float _DeltaTime)
{
	int CurFrame = Renderer->GetCurAnimationFrame();

	if (CurFrame != PrevFrame && CurFrame == 10)
	{
		ThunderCloud* TC = GetWorld()->SpawnActor<ThunderCloud>();
		TC->SetActorLocation(GetActorLocation());
	}

}
