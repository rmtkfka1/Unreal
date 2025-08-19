// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance1_13.h"
#include "MyObject_1_13.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"

const  FString UMyGameInstance1_13::PackageName = TEXT("/Game/Student");
const  FString UMyGameInstance1_13::AssetName = TEXT("Student");

UMyGameInstance1_13::UMyGameInstance1_13()
{
	/*const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	static ConstructorHelpers::FObjectFinder<UMyObject_1_13> MyObjectFinder(*TopSoftObjectPath);

	if (MyObjectFinder.Succeeded())
	{
		MyObject = MyObjectFinder.Object;
		UE_LOG(LogTemp, Log, TEXT("생성자  MyObject found: Order = %d, Name = %s"), MyObject->GetOrder(), *MyObject->GetName());
	}
	else
	{
		MyObject = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("MyObject not found at path: %s"), *TopSoftObjectPath);
	}*/

}

void UMyGameInstance1_13::Init()
{
	Super::Init();

	MYData Data;
	Data.Order = 1;
	Data.Name = TEXT("Example");

	const FString SavePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Saved"));
	UE_LOG(LogTemp, Warning, TEXT("Save Path: %s"), *SavePath);

	{
		FString FileName = TEXT("MyData.txt");
		FString FullPath = FPaths::Combine(*SavePath, *FileName);

		UE_LOG(LogTemp, Log, TEXT("Full Path: %s"), *FullPath);

		FPaths::MakeStandardFilename(FullPath);

		UE_LOG(LogTemp, Log, TEXT("Standardized Path: %s"), *FullPath);

		FArchive* FileArchive = IFileManager::Get().CreateFileWriter(*FullPath);

		if (FileArchive)
		{
			*FileArchive << Data;
			FileArchive->Close();
			delete FileArchive;

		}

		MYData LoadedData;

		FArchive* LoadArchive = IFileManager::Get().CreateFileReader(*FullPath);

		if (LoadArchive)
		{
			*LoadArchive << LoadedData;
			LoadArchive->Close();
			delete LoadArchive;
			UE_LOG(LogTemp, Log, TEXT("Loaded Data: Order = %d, Name = %s"), LoadedData.Order, *LoadedData.Name);
		} 
	
	}

	//Object Serialization Example
	{
		MyObject = NewObject<UMyObject_1_13>();
		MyObject->SetOrder(1);
		MyObject->SetName(TEXT("MyObject Example"));


		const FString FileName = TEXT("MyObjectData.bin");
		FString FullPath = FPaths::Combine(*SavePath, *FileName);
		FPaths::MakeStandardFilename(FullPath);

		UE_LOG(LogTemp, Log, TEXT("Standardized Path: %s"), *FullPath);

		TArray<uint8> BufferArray;
		FMemoryWriter MemoryWriter(BufferArray);
		MyObject->Serialize(MemoryWriter);

		TUniquePtr<FArchive> FileArchive(IFileManager::Get().CreateFileWriter(*FullPath));
		if (FileArchive)
		{
			*FileArchive << BufferArray;
			FileArchive->Close();
		}

		TArray<uint8> LoadedBufferArray;
		TUniquePtr<FArchive> LoadArchive(IFileManager::Get().CreateFileReader(*FullPath));

		if (LoadArchive)
		{
			UMyObject_1_13* MyObject2 = NewObject<UMyObject_1_13>();
			*LoadArchive << LoadedBufferArray;
			LoadArchive->Close();
			FMemoryReader MemoryReader(LoadedBufferArray);
			MyObject2->Serialize(MemoryReader);
			UE_LOG(LogTemp, Log, TEXT("MyObject Loaded: Order = %d, Name = %s"), MyObject->GetOrder(), *MyObject->GetName());
		}

	};



	//JsonTest
	{

		UMyObject_1_13* MyObjectJson = NewObject<UMyObject_1_13>();
		MyObjectJson->SetOrder(1);
		MyObjectJson->SetName(TEXT("Json Example"));

		FString JsonDataFileName = TEXT("JsonData.txt");
		FString JsonFullPath = FPaths::Combine(*SavePath, *JsonDataFileName);
		FPaths::MakeStandardFilename(JsonFullPath);
		UE_LOG(LogTemp, Log, TEXT("Standardized Path: %s"), *JsonFullPath);

		TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();

		FJsonObjectConverter::UStructToJsonObject(MyObjectJson->GetClass(), MyObjectJson, JsonObject);


		FString JsonOutString;
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonOutString);

		if (FJsonSerializer::Serialize(JsonObject, JsonWriter))
		{
			if (FFileHelper::SaveStringToFile(JsonOutString, *JsonFullPath))
			{
				UE_LOG(LogTemp, Log, TEXT("JSON data saved successfully to %s"), *JsonFullPath);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to save JSON data to %s"), *JsonFullPath);
			}
		}

		FString JsonInString;

		if (FFileHelper::LoadFileToString(JsonInString, *JsonFullPath))
		{
			TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonInString);

			TSharedPtr<FJsonObject> LoadedJsonObject;

			if(FJsonSerializer::Deserialize(JsonReader, LoadedJsonObject))
			{
				UMyObject_1_13* MyObjectFromJson = NewObject<UMyObject_1_13>();
				if (FJsonObjectConverter::JsonObjectToUStruct(LoadedJsonObject.ToSharedRef(), MyObjectFromJson->GetClass(), MyObjectFromJson))
				{
					UE_LOG(LogTemp, Log, TEXT("MyObject From JSON: Order = %d, Name = %s"), MyObjectFromJson->GetOrder(), *MyObjectFromJson->GetName());
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to convert JSON object to UMyObject_1_13"));
				}
		
			}
		}

	}




	//1-14
	//패키지 저장 및 로드

	SavePackage();

	//LoadPackageMy();

	//LoadStudentObject();

	//StreamableManager를 사용한 비동기 로드
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	StreamableHandle = StreamableManager.RequestAsyncLoad(TopSoftObjectPath, 
		[&]() {
			if(StreamableHandle.IsValid() && StreamableHandle->HasLoadCompleted())
			{
				UMyObject_1_13* TopStudent = Cast<UMyObject_1_13>(StreamableHandle->GetLoadedAsset());

				if (TopStudent)
				{
					UE_LOG(LogTemp, Log, TEXT("Loaded Top Student: Name = %s, Order = %d"), *TopStudent->GetName(), TopStudent->GetOrder());
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to load Top Student from path: %s"), *TopSoftObjectPath);
				}

				StreamableHandle->ReleaseHandle();
				StreamableHandle.Reset();


			}
		});



}

