// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using System;
using System.Collections.Generic;
using System.IO;
using System.Diagnostics;
using System.Linq;
using System.Xml.Serialization;
using System.ComponentModel;
using System.Runtime.Serialization;

namespace UnrealBuildTool
{
	/// <summary>
	/// Type of a build product
	/// </summary>
	public enum BuildProductType
	{
		/// <summary>
		/// An executable file
		/// </summary>
		Executable,

		/// <summary>
		/// A dynamically loaded module.
		/// </summary>
		DynamicLibrary,

		/// <summary>
		/// A statically linked library. Not required for the executable to run.
		/// </summary>
		StaticLibrary,

		/// <summary>
		/// An import library. Not required for the executable to run.
		/// </summary>
		ImportLibrary,

		/// <summary>
		/// A symbol file. Not required for the executable to run.
		/// </summary>
		SymbolFile,

		/// <summary>
		/// A map file. Not required for the executable to run.
		/// </summary>
		MapFile,

		/// <summary>
		/// A resource file which was generated by the build and is required for the executable to run.
		/// </summary>
		RequiredResource,
	}

	/// <summary>
	/// A file that was created as part of the build process
	/// </summary>
	[Serializable]
	public class BuildProduct
	{
		/// <summary>
		/// Path to the file.
		/// </summary>
		public string Path;

		/// <summary>
		/// Type of the build product.
		/// </summary>
		public BuildProductType Type;

		/// <summary>
		/// Whether the file is precompiled for use by downstream builds, but not directly used by the current target.
		/// </summary>
		public bool IsPrecompiled;

		/// <summary>
		/// Private constructor, for serialization.
		/// </summary>
		private BuildProduct()
		{
		}

		/// <summary>
		/// Constructor.
		/// </summary>
		/// <param name="InPath">Path to the build product</param>
		/// <param name="InType">Type of the build product</param>
		public BuildProduct(string InPath, BuildProductType InType)
		{
			Path = InPath;
			Type = InType;
		}

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="Other">Build product to copy settings from</param>
		public BuildProduct(BuildProduct Other)
		{
			Path = Other.Path;
			Type = Other.Type;
			IsPrecompiled = Other.IsPrecompiled;
		}

		/// <summary>
		/// Convert this object to a string, for debugging.
		/// </summary>
		/// <returns>Path to this build product</returns>
		public override string ToString()
		{
			return Path;
		}
	}

	/// <summary>
	/// How a file may be staged
	/// </summary>
	public enum StagedFileType
	{
		/// <summary>
		/// Only accessed through Unreal filesystem functions; may be included in a PAK file.
		/// </summary>
		UFS,

		/// <summary>
		/// Must be kept as part of the loose filesystem.
		/// </summary>
		NonUFS,

		/// <summary>
		/// Debug file which must be kept as part of the loose filesystem.
		/// </summary>
		DebugNonUFS
	}

	/// <summary>
	/// Information about a file which is required by the target at runtime, and must be moved around with it.
	/// </summary>
	[Serializable]
	public class RuntimeDependency
	{
		/// <summary>
		/// The file that should be staged. Should use $(EngineDir) and $(ProjectDir) variables as a root, so that the target can be relocated to different machines.
		/// </summary>
		public string Path;

		/// <summary>
		/// How to stage this file.
		/// </summary>
		public StagedFileType Type;

		/// <summary>
		/// Private constructor, for serialization.
		/// </summary>
		private RuntimeDependency()
		{
		}

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="InPath">Path to the runtime dependency</param>
		/// <param name="InType">How to stage the given path</param>
		public RuntimeDependency(string InPath, StagedFileType InType = StagedFileType.NonUFS)
		{
			Path = InPath;
			Type = InType;
		}

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="InOther">Runtime dependency to copy settings from</param>
		public RuntimeDependency(RuntimeDependency InOther)
		{
			Path = InOther.Path;
			Type = InOther.Type;
		}

		/// <summary>
		/// Convert this object to a string for debugging
		/// </summary>
		/// <returns>String representation of the object</returns>
		public override string ToString()
		{
			return Path;
		}
	}

	/// <summary>
	/// List of runtime dependencies, with convenience methods for adding new items
	/// </summary>
	[Serializable]
	public class RuntimeDependencyList : List<RuntimeDependency>
	{
		/// <summary>
		/// Default constructor
		/// </summary>
		public RuntimeDependencyList()
		{
		}

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="Other">Sequence of runtime dependencies to initialize with</param>
		public RuntimeDependencyList(IEnumerable<RuntimeDependency> Other) : base(Other)
		{
		}

