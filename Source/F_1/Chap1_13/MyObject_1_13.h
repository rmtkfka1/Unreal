// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject_1_13.generated.h"

/**
 * 
 */
UCLASS()
class F_1_API UMyObject_1_13 : public UObject
{
	GENERATED_BODY()

public:
	int32 GetOrder() const { return Order; }
	FString GetName() const { return Name; }

	void SetOrder(int32 InOrder) { Order = InOrder; }
	void SetName(const FString& InName) { Name = InName; }


	virtual  void Serialize(FArchive& Ar) override;



public:
	UMyObject_1_13();

	UPROPERTY()
	int32 Order = -1;

	UPROPERTY()
	FString Name = "Default";
	
};
