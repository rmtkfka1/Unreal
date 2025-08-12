// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class UCourseInfo;
/**
 * 
 */
UCLASS()
class F_1_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();

	virtual void Init() override;

private:
	UPROPERTY()
	FString SchoolName;


	//DELETEGATE
	UPROPERTY()
	TObjectPtr<UCourseInfo> CourseInfo;
	
};
