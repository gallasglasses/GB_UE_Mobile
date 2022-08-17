// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MobileProject3 : ModuleRules
{
	public MobileProject3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "ImageWrapper" });

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "Launch", "ApplicationCore" });
			PrivateIncludePaths.AddRange(new string[] { "/Source/Runtime/Launch/Private"});
			string pluginPath = Utils.MakePathRelativeTo(ModuleDirectory,Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add(new ReceiptProperty("MobileProject3", System.IO.Path.Combine(pluginPath, "PhotoLibrary_APL.xml")));
		}
	}
}
