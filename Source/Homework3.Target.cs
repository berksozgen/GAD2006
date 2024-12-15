// Develloped by R. Berk Sozgen for GAD2006.

using UnrealBuildTool;
using System.Collections.Generic;

public class Homework3Target : TargetRules
{
	public Homework3Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Homework3" } );
	}
}
