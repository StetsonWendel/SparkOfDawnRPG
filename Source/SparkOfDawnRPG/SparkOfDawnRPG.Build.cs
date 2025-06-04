// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SparkOfDawnRPG : ModuleRules
{
	public SparkOfDawnRPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
