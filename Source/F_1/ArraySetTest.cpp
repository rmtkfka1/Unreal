// Fill out your copyright notice in the Description page of Project Settings.


#include "ArraySetTest.h"
#include "Algo/Accumulate.h"
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

		int32 a = 5;

	}
};
