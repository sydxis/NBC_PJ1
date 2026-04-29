// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(0, 0, 50));//액터의 초기 위치 설정
	for (int32 i = 0; i < 10; ++i) //in32 타입의 변수 i를 선언해주고, for문이 한 번 반복될 때마다 i에 1씩 더해준다. i가 10이 될 때까지 총 10번 반복한다.
	{
		if (FMath::RandRange(0, 1) == 0) // [도전 기능] 0~1의 정수 중 하나를 무작위로 산출해, 0과 같을 경우에만 Move(i)를 실행한다. 0~1에 포함되는 정수는 0과 1 밖에 없으므로 50%의 확률이 된다.
			Move(i);
		else // [도전 기능] 만약 랜덤 정수에서 1이 나와 실패로 처리됐을 경우, 이동(혹은 회전) 실패라는 MoveFailed 로그를 출력한다.
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("MoveFailed"));
			UE_LOG(LogTemp, Warning, TEXT("MoveFailed"));
		}
	}
	for (int32 i = 0; i < 10; ++i) //위와 마찬가지로, Turn() 함수도 실행해준다.
	{
		if (FMath::RandRange(0, 1) == 0)
			Turn(i);
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("TurnFailed"));
			UE_LOG(LogTemp, Warning, TEXT("TurnFailed"));
		}
	}
UE_LOG(LogTemp, Warning, TEXT("Beginplay"));

GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("TotalDistance: %f"), TotalDistance)); //[도전 기능] 위의 반목문이 끝나면, 움직인 총 거리, 이동 성공 횟수, 회전 성공 횟수를 출력한다.
GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("MoveCount: %d"), MoveCount));
GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("TurnCount: %d"), TurnCount));

UE_LOG(LogTemp, Warning, TEXT("TotalDistance: %f"), TotalDistance);
UE_LOG(LogTemp, Warning, TEXT("MoveCount: %d"), MoveCount);
UE_LOG(LogTemp, Warning, TEXT("TurnCount: %d"), TurnCount);

}

void AMyActor::Move(int32 Index) //[도전 기능] Move에 Index라는 매개변수를 추가한다. 이는 For문으로부터 i값(반복 횟수)을 받아오게 되며, 현재 몇 번째 실행인지를 출력한다.
{
	PrevLocation = GetActorLocation(); //[도전 기능] 액터가 이동하기 직전, 현재 위치를 미리 기록해두는 것으로 누적 거리 계산에 활용이 가능하다.
	FVector Target; 
	Target.X = FMath::FRandRange(-50.0, 50.0);
	Target.Y = FMath::FRandRange(-50.0, 50.0);
	Target.Z = 0;

	AddActorWorldOffset(Target); //Target이라는 로컬 변수의 벡터 값을 현재 위치에 더해주는 것으로 이동을 구현한다.

	TotalDistance += FVector::Dist(PrevLocation, GetActorLocation());  //[도전 기능] Move를 반복하는 동안 계속해서 현재 위치와 이전 위치를 비교하여, 그 거리를 TotalDistance에 더해준다. 이 방식으로 누적 이동 거리를 산출한다. 회전으로는 거리가 변하지 않기 때문에, 이는 Move()에만 구현하면 된다.
	MoveCount++; //[도전 기능] 몇 번이나 성공했는지를 기록하기 위해, Move()가 실행 될 때마다 MoveCount 정수 타입 변수도 1씩 값을 더해준다.

	FVector CurrentLocation = GetActorLocation(); //[도전 기능] 액터의 현재 위치만을 출력하던 결과값에 몇 번째 실행인지 표시해주기 위해, for문의 i값을 받아온 Index 매개변수를 활용한다.
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("[Move %d] %s"), Index + 1, *CurrentLocation.ToString())); //단순히 위치 값만 출력할 땐 필요 없었지만, 스트링의 인자로 사용할 땐 CurrentLocation 앞에 반드시 *을 붙여준다.
	}
	UE_LOG(LogTemp, Warning, TEXT("Location %d = %s"), Index +1 , *CurrentLocation.ToString());


}

void AMyActor::Turn(int32 Index) //Move와 전체적인 개요는 같다. 오히려 누적 거리를 산출하는 과정엔 해당 사항이 없으므로 더 간소하다.
{
	FRotator DeltaRotation;
	DeltaRotation.Yaw = FMath::FRandRange(-180.0, 180.0);
	DeltaRotation.Pitch = 0;
	DeltaRotation.Roll = 0;

	AddActorWorldRotation(DeltaRotation);

	TurnCount++;

	FRotator CurrentRotation = GetActorRotation();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("[Turn %d] %s"), Index + 1, *CurrentRotation.ToString()));
	}
	UE_LOG(LogTemp, Warning, TEXT("Rotation %d = %s"), Index + 1,  *CurrentRotation.ToString());
}