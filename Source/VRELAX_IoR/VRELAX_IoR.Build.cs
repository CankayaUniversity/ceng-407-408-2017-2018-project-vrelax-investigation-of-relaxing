// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class VRELAX_IoR : ModuleRules
{
	public VRELAX_IoR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

	    PublicAdditionalLibraries.Add(@"D:\UnrealProjects\VRELAX_IoR\Binaries\Win64\gsl.lib");
	    PublicAdditionalLibraries.Add(@"D:\UnrealProjects\VRELAX_IoR\Binaries\Win64\cblas.lib");

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
