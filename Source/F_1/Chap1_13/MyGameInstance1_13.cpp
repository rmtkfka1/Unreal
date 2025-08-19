// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance1_13.h"
#include "MyObject_1_13.h"
#include "JsonObjectConverter.h"

UMyGameInstance1_13::UMyGameInstance1_13()
{
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


}
