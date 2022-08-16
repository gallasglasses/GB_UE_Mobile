// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MobileProject2 : ModuleRules
{
	public MobileProject2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		if (Target.Platform == UnrealTargetPlatform.Android)
        {
			//PublicAdditionalLibraries.AddRange(new string[] { System.IO.Path.Combine(ModuleDirectory, "PugiXML", "src", "pugixml.lib") });
			PublicSystemLibraryPaths.AddRange(new string[] { System.IO.Path.Combine(ModuleDirectory, "PugiXML", "src", "pugixml.lib") });
        }
	}
}