#include "CharacterSelect.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include "MarcoPhoto.h"
#include "P1.h"
#include "Panel.h"

CharacterSelect::CharacterSelect()
{
}

CharacterSelect::~CharacterSelect()
{
}

void CharacterSelect::BeginPlay()
{
	UEngineDirectory NewPath;
	NewPath.MoveParent();
	NewPath.Move("MT3Resource");
	NewPath.Move("CharacterSelectScreen");

	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	UEngineResourcesManager::GetInst().CuttingImage("MarcoSelectedAnim.png", 2, 1);
	UEngineResourcesManager::GetInst().CuttingImage("DoorEffect.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("Marco_Idle.png", 10, 1);

	SpawnActor<Panel>();
	SpawnActor<P1>();
	SpawnActor<MarcoPhoto>();

}