		/// <summary>
		/// Add a runtime dependency to the list
		/// </summary>
		/// <param name="InPath">Path to the runtime dependency. May include wildcards.</param>
		/// <param name="InType">How to stage this file</param>
		public void Add(string InPath, StagedFileType InType)
		{
			Add(new RuntimeDependency(InPath, InType));
		}
	}

	/// <summary>
	/// Arbitrary property name/value which metadata from the build scripts can be passed on to downstream tasks
	/// </summary>
	[Serializable]
	public class ReceiptProperty
	{
		/// <summary>
		/// Property name
		/// </summary>
		[XmlAttribute]
		public string Name;

		/// <summary>
		/// Value of the property
		/// </summary>
		[XmlAttribute]
		public string Value;

		/// <summary>
		/// Construct a property with the given name and value
		/// </summary>
		/// <param name="InName">Name of the property</param>
		/// <param name="InValue">Value of the property</param>
		public ReceiptProperty(string InName, string InValue)
		{
			Name = InName;
			Value = InValue;
		}
	}

	/// <summary>
	/// Stores a record of a built target, with all metadata that other tools may need to know about the build.
	/// </summary>
	[Serializable]
	public class TargetReceipt
	{
		/// <summary>
		/// The name of this target
		/// </summary>
		public string TargetName;

		/// <summary>
		/// Which platform the target is compiled for
		/// </summary>
		public UnrealTargetPlatform Platform;

		/// <summary>
		/// Which configuration this target is compiled in
		/// </summary>
		public UnrealTargetConfiguration Configuration;

		/// <summary>
		/// The unique ID for this build.
		/// </summary>
		public string BuildId;

		/// <summary>
		/// The changelist that this target was compiled with.
		/// </summary>
		public BuildVersion Version;

		/// <summary>
		/// The build products which are part of this target
		/// </summary>
		public List<BuildProduct> BuildProducts = new List<BuildProduct>();

		/// <summary>
		/// All the runtime dependencies that this target relies on
		/// </summary>
		public RuntimeDependencyList RuntimeDependencies = new RuntimeDependencyList();

		/// <summary>
		/// All the files which are required to use precompiled binaries with this target
		/// </summary>
		public HashSet<string> PrecompiledBuildDependencies = new HashSet<string>(StringComparer.InvariantCultureIgnoreCase);

		/// <summary>
		/// All the files which are required runtime dependencies for precompiled binaries that are part of this target
		/// </summary>
		public HashSet<string> PrecompiledRuntimeDependencies = new HashSet<string>(StringComparer.InvariantCultureIgnoreCase);

		/// <summary>
		/// Additional build properties passed through from the module rules
		/// </summary>
		public List<ReceiptProperty> AdditionalProperties = new List<ReceiptProperty>();

		/// <summary>
		/// Default constructor
		/// </summary>
		public TargetReceipt()
		{
		}

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="InTargetName">The name of the target being compiled</param>
		/// <param name="InPlatform">Platform for the target being compiled</param>
		/// <param name="InConfiguration">Configuration of the target being compiled</param>
		public TargetReceipt(string InTargetName, UnrealTargetPlatform InPlatform, UnrealTargetConfiguration InConfiguration, string InBuildId, BuildVersion InVersion)
		{
			TargetName = InTargetName;
			Platform = InPlatform;
			Configuration = InConfiguration;
			BuildId = InBuildId;
			Version = InVersion;
		}

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="InOther">Receipt to copy from</param>
		public TargetReceipt(TargetReceipt Other)
		{
			foreach (BuildProduct OtherBuildProduct in Other.BuildProducts)
			{
				BuildProducts.Add(new BuildProduct(OtherBuildProduct));
			}
			foreach (RuntimeDependency OtherRuntimeDependency in Other.RuntimeDependencies)
			{
				RuntimeDependencies.Add(new RuntimeDependency(OtherRuntimeDependency));
			}
			AdditionalProperties.AddRange(Other.AdditionalProperties);
			PrecompiledBuildDependencies.UnionWith(Other.PrecompiledBuildDependencies);
			PrecompiledRuntimeDependencies.UnionWith(Other.PrecompiledRuntimeDependencies);
		}

		/// <summary>
		/// Adds a build product to the receipt. Does not check whether it already exists.
		/// </summary>
		/// <param name="Path">Path to the build product.</param>
		/// <param name="Type">Type of build product.</param>
		/// <returns>The BuildProduct object that was created</returns>
		public BuildProduct AddBuildProduct(string Path, BuildProductType Type)
		{
			BuildProduct NewBuildProduct = new BuildProduct(Path, Type);
			BuildProducts.Add(NewBuildProduct);
			return NewBuildProduct;
		}

