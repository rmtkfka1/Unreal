// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"

UStudent::UStudent()
{
	Name = TEXT("이학생");
	Year = 1;
	Id = 1;

	Card->SetCardType(ECardType::Student);
}

void UStudent::DoLesson()
{
	UE_LOG(LogTemp, Log, TEXT("%d 년차 %d번 %s 님이 수업을 듣습니다."), Year, Id, *Name);
}
