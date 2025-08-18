// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UStudent_1_12;

/**
 * 
 */

 //일반 c++ 에서 unrealObject 를 사용하려면 FGCObject 를 상속받아야 한다. (두가지 오버로드 메서드가 있다.)
class F_1_API Manager : public FGCObject
{
public:
	Manager(UStudent_1_12* InStudent) : SafeStudent(InStudent) {};

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override
	{
		return TEXT("Manager");
	}
	
	const UStudent_1_12* GetSafeStudent() const
	{
		return SafeStudent;
	}

	UStudent_1_12* SafeStudent = nullptr;
};
