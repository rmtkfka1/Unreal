// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "School.generated.h"

/**
 * 
 */
UCLASS()
class F_1_API USchool : public UGameInstance
{
	GENERATED_BODY()

public:
	USchool();

	virtual void Init() override;
	
private:
	UPROPERTY()
	FString SchoolName;

};
