// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

class UCard;

/**
 * 
 */
UCLASS()
class F_1_API UPerson : public UObject
{
	GENERATED_BODY()
	
public:
	UPerson();

	FORCEINLINE const FString& GetName() const;
	FORCEINLINE void SetName(const FString& Inname);

	FORCEINLINE const UCard* GetCard() const { return Card;  };
	FORCEINLINE void SetCard(UCard* newCard) { Card = newCard; }

protected:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32	Year;

	//Composition (UE4 방식)
	//UPROPERTY()
	//class UCard* Card;

	//Composition (UE5 방식)
	UPROPERTY()
	TObjectPtr<UCard> Card;


private:


};
