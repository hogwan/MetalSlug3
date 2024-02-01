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
	NewPath.MoveParent();
	NewPath.Move("TestResource");

	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);
	
	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		// �̱��� ���� ����� �Ϻη� GetInst�� ����ϰڽ��ϴ�.
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	UEngineResourcesManager::GetInst().CuttingImage("002_UpperBody_Run_Right.png", 20, 1);
	UEngineResourcesManager::GetInst().CuttingImage("078_LowerBody_Run_Right.png", 20, 1);


	SpawnActor<Marco>();
}
