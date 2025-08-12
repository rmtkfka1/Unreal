// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include  "Student.h"
#include "Staff.h"
#include "Teacher.h"
#include "Card.h"
UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본학교");

}


//This is Test for Interface
void UMyGameInstance::Init()
{
	Super::Init();

	TArray<UPerson*> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>() };

	for (const auto& Person : Persons)
	{
		const UCard* Card =Person->GetCard();
		ECardType CardType= Card->GetTypeCard();
		UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류 %d"), *Person->GetName(), CardType);

		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/F_1.EcardType"));
		if (CardEnumType)
		{
			FString CardMetaData =  CardEnumType->GetDisplayNameTextByValue((int64)CardType).ToString();
			UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류 %s"), *Person->GetName(), *CardMetaData);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("=================="));
}
