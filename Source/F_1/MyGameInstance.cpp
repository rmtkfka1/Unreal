// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include  "Student.h"
#include "Staff.h"
#include "Teacher.h"
#include "Card.h"
#include "CourseInfo.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("학교");

}


//This is Test for Interface
void UMyGameInstance::Init()
{
	Super::Init();

	CourseInfo = NewObject<UCourseInfo>(this);

	UE_LOG(LogTemp, Log, TEXT("=================="));

	UStudent* S1 = NewObject<UStudent>();
	S1->SetName(TEXT("학생1"));
	UStudent* S2 = NewObject<UStudent>();
	S2->SetName(TEXT("학생2"));
	UStudent* S3 = NewObject<UStudent>();
	S3->SetName(TEXT("학생3"));

	CourseInfo->OnChanged.AddUObject(S1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(S2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(S3, &UStudent::GetNotification);

	CourseInfo->ChangeCourseInfo(SchoolName, TEXT(":변경된 학사정보 3"));

	UE_LOG(LogTemp, Log, TEXT("=================="));
}
