// Fill out your copyright notice in the Description page of Project Settings.


#include "School.h"

USchool::USchool()
{
	SchoolName = TEXT("기본학교"); //CDO 에 저장 // CDO 는 엔진이 초기화되는 과정에서 생성됨.
}

void USchool::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("==========================="));
	UClass* ClassRunTime = GetClass();
	UClass* ClassCompileTime = USchool::StaticClass();

	//check(ClassRunTime != ClassCompileTime);
	//ensure(ClassRunTime != ClassCompileTime);
	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름 %s"), *ClassRunTime->GetName());
	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름 %s"), *ClassCompileTime->GetName());
	FString DefaultSchoolName = GetClass()->GetDefaultObject<USchool>()->SchoolName;
	UE_LOG(LogTemp, Log, TEXT("학교 이름 Default 값 %s"), *DefaultSchoolName);
	SchoolName = TEXT("한국공학대학교");

	UE_LOG(LogTemp, Log, TEXT("학교 이름 %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("==========================="));
}
