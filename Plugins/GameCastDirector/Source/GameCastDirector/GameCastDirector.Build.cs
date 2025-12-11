// Copyright Epic Games

using UnrealBuildTool;

public class GameCastDirector : ModuleRules
{
    public GameCastDirector(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[]
        {
            // Add public include paths if needed
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            // Add private include paths if needed
        });

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",

            // REQUIRED FOR ANY UUserWidget, UImage, UMG Binding, Draw To Render Target
            "UMG",
            "Slate",
            "SlateCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "CoreUObject",
            "Engine",
            "Slate",
            "SlateCore",
            "UMG",

            // Optional but recommended (helpful for widget editor features)
            //"UMGEditor"
        });

        DynamicallyLoadedModuleNames.AddRange(new string[]
        {
        });
    }
}
