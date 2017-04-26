﻿// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnrealBuildTool
{
	/// <summary>
	/// Stores the version (or a unique build ID) for the build products of an application in a certain folder.
	/// 
	/// Allows the runtime to identify which modules are used for which files, and at which version they're at. This prevents stale binaries from being
	/// loaded by the runtime when making a local unversioned build, and allows faster incremental builds than compiling the build changelist into every 
	/// module when making versioned builds.
	/// </summary>
	[Serializable]
	class VersionManifest
	{
		public int Changelist;
		public int CompatibleChangelist;
		public string BuildId;
		public Dictionary<string, string> ModuleNameToFileName = new Dictionary<string, string>();

		/// <summary>
		/// Constructs the module map with the given changelist
		/// </summary>
		/// <param name="InChangelist">The changelist that these modules were built from</param>
		/// <param name="InCompatibleChangelist">The changelist that these modules are compatible with</param>
		/// <param name="InBuildId">The unique build id</param>
		public VersionManifest(int InChangelist, int InCompatibleChangelist, string InBuildId)
		{
			Changelist = InChangelist;
			CompatibleChangelist = InCompatibleChangelist;
			BuildId = InBuildId;
		}

		/// <summary>
		/// Merge another manifest into this one
		/// </summary>
		/// <param name="Other">The manifest to merge in</param>
		public void Include(VersionManifest Other)
		{
			foreach (KeyValuePair<string, string> Pair in Other.ModuleNameToFileName)
			{
				if (!ModuleNameToFileName.ContainsKey(Pair.Key))
				{
					ModuleNameToFileName.Add(Pair.Key, Pair.Value);
				}
			}
		}

		/// <summary>
		/// Gets the standard path for an manifest
		/// </summary>
		/// <param name="AppName">The modular app name being built</param>
		/// <param name="Configuration">The target configuration</param>
		/// <param name="Platform">The target platform</param>
		/// <param name="BuildArchitecture">The architecture of the target platform</param>
		/// <param name="bIsGameDirectory"></param>
		/// <returns>Filename for the app receipt</returns>
		public static string GetStandardFileName(string AppName, UnrealTargetPlatform Platform, UnrealTargetConfiguration Configuration, string BuildArchitecture, bool bIsGameDirectory)
		{
			string BaseName = AppName;
			if (Configuration != UnrealTargetConfiguration.Development && !(Configuration == UnrealTargetConfiguration.DebugGame && !bIsGameDirectory))
			{
				BaseName += String.Format("-{0}-{1}", Platform.ToString(), Configuration.ToString());
			}
			return String.Format("{0}{1}.modules", BaseName, BuildArchitecture);
		}

		/// <summary>
		/// Read an app receipt from disk
		/// </summary>
		/// <param name="FileName">Filename to read from</param>
		/// <returns>The receipt that was read</returns>
		public static VersionManifest Read(string FileName)
		{
			JsonObject Object = JsonObject.Read(FileName);

			int Changelist = Object.GetIntegerField("Changelist");

			int CompatibleChangelist;
			if(!Object.TryGetIntegerField("CompatibleChangelist", out CompatibleChangelist))
			{
				CompatibleChangelist = Changelist;
			}

			VersionManifest Receipt = new VersionManifest(Changelist, CompatibleChangelist, Object.GetStringField("BuildId"));

			JsonObject Modules = Object.GetObjectField("Modules");
			foreach (string ModuleName in Modules.KeyNames)
			{
				Receipt.ModuleNameToFileName.Add(ModuleName, Modules.GetStringField(ModuleName));
			}
			return Receipt;
		}

		/// <summary>
		/// Tries to read a receipt from disk.
		/// </summary>
		/// <param name="FileName">The filename that was read</param>
		/// <param name="Result">If successful, the receipt that was read. Null otherwise.</param>
		/// <returns>True if the file was read succesfully.</returns>
		public static bool TryRead(string FileName, out VersionManifest Result)
		{
			if (!File.Exists(FileName))
			{
				Result = null;
				return false;
			}
			try
			{
				Result = Read(FileName);
				return true;
			}
			catch (Exception)
			{
				Result = null;
				return false;
			}
		}

		/// <summary>
		/// Write the receipt to disk.
		/// </summary>
		/// <param name="FileName">The file to write to</param>
		public void Write(string FileName)
		{
			Directory.CreateDirectory(Path.GetDirectoryName(FileName));
			using(StreamWriter Writer = new StreamWriter(FileName))
			{
				Write(Writer);
			}
		}

		/// <summary>
		/// Write the receipt to disk.
		/// </summary>
		/// <param name="Writer">The writer to output to</param>
		public void Write(TextWriter Writer)
		{
			using (JsonWriter OutputWriter = new JsonWriter(Writer, true))
			{
				OutputWriter.WriteObjectStart();

				OutputWriter.WriteValue("Changelist", Changelist);
				if(CompatibleChangelist != Changelist)
				{
					OutputWriter.WriteValue("CompatibleChangelist", CompatibleChangelist);
				}
				OutputWriter.WriteValue("BuildId", BuildId);

				OutputWriter.WriteObjectStart("Modules");
				foreach (KeyValuePair<string, string> ModuleNameToFileNamePair in ModuleNameToFileName.OrderBy(x => x.Key))
				{
					OutputWriter.WriteValue(ModuleNameToFileNamePair.Key, ModuleNameToFileNamePair.Value);
				}
				OutputWriter.WriteObjectEnd();

				OutputWriter.WriteObjectEnd();
			}
		}
	}
}
