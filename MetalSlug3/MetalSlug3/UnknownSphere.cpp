#include "UnknownSphere.h"
#include "ContentsHelper.h"

AUnknownSphere::AUnknownSphere()
{
}

AUnknownSphere::~AUnknownSphere()
{
}

void AUnknownSphere::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
	Renderer->SetImage("MonoEyes_UnknownSphere.png");
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->CreateAnimation("Sphere", "MonoEyes_UnknownSphere.png", 0, 11, 0.12f, false);
	Renderer->ChangeAnimation("Sphere", false, 0, 0.08f);

}

void AUnknownSphere::Tick(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}
