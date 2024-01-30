#include "Bomb.h"
#include "EngineCore/EngineCore.h"

ABomb::ABomb()
{
}

ABomb::~ABomb()
{
}

void ABomb::BeginPlay()
{
	{
		UImageRenderer* Renderer = CreateImageRenderer(-10);
		Renderer->SetImageToScale("Tool_Bomb_Right_0.bmp");
	}
}
void ABomb::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);

}