		/// <summary>
		/// Merges another receipt to this one.
		/// </summary>
		/// <param name="Other">Receipt which should be merged</param>
		public void Merge(TargetReceipt Other)
		{
			foreach (BuildProduct OtherBuildProduct in Other.BuildProducts)
			{
				BuildProducts.Add(OtherBuildProduct);
			}
			foreach (RuntimeDependency OtherRuntimeDependency in Other.RuntimeDependencies)
			{
				if (!RuntimeDependencies.Any(x => x.Path == OtherRuntimeDependency.Path))
				{
					RuntimeDependencies.Add(OtherRuntimeDependency);
				}
			}
			PrecompiledBuildDependencies.UnionWith(Other.PrecompiledBuildDependencies);
			PrecompiledRuntimeDependencies.UnionWith(Other.PrecompiledRuntimeDependencies);
		}

		/// <summary>
		/// Expand all the path variables in the manifest
		/// </summary>
		/// <param name="EngineDir">Value for the $(EngineDir) variable</param>
		/// <param name="ProjectDir">Value for the $(ProjectDir) variable</param>
		public void ExpandPathVariables(DirectoryReference EngineDir, DirectoryReference ProjectDir)
		{
			ExpandPathVariables(EngineDir, ProjectDir, new Dictionary<string, string>());
		}

		/// <summary>
		/// Expand all the path variables in the manifest, including a list of supplied variable values.
		/// </summary>
		/// <param name="EngineDir">Value for the $(EngineDir) variable</param>
		/// <param name="ProjectDir">Value for the $(ProjectDir) variable</param>
		public void ExpandPathVariables(DirectoryReference EngineDir, DirectoryReference ProjectDir, IDictionary<string, string> OtherVariables)
		{
			// Build a dictionary containing the standard variable expansions
			Dictionary<string, string> Variables = new Dictionary<string, string>(OtherVariables);
			Variables["EngineDir"] = EngineDir.FullName;
			Variables["ProjectDir"] = ProjectDir.FullName;

			// Replace all the variables in the paths
			foreach (BuildProduct BuildProduct in BuildProducts)
			{
				BuildProduct.Path = Utils.ExpandVariables(BuildProduct.Path, Variables);
			}
			foreach (RuntimeDependency RuntimeDependency in RuntimeDependencies)
			{
				RuntimeDependency.Path = Utils.ExpandVariables(RuntimeDependency.Path, Variables);
			}

			// Replace the variables in the precompiled dependencies
			PrecompiledBuildDependencies = new HashSet<string>(PrecompiledBuildDependencies.Select(x => Utils.ExpandVariables(x, Variables)), StringComparer.InvariantCultureIgnoreCase);
			PrecompiledRuntimeDependencies = new HashSet<string>(PrecompiledRuntimeDependencies.Select(x => Utils.ExpandVariables(x, Variables)), StringComparer.InvariantCultureIgnoreCase);
		}

		/// <summary>
		/// Inserts $(EngineDir) and $(ProjectDir) variables into a path string, so it can be used on different machines.
		/// </summary>
		/// <param name="InputPath">Input path</param>
		/// <param name="EngineDir">The engine directory. Relative paths are ok.</param>
		/// <param name="ProjectDir">The project directory. Relative paths are ok.</param>
		/// <returns>New string with the base directory replaced, or the original string</returns>
		public static string InsertPathVariables(string InputPath, DirectoryReference EngineDir, DirectoryReference ProjectDir)
		{
			string Result = InputPath;
			if (InputPath != null && !InputPath.StartsWith("$("))
			{
				Result = InsertPathVariables(new FileReference(InputPath), EngineDir, ProjectDir);
			}
			return Result;
		}

		/// <summary>
		/// Inserts variables to make a file relative to $(EngineDir) or $(ProjectDir)
		/// </summary>
		/// <param name="File">The file to insert variables into.</param>
		/// <param name="EngineDir">Value of the $(EngineDir) variable.</param>
		/// <param name="ProjectDir">Value of the $(ProjectDir) variable.</param>
		/// <returns>Converted path for the file.</returns>
		public static string InsertPathVariables(FileReference File, DirectoryReference EngineDir, DirectoryReference ProjectDir)
		{
			if (File.IsUnderDirectory(EngineDir))
			{
				return "$(EngineDir)/" + File.MakeRelativeTo(EngineDir).Replace(Path.DirectorySeparatorChar, '/');
			}
			else if (File.IsUnderDirectory(ProjectDir))
			{
				return "$(ProjectDir)/" + File.MakeRelativeTo(ProjectDir).Replace(Path.DirectorySeparatorChar, '/');
			}
			else
			{
				return File.FullName;
			}
		}

