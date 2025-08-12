// Fill out your copyright notice in the Description page of Project Settings.


#include "Teacher.h"

UTeacher::UTeacher()
{
	Name = TEXT("박선생");
	Year = 3;
	Id = 1;

}

void UTeacher::DoLesson()
{

	UE_LOG(LogTemp, Log, TEXT("%d 년차선생님 %d번 %s 님이 수업을 강의합니다."), Year, Id, *Name);

}
