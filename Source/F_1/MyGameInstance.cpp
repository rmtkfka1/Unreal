// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include  "Student.h"
#include "Staff.h"
#include "Teacher.h"
UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본학교");

}


//This is Test for Interface
void UMyGameInstance::Init()
{
	Super::Init();

	TArray<UPerson*> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>() };

	//UE_LOG(LogTemp, Log, TEXT("=================="));

	//for (const auto& Person : Persons)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("구성원이름 : %s"), *Person->GetName());
	//}
	//
	//UE_LOG(LogTemp, Log, TEXT("=================="));

	for (const auto& Person : Persons)
	{
		ILessonInterface* Interface = Cast<ILessonInterface>(Person);

		if (Interface)
		{
			Interface->DoLesson();
		}

	}

	UE_LOG(LogTemp, Log, TEXT("=================="));
}
