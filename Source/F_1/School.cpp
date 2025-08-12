// Fill out your copyright notice in the Description page of Project Settings.


#include "School.h" //가장위쪽에 위치해야함..
#include "Student.h"
#include "Teacher.h"

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


	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();

	Student->SetName(TEXT("학생5번"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생이름 %s "), *Student->GetName());

	FString CurrentTeachrName;
	FString NewTeachrName=TEXT("김상혁");
	FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	if (NameProp)
	{
		NameProp->GetValue_InContainer(Teacher, &CurrentTeachrName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름 %s "), *CurrentTeachrName);

		NameProp->SetValue_InContainer(Teacher, &NewTeachrName);
		UE_LOG(LogTemp, Log, TEXT("새로운 선생님 이름 %s "), *NewTeachrName);
		UE_LOG(LogTemp, Log, TEXT("새로운 선생님 이름 %s "), *Teacher->GetName());
	}

	Student->DoLesson();
	Teacher->DoLesson();


}
