// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAD2006 : ModuleRules
{
	public GAD2006(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