void UMyGameInstance1_13::SavePackage() const
{

	UPackage* ExistingPackage = ::LoadPackage(nullptr, *PackageName,LOAD_None);

	if (ExistingPackage)
	{
		ExistingPackage->FullyLoad();
	}


	//패키지생성
	UPackage* Package = CreatePackage(*PackageName);
	EObjectFlags Flags = RF_Public | RF_Standalone;

	UMyObject_1_13* TopStudent = NewObject<UMyObject_1_13>(Package,UMyObject_1_13::StaticClass(),*AssetName,Flags);
	TopStudent->SetName(TEXT("김상혁"));
	TopStudent->SetOrder(94);

	const int32  NumofSubs = 10;

	for (int32 i = 0; i < NumofSubs; ++i)
	{
		FString SubName = FString::Printf(TEXT("Subject %d"), i + 1);
		UMyObject_1_13* Subject = NewObject<UMyObject_1_13>(TopStudent, UMyObject_1_13::StaticClass(), *SubName, Flags);
		Subject->SetName(FString::Printf(TEXT("학생%d"), i));
		Subject->SetOrder(i + 1);
	}

	const FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = Flags;

	if(UPackage::SavePackage(Package,nullptr,*PackageFileName, SaveArgs))
	{ 
		UE_LOG(LogTemp, Log, TEXT("Package saved successfully %s:"), *PackageFileName);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to save package: %s"), *PackageFileName);
	}
}
void UMyGameInstance1_13::LoadPackageMy() const
{
	UPackage* LoadedPackage = LoadPackage(nullptr, *PackageName, LOAD_None);

	if(nullptr == LoadedPackage)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load package: %s"), *PackageName);
		return;
	}

	LoadedPackage->FullyLoad();

	UMyObject_1_13* TopStudent = FindObject<UMyObject_1_13>(LoadedPackage, *AssetName);

	if (TopStudent)
	{
		UE_LOG(LogTemp, Log, TEXT("Loaded Top Student: Name = %s, Order = %d"), *TopStudent->GetName(), TopStudent->GetOrder());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find Top Student in loaded package: %s"), *PackageName);
	}

}
void UMyGameInstance1_13::LoadStudentObject() const
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);

	UMyObject_1_13* TopStudent = LoadObject<UMyObject_1_13>(nullptr, *TopSoftObjectPath);

	if (TopStudent)
	{
		UE_LOG(LogTemp, Log, TEXT("Loaded Top Student: Name = %s, Order = %d"), *TopStudent->GetName(), TopStudent->GetOrder());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Top Student from path: %s"), *TopSoftObjectPath);
	}
}
;