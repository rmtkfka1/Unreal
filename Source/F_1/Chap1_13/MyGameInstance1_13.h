// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance1_13.generated.h"

class  UMyObject_1_13;

struct  MYData
{
	int Order = -1;
	FString Name = "Default";


	friend FArchive& operator<<(FArchive& Ar, MYData& data)
	{
		Ar << data.Order;
		Ar << data.Name;
		return Ar;
	}


};

UCLASS()
class F_1_API UMyGameInstance1_13 : public UMyGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance1_13();
	virtual void Init() override;


private:
	TObjectPtr<UMyObject_1_13> MyObject;
};
