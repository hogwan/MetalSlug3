#include "PlayLevel.h"
#include "Marco.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::BeginPlay()
{
	SpawnActor<Marco>();
}
