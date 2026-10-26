// Copyright Mippithedork 2026, Inc. All Rights Reserved.
using UnrealBuildTool;

public class Lux : ModuleRules
{
    public Lux(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "EditorSubsystem"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "UnrealEd", "LevelEditor", "Slate", "SlateCore", "InputCore",
            "ToolMenus", "DeveloperSettings", "Projects", "AppFramework", "Settings"
        });
    }
}
