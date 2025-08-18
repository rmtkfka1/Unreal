// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance_1_12.h"
#include "Student_1_12.h"
#include "Manager.h"


void CheckUObjectIsValid(const UObject* Object, const FString& InTag)
{
	if (Object->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효한 언리얼 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효하지않은 언리얼 오브젝트"), *InTag);
	}


}

void CheckUObjectIsNull(const UObject* Object, const FString& InTag)
{
	if (Object==nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 널 포인터 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 널 포인터가 아닌 오브젝트"), *InTag);
	}

}

void UMyGameInstance_1_12::Init()
{
	Super::Init();
	
	NonPropStudent = NewObject<UStudent_1_12>();
	PropStudent = NewObject<UStudent_1_12>();

	NonPropStudentArray.Add(NewObject<UStudent_1_12>());
	PropStudentArray.Add(NewObject<UStudent_1_12>());

	StudentManager = new Manager(NewObject<UStudent_1_12>());
}

void UMyGameInstance_1_12::Shutdown()
{
	Super::Shutdown();


	const UStudent_1_12* SafeStudent = StudentManager->GetSafeStudent();

	delete StudentManager;
	StudentManager = nullptr;

	CheckUObjectIsNull(SafeStudent, TEXT("SafeStudent"));
	CheckUObjectIsValid(SafeStudent, TEXT("SafeStudent"));


	CheckUObjectIsNull(NonPropStudent, TEXT("NonPropStudent"));
	CheckUObjectIsValid(NonPropStudent, TEXT("NonPropStudent"));

	CheckUObjectIsNull(PropStudent, TEXT("PropStudent"));
	CheckUObjectIsValid(PropStudent, TEXT("PropStudent"));


	CheckUObjectIsNull(NonPropStudentArray[0], TEXT("NonPropStudent"));
	CheckUObjectIsValid(NonPropStudentArray[0], TEXT("NonPropStudent"));

	CheckUObjectIsNull(PropStudentArray[0], TEXT("PropStudent"));
	CheckUObjectIsValid(PropStudentArray[0], TEXT("PropStudent"));



}
