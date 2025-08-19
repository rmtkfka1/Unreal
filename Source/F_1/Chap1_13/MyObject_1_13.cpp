// Fill out your copyright notice in the Description page of Project Settings.


#include "MyObject_1_13.h"



UMyObject_1_13::UMyObject_1_13()
{

}

void UMyObject_1_13::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	Ar << Order;
	Ar << Name;
}