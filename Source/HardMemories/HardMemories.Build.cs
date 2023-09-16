// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HardMemories : ModuleRules
{
	public HardMemories(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "GameplayAbilities",
	        "GameplayTags",
	        "GameplayTasks",
	        "UMG",
	        "Core",
	        "CoreUObject",
	        "Engine",
	        "InputCore",
	        "SlateCore",
	        "NavigationSystem",
	        "AIModule"
        });
        
        PublicIncludePaths.Add("HardMemories/Public");
	}
}
