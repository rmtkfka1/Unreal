﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"

UPerson::UPerson()
{
	Name = TEXT("홍길동");
	Year = 1;
}

void UPerson::DoLesson()
{
	UE_LOG(LogTemp, Log, TEXT("%s 님이 수업에 참여하였습니다."), *Name);
}


const FString& UPerson::GetName() const
{
	return Name;
}

void UPerson::SetName(const FString& Inname)
{
	Name = Inname;
}