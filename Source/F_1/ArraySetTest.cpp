// Fill out your copyright notice in the Description page of Project Settings.


#include "ArraySetTest.h"
#include "Algo/Accumulate.h"

FString MakeRandomName()
{
	TCHAR FirstChar[] = TEXT("김이박최");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[] = TEXT("수은원연");

	TArray<TCHAR> Name;
	Name.SetNum(3);

	Name[0] = FirstChar[FMath::RandRange(0, 3)];
	Name[1] = MiddleChar[FMath::RandRange(0, 3)];
	Name[2] = LastChar[FMath::RandRange(0, 3)];

	return Name.GetData();

}

void UArraySetTest::Init()
{
	Super::Init();

	{
		const int32 ArrayNum = 10;

		TArray<int32> v;
		TArray<int32> v2;

		for (int32 i = 1; i <= ArrayNum; ++i)
		{
			v.Emplace(i);
		}

		v.RemoveAll([](int32 val) {return val % 2 == 0; });
		v += {2, 4, 6, 8, 10};

		int32 temp[] = { 1,3,5,7,9,2,4,6,8,10 };
		v2.AddUninitialized(ArrayNum);
		FMemory::Memcpy(v2.GetData(), temp, sizeof(int32) * ArrayNum);
		int32 sum = Algo::Accumulate(v, 0);

		ensure(v == v2);
	}

	{
		TSet<int32> s;

		for (int32 i = 1; i <= 10; ++i)
		{
			s.Emplace(i);
		}

		s.Remove(2);
		s.Remove(4);
		s.Remove(6);
		s.Remove(8);
		s.Remove(10);

		s.Emplace(2);
		s.Emplace(4);
		s.Emplace(6);
		s.Emplace(8);
		s.Emplace(10);

	}

	{
		const int32 ArrayNum = 300;

		for(int32 i = 0; i < ArrayNum; ++i)
		{
			Students.Emplace(FStudentData(MakeRandomName(), i));
		}

		{
			TArray<FString> AllStudentNames;

			Algo::Transform(Students, AllStudentNames, [](const FStudentData& Student) {
				return Student.Name;
				});

			UE_LOG(LogTemp, Log, TEXT("All Student Names 의 수 : %d"), AllStudentNames.Num());
		}
		{

			TSet<FString> AllUniqueStudentNames;

			Algo::Transform(Students, AllUniqueStudentNames, [](const FStudentData& Student) {
				return Student.Name;
				});

			UE_LOG(LogTemp, Log, TEXT("중복없는 All Student Names 의 수 : %d"), AllUniqueStudentNames.Num());

		}
	}

	{

		Algo::Transform(Students, StudentMap, [](const FStudentData& Student) {
			return TPair<int32, FString>(Student.Order, Student.Name);
			});

		UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 맵의 레코드 의 수 : %d"), StudentMap.Num());

		TMap<FString, int32> StudentsMapByUniqueName;

		Algo::Transform(Students, StudentsMapByUniqueName, [](const FStudentData& Student) {
			return TPair<FString, int32>(Student.Name, Student.Order);
			});

		UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 맵의 레코드 의 수 : %d"), StudentsMapByUniqueName.Num());

		TMultiMap<FString, int32> StudentsMultiMapName;

		Algo::Transform(Students, StudentsMultiMapName, [](const FStudentData& Student) {
			return TPair<FString, int32>(Student.Name, Student.Order);
			});

		UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 멀티맵의 레코드 의 수 : %d"), StudentsMultiMapName.Num());

		const FString TargetName(TEXT("이혜은"));

		TArray<int32> Allorders;

		StudentsMultiMapName.MultiFind(TargetName, Allorders);

		UE_LOG(LogTemp, Log, TEXT("이름이 %s 인 학생의 수 %d  "), *TargetName,Allorders.Num());

	}

	{
		TSet<FStudentData> SetStudentData;

		for (int32 i = 0; i < Students.Num(); ++i)
		{
			SetStudentData.Emplace(FStudentData(MakeRandomName(),i));
		}

	}
};
