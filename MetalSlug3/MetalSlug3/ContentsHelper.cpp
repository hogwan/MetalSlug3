#include "ContentsHelper.h"

UWindowImage* UContentsHelper::ColMapImage = nullptr;
UWindowImage* UContentsHelper::CrouchColMapImage = nullptr;
AScreenCollision* UContentsHelper::ScreenCol = nullptr;
class Marco* UContentsHelper::Player = nullptr;
class CameraManager* UContentsHelper::CameraManager = nullptr;
int UContentsHelper::Life = 2;
int UContentsHelper::Score = 0;

UContentsHelper::UContentsHelper()
{
}

UContentsHelper::~UContentsHelper()
{
}
