// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArraySetTest.generated.h"

USTRUCT()
struct FStudentData
{
	GENERATED_BODY()

public:
	FStudentData()
	{
		Name = TEXT("Default Name");
		Order = -1;
	};

	FStudentData(const FString& InName, int32 InOrder)
		: Name(InName), Order(InOrder)
	{
	};

	friend FORCEINLINE uint32 GetTypeHash(const FStudentData& Student)
	{
		return GetTypeHash(Student.Order);
	}


	bool operator==(const FStudentData& Other) const
	{
		return Order == Other.Order;
	}

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Order;

	void Print() const
	{
		UE_LOG(LogTemp, Log, TEXT("Name: %s, Order: %d"), *Name, Order);
	}

};

/**
 * 
 */
UCLASS()
class F_1_API UArraySetTest : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

private:
	TArray<FStudentData> Students;

	UPROPERTY()
	TArray<TObjectPtr<class UP11>> P11Objects;

	TMap<int32, FString> StudentMap;

};
