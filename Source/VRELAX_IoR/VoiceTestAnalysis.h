// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VoiceTestAnalysis.generated.h"

/**
 * 
 */
UCLASS()
class VRELAX_IOR_API UVoiceTestAnalysis : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "Start Voice Test")
		static bool StartVoiceAnalysis(FString message);
	
	
};
