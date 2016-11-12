// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAS : ModuleRules
{
	public GAS(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "GameplayAbilities",
                "GameplayAbilitiesEditor",
                "GameplayTags",
                "GameplayTagsEditor",
                "GameplayTasks"
            }
       );
    }
}
