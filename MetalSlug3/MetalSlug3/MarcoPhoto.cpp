#include "MarcoPhoto.h"
#include <EngineCore\EngineCore.h>
#include <EngineBase/EngineTime.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/ImageRenderer.h>

MarcoPhoto::MarcoPhoto()
{
}

MarcoPhoto::~MarcoPhoto()
{
}

void MarcoPhoto::BeginPlay()
{
	ThisRenderer = CreateImageRenderer(5);
	ThisRenderer->SetImage("MarcoPocus.png");
	ThisRenderer->SetTransform({ {0,0} , {170, 325} });
	SetActorLocation({ 130.0f, 300.0f });
	


	/*UpperBodyRenderer = CreateImageRenderer(5);
	UpperBodyRenderer->SetImage("Marco_face-Resource.png");
	UpperBodyRenderer->SetTransform({ {0,0}, {200, 200} });
	UpperBodyRenderer->SetImageCuttingTransform({ {0,0}, {100, 100} });
	UpperBodyRenderer->SetTransColor({ 153, 217, 234, 0 });*/
}