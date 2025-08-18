// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance_1_12.generated.h"



/**
 * 
 */
UCLASS()
class F_1_API UMyGameInstance_1_12 : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;
	

private:
	TObjectPtr<class UStudent_1_12> NonPropStudent;

	UPROPERTY()
	TObjectPtr<class UStudent_1_12> PropStudent;

	TArray<TObjectPtr<class UStudent_1_12>> NonPropStudentArray;

	UPROPERTY()
	TArray<TObjectPtr<class UStudent_1_12>> PropStudentArray;


public:
	class  Manager* StudentManager;


};
