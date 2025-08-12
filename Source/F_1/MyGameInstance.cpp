// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	//TCHAR mylog[] = TEXT("Hello world");
	//UE_LOG(LogTemp, Log, TEXT("%s"), mylog);

	//FString str = mylog;
	//UE_LOG(LogTemp, Log, TEXT("%s"), *str);

	//FString Left, Right;

	//if (str.Split(TEXT(" "), &Left, &Right))
	//{
	//	UE_LOG(LogTemp, Log, TEXT("split Test:%s 와 %s"), *Left, *Right);
	//}

	int32 Intvalue = 32;
	float FloatValue = 3.14f;


	//Printf 데이터형 포맷팅해서 Fstring 만들어줌.
	
	FString FloatString = FString::SanitizeFloat(FloatValue);
	FString IntString = FString::FromInt(Intvalue);

	//UE_LOG(LogTemp, Log, TEXT("%s"), *IntString);
	//UE_LOG(LogTemp, Log, TEXT("%s"), *FloatString);

	int32 IntValueFromString = FCString::Atoi(*IntString);
	float FloatValueFromString = FCString::Atof(*FloatString);

	FString FloatIntString = FString::Printf(TEXT("Int %d , Float:%f"), IntValueFromString, FloatValueFromString);
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);

	FName N1 = TEXT("H1");
	FName N2 = TEXT("H1");

	if (N1 == N2)
	{
		UE_LOG(LogTemp, Log, TEXT("같음"));
	}
}
