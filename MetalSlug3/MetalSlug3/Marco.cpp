#include "Marco.h"
#include <EngineCore\EngineCore.h>

Marco::Marco()
{
}

Marco::~Marco()
{
}

void Marco::BeginPlay()
{
	SetActorLocation({ 100, 100 });
	SetActorScale({ 100, 100 });
}

void Marco::Tick(float _DeltaTime)
{
	HDC WindowDC = GEngine->MainWindow.GetWindowDC();

	FVector Pos = GetActorLocation();
	Pos.X += 0.01;
	SetActorLocation(Pos);

	FTransform Trans = GetTransform();




	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom());
}