// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LocalMultiplayer : ModuleRules
{
	public LocalMultiplayer(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] {"CustomSplitscreen"});
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });
	}
}
