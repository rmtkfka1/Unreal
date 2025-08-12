﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

UENUM()
enum class ECardType :uint8
{
	Student = 1 UMETA(DisplayName = "For Student"),
	Teacher UMETA(DisplayName = "For Teacehr"),
	Staff  UMETA(DisplayName = "For Staff"),
	Invaild
};

/**
 * 
 */
UCLASS()
class F_1_API UCard : public UObject
{
	GENERATED_BODY()

public:
	UCard();
	ECardType GetTypeCard() const { return CardType; }
	void SetCardType(ECardType type) { CardType = type; }

private:
	UPROPERTY()
	ECardType CardType;

	UPROPERTY()
	uint32 Id;
	
};
