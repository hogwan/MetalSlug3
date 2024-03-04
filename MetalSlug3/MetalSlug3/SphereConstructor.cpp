#include "SphereConstructor.h"
#include "UnknownSphere.h"

ASphereConstructor::ASphereConstructor()
{
}

ASphereConstructor::~ASphereConstructor()
{
}

void ASphereConstructor::BeginPlay()
{

}

void ASphereConstructor::Tick(float _DeltaTime)
{

	FVector CurPos = GetActorLocation();

	float InitialToTargetAngle = AngleBetween(InitialVector,TargetVector);
	float MidAngle = InitialToTargetAngle / 2;

	FVector CurVector = CurPos - OriginVector;
	float InitialToCurAngle = AngleBetween(InitialVector, CurVector);

	AccSpawnTime += _DeltaTime;
	if (AccSpawnTime > SpawnCoolTime)
	{
		AccSpawnTime = 0.0f;
		AUnknownSphere* Sphere = GetWorld()->SpawnActor<AUnknownSphere>();
		Sphere->SetActorLocation(GetActorLocation());
	}

	if (InitialToCurAngle > InitialToTargetAngle)
	{
		Speed = 0.f;
		ClockDir = !ClockDir;
	}

	if (InitialToCurAngle < MidAngle)
	{
		Speed += Accel * _DeltaTime;
	}
	else
	{
		Speed -= Accel * _DeltaTime;
	}

	if (ClockDir)
	{
		CurVector.RotationZToDeg(Speed);
	}
	else
	{
		CurVector.RotationZToDeg(-Speed);
	}

	SetActorLocation(CurPos + CurVector);
}

float ASphereConstructor::AngleBetween(FVector _Initial, FVector _Last)
{
	
	float InnerProduct = (_Initial.X * _Last.X) + (_Initial.Y * _Last.Y);
	float InitialVectorSize = _Initial.Size2D();
	float LastVectorSize = _Last.Size2D();

	float Data = InnerProduct / (InitialVectorSize * LastVectorSize);

	float Angle = acosf(Data);

	return Angle;
	
}