		/// <summary>
		/// Returns the standard path to the build receipt for a given target
		/// </summary>
		/// <param name="DirectoryName">Base directory for the target being built; either the project directory or engine directory.</param>
		/// <param name="TargetName">The target being built</param>
		/// <param name="Configuration">The target configuration</param>
		/// <param name="Platform">The target platform</param>
		/// <returns>Path to the receipt for this target</returns>
		public static string GetDefaultPath(string BaseDir, string TargetName, UnrealTargetPlatform Platform, UnrealTargetConfiguration Configuration, string BuildArchitecture)
		{
			// Get the architecture suffix. Platforms have the option of overriding whether to include this string in filenames.
			string ArchitectureSuffix = "";
			if(UEBuildPlatform.GetBuildPlatform(Platform).RequiresArchitectureSuffix())
			{
				ArchitectureSuffix = BuildArchitecture;
			}
		
			// Build the output filename
			if (String.IsNullOrEmpty(ArchitectureSuffix) && Configuration == UnrealTargetConfiguration.Development)
			{
				return Path.Combine(BaseDir, "Binaries", Platform.ToString(), String.Format("{0}.target", TargetName));
			}
			else
			{
				return Path.Combine(BaseDir, "Binaries", Platform.ToString(), String.Format("{0}-{1}-{2}{3}.target", TargetName, Platform.ToString(), Configuration.ToString(), ArchitectureSuffix));
			}
		}

		/// <summary>
		/// Read a receipt from disk.
		/// </summary>
		/// <param name="FileName">Filename to read from</param>
		public static TargetReceipt Read(string FileName)
		{
			JsonObject RawObject = JsonObject.Read(FileName);

			// Read the initial fields
			string TargetName = RawObject.GetStringField("TargetName");
			UnrealTargetPlatform Platform = RawObject.GetEnumField<UnrealTargetPlatform>("Platform");
			UnrealTargetConfiguration Configuration = RawObject.GetEnumField<UnrealTargetConfiguration>("Configuration");
			string BuildId = RawObject.GetStringField("BuildId");

			// Try to read the build version
			BuildVersion Version;
			if (!BuildVersion.TryParse(RawObject.GetObjectField("Version"), out Version))
			{
				throw new JsonParseException("Invalid 'Version' field");
			}

			// Create the receipt
			TargetReceipt Receipt = new TargetReceipt(TargetName, Platform, Configuration, BuildId, Version);

			// Read the build products
			JsonObject[] BuildProductObjects;
			if (RawObject.TryGetObjectArrayField("BuildProducts", out BuildProductObjects))
			{
				foreach (JsonObject BuildProductObject in BuildProductObjects)
				{
					string Path;
					BuildProductType Type;
					if (BuildProductObject.TryGetStringField("Path", out Path) && BuildProductObject.TryGetEnumField("Type", out Type))
					{
						string Module;
						BuildProductObject.TryGetStringField("Module", out Module);

						BuildProduct NewBuildProduct = Receipt.AddBuildProduct(Path, Type);

						bool IsPrecompiled;
						if (BuildProductObject.TryGetBoolField("IsPrecompiled", out IsPrecompiled))
						{
							NewBuildProduct.IsPrecompiled = IsPrecompiled;
						}
					}
				}
			}

			// Read the runtime dependencies
			JsonObject[] RuntimeDependencyObjects;
			if (RawObject.TryGetObjectArrayField("RuntimeDependencies", out RuntimeDependencyObjects))
			{
				foreach (JsonObject RuntimeDependencyObject in RuntimeDependencyObjects)
				{
					string Path;
					if (RuntimeDependencyObject.TryGetStringField("Path", out Path))
					{
						StagedFileType Type;
						if(!RuntimeDependencyObject.TryGetEnumField("Type", out Type))
						{
							// Previous format included an optional IgnoreIfMissing flag, which was only used for debug files. We can explicitly reference them as DebugNonUFS files now.
							bool bIgnoreIfMissing;
							if(RuntimeDependencyObject.TryGetBoolField("IgnoreIfMissing", out bIgnoreIfMissing))
							{
								bIgnoreIfMissing = false;
							}
							Type = bIgnoreIfMissing? StagedFileType.DebugNonUFS : StagedFileType.NonUFS;
						}
						Receipt.RuntimeDependencies.Add(Path, Type);
					}
				}
			}

			// Read the additional properties
			JsonObject[] AdditionalPropertyObjects;
			if(RawObject.TryGetObjectArrayField("AdditionalProperties", out AdditionalPropertyObjects))
			{
				foreach(JsonObject AdditionalPropertyObject in AdditionalPropertyObjects)
				{
					string Name;
					if(AdditionalPropertyObject.TryGetStringField("Name", out Name))
					{
						string Value;
						if(AdditionalPropertyObject.TryGetStringField("Value", out Value))
						{
							Receipt.AdditionalProperties.Add(new ReceiptProperty(Name, Value));
						}
					}
				}
			}

			// Read the precompiled dependencies
			string[] PrecompiledBuildDependencies;
			if(RawObject.TryGetStringArrayField("PrecompiledBuildDependencies", out PrecompiledBuildDependencies))
			{
				Receipt.PrecompiledBuildDependencies.UnionWith(PrecompiledBuildDependencies);
			}

			// Read the precompiled dependencies
			string[] PrecompiledRuntimeDependencies;
			if(RawObject.TryGetStringArrayField("PrecompiledRuntimeDependencies", out PrecompiledRuntimeDependencies))
			{
				Receipt.PrecompiledRuntimeDependencies.UnionWith(PrecompiledRuntimeDependencies);
			}

			return Receipt;
		}

