#include "PlayLevel.h"
#include "Marco.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::BeginPlay()
{
	UEngineDirectory NewPath;
	NewPath;
	NewPath.MoveParent();
	NewPath;
	NewPath.MoveParent();
	NewPath;
	NewPath.Move("Resource");
	NewPath;
	NewPath.Move("Marco");
	NewPath;

	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);
	
	SpawnActor<Marco>();
}
