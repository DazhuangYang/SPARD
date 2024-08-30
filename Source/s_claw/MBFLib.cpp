// Fill out your copyright notice in the Description page of Project Settings.


#include "MBFLib.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "DataTableUtils.h"
//ydz-self
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>


//Declare General Log Category, source file .cpp
DEFINE_LOG_CATEGORY(LogUtiliesNode);

bool UMBFLib::SaveDatatotxt(const FString& DataString, const FString& DataFilePath)
{
	// 定义/打开输出的txt文件
	std::ofstream out_txt_file;
	std::string DataFP = "F:/temp/UETXTSave.txt";
	if (DataFilePath.Len() != 0)
	{
		DataFP = TCHAR_TO_UTF8(*DataFilePath);
	}
	out_txt_file.open(DataFP, std::ios::out | std::ios::app);
	out_txt_file << std::fixed;
	out_txt_file << TCHAR_TO_UTF8(*DataString) << "\n";

	out_txt_file.close();

	return true;
}

bool UMBFLib::FillDataTableFromCSVString(UDataTable* DataTable, const FString& CSVString)
{
	if (!DataTable || (CSVString.Len() == 0))
	{
		UE_LOG(LogUtiliesNode, Warning, TEXT("FillDataTableFromCSVString -> Can't fill DataTable with CSVString: %."), *CSVString);
		return false;
	}
	// Call bulit-in function
	TArray<FString> Errors = DataTable->CreateTableFromCSVString(CSVString);
	// 定义/打开输出的txt文件
	std::ofstream out_txt_file;
	out_txt_file.open("F:/temp/numbers_test2.txt", std::ios::out | std::ios::trunc);
	out_txt_file << std::fixed;
	out_txt_file << TCHAR_TO_UTF8(*CSVString);
	// 保存数据到文件中
	for (int i = 0; i < 10; i++)
	{
		out_txt_file << std::setprecision(5) << i << "\n";
	}
	// 关闭文件
	out_txt_file.close();


	if (Errors.Num())
	{
		// It has some error message
		for (const FString& Error : Errors)
		{
			UE_LOG(LogUtiliesNode, Warning, TEXT("%s"), *Error);
		}
		return false;
	}

	return true;
}

bool UMBFLib::FillDataTableFromCSVFile(UDataTable* DataTable, const FString& CSVFilePath)
{
	FString CSVString;
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*CSVFilePath))
	{
		// Supports all combination of ANSI/Unicode files and platforms.
		FFileHelper::LoadFileToString(CSVString, *CSVFilePath);
	}
	else
	{
		UE_LOG(LogUtiliesNode, Warning, TEXT("FillDataTableFromCSVFile -> Cannot find CSV file %s"), *CSVFilePath);
		return false;
	}
	return UMBFLib::FillDataTableFromCSVString(DataTable, CSVString);
}

bool UMBFLib::FillDataTableFromJSONString(UDataTable* DataTable, const FString& JSONString)
{
	if (!DataTable || (JSONString.Len() == 0))
	{
		UE_LOG(LogUtiliesNode, Warning, TEXT("FillDataTableFromJSONString -> Can't fill DataTable with JSONString: %."), *JSONString);
		return false;
	}
	// Call bulit-in function 
	TArray<FString> Errors = DataTable->CreateTableFromJSONString(JSONString);

	if (Errors.Num())
	{
		// It has some error message
		for (const FString& Error : Errors)
		{
			UE_LOG(LogUtiliesNode, Warning, TEXT("%s"), *Error);
		}
		return false;
	}

	return true;
}

bool UMBFLib::FillDataTableFromJSONFile(UDataTable* DataTable, const FString& JSONFilePath)
{
	FString JSONString;
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*JSONFilePath))
	{
		// Supports all combination of ANSI/Unicode files and platforms.
		FFileHelper::LoadFileToString(JSONString, *JSONFilePath);
	}
	else
	{
		UE_LOG(LogUtiliesNode, Warning, TEXT("FillDataTableFromJSONFile -> Cannot find CSV file %s"), *JSONFilePath);
		return false;
	}
	return UMBFLib::FillDataTableFromJSONString(DataTable, JSONString);
}

void UMBFLib::GetDataTableAsCSVString(UDataTable* DataTable, FString& CSVString)
{
	CSVString = FString();

	if (!DataTable || (DataTable->RowStruct == nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("UMBFLib::GetTableAsCSV : Missing DataTable or RowStruct !"));
		return;
	}

	// First build array of properties
	TArray<FProperty*> StructProps;
	for (TFieldIterator<FProperty> It(DataTable->RowStruct); It; ++It)
	{
		FProperty* Prop = *It;
		check(Prop != nullptr);
		StructProps.Add(Prop);
	}

	// First row, column titles, taken from properties
	CSVString += TEXT("---");
	for (int32 PropIdx = 0; PropIdx < StructProps.Num(); PropIdx++)
	{
		CSVString += TEXT(",");
		CSVString += StructProps[PropIdx]->GetName();
	}
	CSVString += TEXT("\n");

	// Now iterate over rows
	for (auto RowIt = DataTable->GetRowMap().CreateConstIterator(); RowIt; ++RowIt)
	{
		FName RowName = RowIt.Key();
		CSVString += RowName.ToString();

		uint8* RowData = RowIt.Value();
		for (int32 PropIdx = 0; PropIdx < StructProps.Num(); PropIdx++)
		{
			CSVString += TEXT(",");
			CSVString += DataTableUtils::GetPropertyValueAsString(StructProps[PropIdx], RowData, EDataTableExportFlags::None);
		}
		CSVString += TEXT("\n");
	}
}



void UMBFLib::GetDataTableAsCSVFile(UDataTable* DataTable, const FString& CSVFilePath)
{
	FString CSVString;
	UMBFLib::GetDataTableAsCSVString(DataTable, CSVString);
	if (CSVString.Len() == 0)
	{
		return;
	}
	FFileHelper::SaveStringToFile(CSVString, *CSVFilePath, FFileHelper::EEncodingOptions::ForceUTF8);
}