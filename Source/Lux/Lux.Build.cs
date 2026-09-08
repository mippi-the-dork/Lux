// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Lux : ModuleRules
{
    public Lux(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
			}
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "EditorSubsystem" // Maps header paths publicly across the compilation chain
			}
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "UnrealEd",
                "LevelEditor",
                "Slate",
                "SlateCore",
                "Blutility",
                "UMG",
                "UMGEditor",
                "ToolMenus"
            }
            );



        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );
    }
}
