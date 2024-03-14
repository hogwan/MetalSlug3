#include "EndLevel.h"
#include "EndScreen.h"

EndLevel::EndLevel()
{
}

EndLevel::~EndLevel()
{
}

void EndLevel::BeginPlay()
{
	SpawnActor<EndScreen>();
}

void EndLevel::Tick(float _DeltaTime)
{
}
