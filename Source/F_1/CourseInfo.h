// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseInfo.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInfoOnChagnedSignature, const FString&, const FString&)
/**
 * 
 */
UCLASS()
class F_1_API UCourseInfo : public UObject
{
	GENERATED_BODY()
	
public:
	UCourseInfo();


	void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents);
	FCourseInfoOnChagnedSignature OnChanged;

private:

	FString Contents;

};
