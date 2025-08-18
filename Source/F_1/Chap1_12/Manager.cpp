// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager.h"
#include "Student_1_12.h"
void Manager::AddReferencedObjects(FReferenceCollector& Collector)
{
	if (SafeStudent->IsValidLowLevel())
	{
		Collector.AddReferencedObject(SafeStudent);
	}
}
