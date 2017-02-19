// Copyright 2016 Pixela Labs. All Rights Reserved.
using UnrealBuildTool;
using System.IO;

public class UVR : ModuleRules
{
	private string ModulePath
	{
		get
		{
			//return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name));
			string ModuleFilename = UnrealBuildTool.RulesCompiler.GetFileNameFromType(GetType());
			string ModuleBaseDirectory = Path.GetDirectoryName(ModuleFilename);
			return ModuleBaseDirectory;
		}
	}

	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
	}

	public UVR(TargetInfo Target)
	{

		PublicIncludePaths.AddRange(
			new string[] {
				"UVR/Public",
				"../../../../Source/Runtime/OpenGLDrv/Public",
				// ... add public include paths required here ...
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				"UVR/Private",
				"UVR/Private/Interface",
				"../../../../Source/Runtime/OpenGLDrv/Public",
				"../../../../Source/Runtime/OpenGLDrv/Private",
				"../../../../Source/Runtime/Renderer/Private",
				Path.Combine(ThirdPartyPath, "OpenGL", "")
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
				"InputDevice",
				"Networking",
				"OpenGLDrv", // << only pub/priv or pub+priv
				"RHI",
				"RenderCore",
				"Renderer",
				"ShaderCore",
				"Slate",
				"SlateCore",
				"Sockets"
				// ... add other public dependencies that you statically link with here ...
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"OpenGLDrv"
				// ... add private dependencies that you statically link with here ...
			}
			);

		if (UEBuildConfiguration.bBuildEditor == true)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		AddThirdPartyPrivateStaticDependencies(Target, "OpenGL"); // <<
		PublicAdditionalLibraries.Add("opengl32.lib");
		//PublicAdditionalFrameworks.Add(new UEBuildFramework("OpenGL"));

		LoadVrpnLib(Target);
	}

	public bool LoadVrpnLib(TargetInfo Target)
	{
		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
			string LibrariesPath = Path.Combine(ThirdPartyPath, "VRPN", "Lib/" + PlatformString);

			//@todo: There are also debug versions: vrpnd.lib and quatd.lib
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "vrpn.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "quat.lib"));

			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "VRPN", "Include"));

			return true;
		}

		return false;
	}

	private void Trace(string msg)
	{
		Log.TraceError("Plugin + : " + msg);
	}
}