		/// <summary>
		/// Try to read a receipt from disk, failing gracefully if it can't be read.
		/// </summary>
		/// <param name="FileName">Filename to read from</param>
		public static bool TryRead(string FileName, out TargetReceipt Receipt)
		{
			if (!File.Exists(FileName))
			{
				Receipt = null;
				return false;
			}

			try
			{
				Receipt = Read(FileName);
				return true;
			}
			catch (Exception)
			{
				Receipt = null;
				return false;
			}
		}

		/// <summary>
		/// Write the receipt to disk.
		/// </summary>
		/// <param name="FileName">Output filename</param>
		public void Write(string FileName)
		{
			using (JsonWriter Writer = new JsonWriter(FileName))
			{
				Writer.WriteObjectStart();
				Writer.WriteValue("TargetName", TargetName);
				Writer.WriteValue("Platform", Platform.ToString());
				Writer.WriteValue("Configuration", Configuration.ToString());
				Writer.WriteValue("BuildId", BuildId);

				Writer.WriteObjectStart("Version");
				Version.WriteProperties(Writer);
				Writer.WriteObjectEnd();

				Writer.WriteArrayStart("BuildProducts");
				foreach (BuildProduct BuildProduct in BuildProducts)
				{
					Writer.WriteObjectStart();
					Writer.WriteValue("Path", BuildProduct.Path);
					Writer.WriteValue("Type", BuildProduct.Type.ToString());
					if (BuildProduct.IsPrecompiled)
					{
						Writer.WriteValue("IsPrecompiled", BuildProduct.IsPrecompiled);
					}
					Writer.WriteObjectEnd();
				}
				Writer.WriteArrayEnd();

				Writer.WriteArrayStart("RuntimeDependencies");
				foreach (RuntimeDependency RuntimeDependency in RuntimeDependencies)
				{
					Writer.WriteObjectStart();
					Writer.WriteValue("Path", RuntimeDependency.Path);
					Writer.WriteValue("Type", RuntimeDependency.Type.ToString());
					Writer.WriteObjectEnd();
				}
				Writer.WriteArrayEnd();

				if(AdditionalProperties.Count > 0)
				{
					Writer.WriteArrayStart("AdditionalProperties");
					foreach (ReceiptProperty AdditionalProperty in AdditionalProperties)
					{
						Writer.WriteObjectStart();
						Writer.WriteValue("Name", AdditionalProperty.Name);
						Writer.WriteValue("Value", AdditionalProperty.Value);
						Writer.WriteObjectEnd();
					}
					Writer.WriteArrayEnd();
				}

				if(PrecompiledBuildDependencies.Count > 0)
				{
					Writer.WriteArrayStart("PrecompiledBuildDependencies");
					foreach(string PrecompiledBuildDependency in PrecompiledBuildDependencies.OrderBy(x => x))
					{
						Writer.WriteValue(PrecompiledBuildDependency);
					}
					Writer.WriteArrayEnd();
				}

				if(PrecompiledRuntimeDependencies.Count > 0)
				{
					Writer.WriteArrayStart("PrecompiledRuntimeDependencies");
					foreach(string PrecompiledRuntimeDependency in PrecompiledRuntimeDependencies.OrderBy(x => x))
					{
						Writer.WriteValue(PrecompiledRuntimeDependency);
					}
					Writer.WriteArrayEnd();
				}

				Writer.WriteObjectEnd();
			}
		}
	}
}
