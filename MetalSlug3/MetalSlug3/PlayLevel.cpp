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

	UEngineResourcesManager::GetInst().CuttingImage("Marco_face-Resource.png", 20, 195);
	UEngineResourcesManager::GetInst().CuttingImage("Exception1_150by150_HeavyMacineGun_JumpUpDownShoot.png", 4, 4);
	UEngineResourcesManager::GetInst().CuttingImage("Exception2_100by300_SpawnAndThunder.png", 10, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Exception3_200by200_ZombieDeathInAir.png", 10, 4);

	ABackGroundMap* Map = SpawnActor<ABackGroundMap>();
	Map->SetMapImage("State2Map.png");
	Map->SetColMapImage("Stage2Map_Col.png");



	SpawnActor<Marco>();
}
