#include "PlayLevel.h"
#include "Marco.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include "BackGroundMap.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::BeginPlay()
{
	UEngineDirectory NewPath;
	NewPath.MoveParent();
	NewPath.Move("MT3Resource");
	NewPath.Move("PlayLevel");


	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);
	
	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	UEngineResourcesManager::GetInst().CuttingImage("Marco_Pistol_UpperBody.png", 44, 10);
	UEngineResourcesManager::GetInst().CuttingImage("Marco_LowerBody_Left.png", 3, 10);
	UEngineResourcesManager::GetInst().CuttingImage("Marco_LowerBody_Right.png", 3, 10);

	ABackGroundMap* Map = SpawnActor<ABackGroundMap>();
	Map->SetMapImage("State2Map.png");
	Map->SetColMapImage("Stage2Map_Col.png");



	SpawnActor<Marco>();
}
