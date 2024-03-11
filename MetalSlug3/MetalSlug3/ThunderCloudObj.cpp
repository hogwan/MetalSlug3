#include "ThunderCloudObj.h"
#include "ContentsHelper.h"

ThunderCloudObj::ThunderCloudObj()
{
}

ThunderCloudObj::~ThunderCloudObj()
{
}

void ThunderCloudObj::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::Enemy);
}

void ThunderCloudObj::Tick(float _DeltaTime)
{
}
