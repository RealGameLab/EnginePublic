#pragma once

#include <string>
#include <stdexcept>

using namespace std;

namespace Simplygon {
	namespace SPL {
		namespace v80 {

			enum FillMode
			{
				SG_ATLASFILLMODE_INTERPOLATE = 0x0,
				SG_ATLASFILLMODE_NEARESTNEIGHBOR = 0x1,
				SG_ATLASFILLMODE_NONE = 0x2
			};

			class  FillModeUtil
			{
			public:
				static FillMode Parse(string enumString, FillMode defaultValue)
				{
					if (enumString == "SG_ATLASFILLMODE_INTERPOLATE")
					{
						return SG_ATLASFILLMODE_INTERPOLATE;
					}
					else if (enumString == "SG_ATLASFILLMODE_NEARESTNEIGHBOR")
					{
						return SG_ATLASFILLMODE_NEARESTNEIGHBOR;
					}
					else if (enumString == "SG_ATLASFILLMODE_NONE")
					{
						return SG_ATLASFILLMODE_NONE;
					}
					return defaultValue;
				}

				static FillMode Parse(string enumString)
				{
					if (enumString == "SG_ATLASFILLMODE_INTERPOLATE")
					{
						return SG_ATLASFILLMODE_INTERPOLATE;
					}
					else if (enumString == "SG_ATLASFILLMODE_NEARESTNEIGHBOR")
					{
						return SG_ATLASFILLMODE_NEARESTNEIGHBOR;
					}
					else if (enumString == "SG_ATLASFILLMODE_NONE")
					{
						return SG_ATLASFILLMODE_NONE;
					}
					throw invalid_argument("Invalid AtlasFillMode: " + enumString);
				}

				static string ToString(FillMode e)
				{
					if (e == SG_ATLASFILLMODE_INTERPOLATE)
					{
						return "SG_ATLASFILLMODE_INTERPOLATE";
					}
					else if (e == SG_ATLASFILLMODE_NEARESTNEIGHBOR)
					{
						return "SG_ATLASFILLMODE_NEARESTNEIGHBOR";
					}
					else if (e == SG_ATLASFILLMODE_NONE)
					{
						return "SG_ATLASFILLMODE_NONE";
					}
					return "SG_ATLASFILLMODE_INTERPOLATE";
				}
			};

			enum BoneReductionTargets
			{
				SG_BONEREDUCTIONTARGET_BONECOUNT = 0x1,
				SG_BONEREDUCTIONTARGET_BONERATIO = 0x2,
				SG_BONEREDUCTIONTARGET_MAXDEVIATION = 0x4,
				SG_BONEREDUCTIONTARGET_ONSCREENSIZE = 0x8,
				SG_BONEREDUCTIONTARGET_ALL = 0xffffffff
			};

			class  BoneReductionTargetsUtil
			{
			public:
				static BoneReductionTargets Parse(string enumString, BoneReductionTargets defaultValue)
				{
					if (enumString == "SG_BONEREDUCTIONTARGET_BONECOUNT")
					{
						return SG_BONEREDUCTIONTARGET_BONECOUNT;
					}
					else if (enumString == "SG_BONEREDUCTIONTARGET_BONERATIO")
					{
						return SG_BONEREDUCTIONTARGET_BONERATIO;
					}
					else if (enumString == "SG_BONEREDUCTIONTARGET_MAXDEVIATION")
					{
						return SG_BONEREDUCTIONTARGET_MAXDEVIATION;
					}
					else if (enumString == "SG_BONEREDUCTIONTARGET_ONSCREENSIZE")
					{
						return SG_BONEREDUCTIONTARGET_ONSCREENSIZE;
					}
					else if (enumString == "SG_BONEREDUCTIONTARGET_ALL")
					{
						return SG_BONEREDUCTIONTARGET_ALL;
					}
					return defaultValue;
				}

				static BoneReductionTargets Parse(string enumString)
				{
					if (enumString == "SG_BONEREDUCTIONTARGET_BONECOUNT")
					{
						return SG_BONEREDUCTIONTARGET_BONECOUNT;
					}
					else if (enumString == "SG_BONEREDUCTIONTARGET_BONERATIO")
					{
						return SG_BONEREDUCTIONTARGET_BONERATIO;
					}
					else if (enumString == "SG_BONEREDUCTIONTARGET_MAXDEVIATION")
					{
						return SG_BONEREDUCTIONTARGET_MAXDEVIATION;
					}
					else if (enumString == "SG_BONEREDUCTIONTARGET_ONSCREENSIZE")
					{
						return SG_BONEREDUCTIONTARGET_ONSCREENSIZE;
					}
					else if (enumString == "SG_BONEREDUCTIONTARGET_ALL")
					{
						return SG_BONEREDUCTIONTARGET_ALL;
					}
					throw invalid_argument("Invalid BoneReductionTargets: " + enumString);
				}

				static string ToString(BoneReductionTargets e)
				{
					if (e == SG_BONEREDUCTIONTARGET_BONECOUNT)
					{
						return "SG_BONEREDUCTIONTARGET_BONECOUNT";
					}
					else if (e == SG_BONEREDUCTIONTARGET_BONERATIO)
					{
						return "SG_BONEREDUCTIONTARGET_BONERATIO";
					}
					else if (e == SG_BONEREDUCTIONTARGET_MAXDEVIATION)
					{
						return "SG_BONEREDUCTIONTARGET_MAXDEVIATION";
					}
					else if (e == SG_BONEREDUCTIONTARGET_ONSCREENSIZE)
					{
						return "SG_BONEREDUCTIONTARGET_ONSCREENSIZE";
					}
					else if (e == SG_BONEREDUCTIONTARGET_ALL)
					{
						return "SG_BONEREDUCTIONTARGET_ALL";
					}
					return "SG_BONEREDUCTIONTARGET_BONECOUNT";
				}
			};

			enum CasterOutputChannels
			{
				Luminance = 1,
				RGB = 3,
				RGBA = 4
			};

			class  CasterOutputChannelsUtil
			{
			public:
				static CasterOutputChannels Parse(string enumString, CasterOutputChannels defaultValue)
				{
					if (enumString == "Luminance")
					{
						return Luminance;
					}
					else if (enumString == "RGB")
					{
						return RGB;
					}
					else if (enumString == "RGBA")
					{
						return RGBA;
					}
					return defaultValue;
				}

				static CasterOutputChannels Parse(string enumString)
				{
					if (enumString == "Luminance")
					{
						return Luminance;
					}
					else if (enumString == "RGB")
					{
						return RGB;
					}
					else if (enumString == "RGBA")
					{
						return RGBA;
					}
					throw invalid_argument("Invalid CasterOutputChannels: " + enumString);
				}

				static string ToString(CasterOutputChannels e)
				{
					if (e == Luminance)
					{
						return "Luminance";
					}
					else if (e == RGB)
					{
						return "RGB";
					}
					else if (e == RGBA)
					{
						return "RGBA";
					}
					return "Luminance";
				}
			};

			enum ChartAggregatorMode
			{
				SG_CHARTAGGREGATORMODE_TEXTURESIZEPROPORTIONS = 0x0,
				SG_CHARTAGGREGATORMODE_SURFACEAREA = 0x1,
				SG_CHARTAGGREGATORMODE_ORIGINALPIXELDENSITY = 0x2,
				SG_CHARTAGGREGATORMODE_UVSIZEPROPORTIONS = 0x3
			};

			class  ChartAggregatorModeUtil
			{
			public:
				static ChartAggregatorMode Parse(string enumString, ChartAggregatorMode defaultValue)
				{
					if (enumString == "SG_CHARTAGGREGATORMODE_TEXTURESIZEPROPORTIONS")
					{
						return SG_CHARTAGGREGATORMODE_TEXTURESIZEPROPORTIONS;
					}
					else if (enumString == "SG_CHARTAGGREGATORMODE_SURFACEAREA")
					{
						return SG_CHARTAGGREGATORMODE_SURFACEAREA;
					}
					else if (enumString == "SG_CHARTAGGREGATORMODE_ORIGINALPIXELDENSITY")
					{
						return SG_CHARTAGGREGATORMODE_ORIGINALPIXELDENSITY;
					}
					else if (enumString == "SG_CHARTAGGREGATORMODE_UVSIZEPROPORTIONS")
					{
						return SG_CHARTAGGREGATORMODE_UVSIZEPROPORTIONS;
					}
					return defaultValue;
				}

				static ChartAggregatorMode Parse(string enumString)
				{
					if (enumString == "SG_CHARTAGGREGATORMODE_TEXTURESIZEPROPORTIONS")
					{
						return SG_CHARTAGGREGATORMODE_TEXTURESIZEPROPORTIONS;
					}
					else if (enumString == "SG_CHARTAGGREGATORMODE_SURFACEAREA")
					{
						return SG_CHARTAGGREGATORMODE_SURFACEAREA;
					}
					else if (enumString == "SG_CHARTAGGREGATORMODE_ORIGINALPIXELDENSITY")
					{
						return SG_CHARTAGGREGATORMODE_ORIGINALPIXELDENSITY;
					}
					else if (enumString == "SG_CHARTAGGREGATORMODE_UVSIZEPROPORTIONS")
					{
						return SG_CHARTAGGREGATORMODE_UVSIZEPROPORTIONS;
					}
					throw invalid_argument("Invalid ChartAggregatorMode: " + enumString);
				}

				static string ToString(ChartAggregatorMode e)
				{
					if (e == SG_CHARTAGGREGATORMODE_TEXTURESIZEPROPORTIONS)
					{
						return "SG_CHARTAGGREGATORMODE_TEXTURESIZEPROPORTIONS";
					}
					else if (e == SG_CHARTAGGREGATORMODE_SURFACEAREA)
					{
						return "SG_CHARTAGGREGATORMODE_SURFACEAREA";
					}
					else if (e == SG_CHARTAGGREGATORMODE_ORIGINALPIXELDENSITY)
					{
						return "SG_CHARTAGGREGATORMODE_ORIGINALPIXELDENSITY";
					}
					else if (e == SG_CHARTAGGREGATORMODE_UVSIZEPROPORTIONS)
					{
						return "SG_CHARTAGGREGATORMODE_UVSIZEPROPORTIONS";
					}
					return "SG_CHARTAGGREGATORMODE_TEXTURESIZEPROPORTIONS";
				}
			};

			enum DataCreationPreferences
			{
				SG_DATACREATIONPREFERENCES_ONLY_USE_ORIGINAL_DATA = 0x0,
				SG_DATACREATIONPREFERENCES_PREFER_ORIGINAL_DATA = 0x1,
				SG_DATACREATIONPREFERENCES_PREFER_OPTIMIZED_RESULT = 0x2
			};

			class  DataCreationPreferencesUtil
			{
			public:
				static DataCreationPreferences Parse(string enumString, DataCreationPreferences defaultValue)
				{
					if (enumString == "SG_DATACREATIONPREFERENCES_ONLY_USE_ORIGINAL_DATA")
					{
						return SG_DATACREATIONPREFERENCES_ONLY_USE_ORIGINAL_DATA;
					}
					else if (enumString == "SG_DATACREATIONPREFERENCES_PREFER_ORIGINAL_DATA")
					{
						return SG_DATACREATIONPREFERENCES_PREFER_ORIGINAL_DATA;
					}
					else if (enumString == "SG_DATACREATIONPREFERENCES_PREFER_OPTIMIZED_RESULT")
					{
						return SG_DATACREATIONPREFERENCES_PREFER_OPTIMIZED_RESULT;
					}
					return defaultValue;
				}

				static DataCreationPreferences Parse(string enumString)
				{
					if (enumString == "SG_DATACREATIONPREFERENCES_ONLY_USE_ORIGINAL_DATA")
					{
						return SG_DATACREATIONPREFERENCES_ONLY_USE_ORIGINAL_DATA;
					}
					else if (enumString == "SG_DATACREATIONPREFERENCES_PREFER_ORIGINAL_DATA")
					{
						return SG_DATACREATIONPREFERENCES_PREFER_ORIGINAL_DATA;
					}
					else if (enumString == "SG_DATACREATIONPREFERENCES_PREFER_OPTIMIZED_RESULT")
					{
						return SG_DATACREATIONPREFERENCES_PREFER_OPTIMIZED_RESULT;
					}
					throw invalid_argument("Invalid DataCreationPreferences: " + enumString);
				}

				static string ToString(DataCreationPreferences e)
				{
					if (e == SG_DATACREATIONPREFERENCES_ONLY_USE_ORIGINAL_DATA)
					{
						return "SG_DATACREATIONPREFERENCES_ONLY_USE_ORIGINAL_DATA";
					}
					else if (e == SG_DATACREATIONPREFERENCES_PREFER_ORIGINAL_DATA)
					{
						return "SG_DATACREATIONPREFERENCES_PREFER_ORIGINAL_DATA";
					}
					else if (e == SG_DATACREATIONPREFERENCES_PREFER_OPTIMIZED_RESULT)
					{
						return "SG_DATACREATIONPREFERENCES_PREFER_OPTIMIZED_RESULT";
					}
					return "SG_DATACREATIONPREFERENCES_ONLY_USE_ORIGINAL_DATA";
				}
			};

			enum DitherType
			{
				SG_DITHERPATTERNS_NO_DITHER = 0x0,
				SG_DITHERPATTERNS_FLOYDSTEINBERG = 0x1,
				SG_DITHERPATTERNS_JARVISJUDICENINKE = 0x2,
				SG_DITHERPATTERNS_SIERRA = 0x3
			};

			class  DitherTypeUtil
			{
			public:
				static DitherType Parse(string enumString, DitherType defaultValue)
				{
					if (enumString == "SG_DITHERPATTERNS_NO_DITHER")
					{
						return SG_DITHERPATTERNS_NO_DITHER;
					}
					else if (enumString == "SG_DITHERPATTERNS_FLOYDSTEINBERG")
					{
						return SG_DITHERPATTERNS_FLOYDSTEINBERG;
					}
					else if (enumString == "SG_DITHERPATTERNS_JARVISJUDICENINKE")
					{
						return SG_DITHERPATTERNS_JARVISJUDICENINKE;
					}
					else if (enumString == "SG_DITHERPATTERNS_SIERRA")
					{
						return SG_DITHERPATTERNS_SIERRA;
					}
					return defaultValue;
				}

				static DitherType Parse(string enumString)
				{
					if (enumString == "SG_DITHERPATTERNS_NO_DITHER")
					{
						return SG_DITHERPATTERNS_NO_DITHER;
					}
					else if (enumString == "SG_DITHERPATTERNS_FLOYDSTEINBERG")
					{
						return SG_DITHERPATTERNS_FLOYDSTEINBERG;
					}
					else if (enumString == "SG_DITHERPATTERNS_JARVISJUDICENINKE")
					{
						return SG_DITHERPATTERNS_JARVISJUDICENINKE;
					}
					else if (enumString == "SG_DITHERPATTERNS_SIERRA")
					{
						return SG_DITHERPATTERNS_SIERRA;
					}
					throw invalid_argument("Invalid DitherPatterns: " + enumString);
				}

				static string ToString(DitherType e)
				{
					if (e == SG_DITHERPATTERNS_NO_DITHER)
					{
						return "SG_DITHERPATTERNS_NO_DITHER";
					}
					else if (e == SG_DITHERPATTERNS_FLOYDSTEINBERG)
					{
						return "SG_DITHERPATTERNS_FLOYDSTEINBERG";
					}
					else if (e == SG_DITHERPATTERNS_JARVISJUDICENINKE)
					{
						return "SG_DITHERPATTERNS_JARVISJUDICENINKE";
					}
					else if (e == SG_DITHERPATTERNS_SIERRA)
					{
						return "SG_DITHERPATTERNS_SIERRA";
					}
					return "SG_DITHERPATTERNS_NO_DITHER";
				}
			};

			enum ReductionHeuristics
			{
				SG_REDUCTIONHEURISTICS_FAST = 0x0,
				SG_REDUCTIONHEURISTICS_CONSISTENT = 0x1
			};

			class  ReductionHeuristicsUtil
			{
			public:
				static ReductionHeuristics Parse(string enumString, ReductionHeuristics defaultValue)
				{
					if (enumString == "SG_REDUCTIONHEURISTICS_FAST")
					{
						return SG_REDUCTIONHEURISTICS_FAST;
					}
					else if (enumString == "SG_REDUCTIONHEURISTICS_CONSISTENT")
					{
						return SG_REDUCTIONHEURISTICS_CONSISTENT;
					}
					return defaultValue;
				}

				static ReductionHeuristics Parse(string enumString)
				{
					if (enumString == "SG_REDUCTIONHEURISTICS_FAST")
					{
						return SG_REDUCTIONHEURISTICS_FAST;
					}
					else if (enumString == "SG_REDUCTIONHEURISTICS_CONSISTENT")
					{
						return SG_REDUCTIONHEURISTICS_CONSISTENT;
					}
					throw invalid_argument("Invalid ReductionHeuristics: " + enumString);
				}

				static string ToString(ReductionHeuristics e)
				{
					if (e == SG_REDUCTIONHEURISTICS_FAST)
					{
						return "SG_REDUCTIONHEURISTICS_FAST";
					}
					else if (e == SG_REDUCTIONHEURISTICS_CONSISTENT)
					{
						return "SG_REDUCTIONHEURISTICS_CONSISTENT";
					}
					return "SG_REDUCTIONHEURISTICS_FAST";
				}
			};

			enum ReductionTargets
			{
				SG_REDUCTIONTARGET_TRIANGLECOUNT = 0x1,
				SG_REDUCTIONTARGET_TRIANGLERATIO = 0x2,
				SG_REDUCTIONTARGET_MAXDEVIATION = 0x4,
				SG_REDUCTIONTARGET_ONSCREENSIZE = 0x8,
				SG_REDUCTIONTARGET_ALL = 0xffffffff
			};

			class  ReductionTargetsUtil
			{
			public:
				static ReductionTargets Parse(string enumString, ReductionTargets defaultValue)
				{
					if (enumString == "SG_REDUCTIONTARGET_TRIANGLECOUNT")
					{
						return SG_REDUCTIONTARGET_TRIANGLECOUNT;
					}
					else if (enumString == "SG_REDUCTIONTARGET_TRIANGLERATIO")
					{
						return SG_REDUCTIONTARGET_TRIANGLERATIO;
					}
					else if (enumString == "SG_REDUCTIONTARGET_MAXDEVIATION")
					{
						return SG_REDUCTIONTARGET_MAXDEVIATION;
					}
					else if (enumString == "SG_REDUCTIONTARGET_ONSCREENSIZE")
					{
						return SG_REDUCTIONTARGET_ONSCREENSIZE;
					}
					else if (enumString == "SG_REDUCTIONTARGET_ALL")
					{
						return SG_REDUCTIONTARGET_ALL;
					}
					return defaultValue;
				}

				static ReductionTargets Parse(string enumString)
				{
					if (enumString == "SG_REDUCTIONTARGET_TRIANGLECOUNT")
					{
						return SG_REDUCTIONTARGET_TRIANGLECOUNT;
					}
					else if (enumString == "SG_REDUCTIONTARGET_TRIANGLERATIO")
					{
						return SG_REDUCTIONTARGET_TRIANGLERATIO;
					}
					else if (enumString == "SG_REDUCTIONTARGET_MAXDEVIATION")
					{
						return SG_REDUCTIONTARGET_MAXDEVIATION;
					}
					else if (enumString == "SG_REDUCTIONTARGET_ONSCREENSIZE")
					{
						return SG_REDUCTIONTARGET_ONSCREENSIZE;
					}
					else if (enumString == "SG_REDUCTIONTARGET_ALL")
					{
						return SG_REDUCTIONTARGET_ALL;
					}
					throw invalid_argument("Invalid ReductionTargets: " + enumString);
				}

				static string ToString(ReductionTargets e)
				{
					if (e == SG_REDUCTIONTARGET_TRIANGLECOUNT)
					{
						return "SG_REDUCTIONTARGET_TRIANGLECOUNT";
					}
					else if (e == SG_REDUCTIONTARGET_TRIANGLERATIO)
					{
						return "SG_REDUCTIONTARGET_TRIANGLERATIO";
					}
					else if (e == SG_REDUCTIONTARGET_MAXDEVIATION)
					{
						return "SG_REDUCTIONTARGET_MAXDEVIATION";
					}
					else if (e == SG_REDUCTIONTARGET_ONSCREENSIZE)
					{
						return "SG_REDUCTIONTARGET_ONSCREENSIZE";
					}
					else if (e == SG_REDUCTIONTARGET_ALL)
					{
						return "SG_REDUCTIONTARGET_ALL";
					}
					return "SG_REDUCTIONTARGET_TRIANGLECOUNT";
				}
			};

			enum SurfaceTransferMode
			{
				SG_SURFACETRANSFER_FAST = 0x0,
				SG_SURFACETRANSFER_ACCURATE = 0x1
			};

			class  SurfaceTransferModeUtil
			{
			public:
				static SurfaceTransferMode Parse(string enumString, SurfaceTransferMode defaultValue)
				{
					if (enumString == "SG_SURFACETRANSFER_FAST")
					{
						return SG_SURFACETRANSFER_FAST;
					}
					else if (enumString == "SG_SURFACETRANSFER_ACCURATE")
					{
						return SG_SURFACETRANSFER_ACCURATE;
					}
					return defaultValue;
				}

				static SurfaceTransferMode Parse(string enumString)
				{
					if (enumString == "SG_SURFACETRANSFER_FAST")
					{
						return SG_SURFACETRANSFER_FAST;
					}
					else if (enumString == "SG_SURFACETRANSFER_ACCURATE")
					{
						return SG_SURFACETRANSFER_ACCURATE;
					}
					throw invalid_argument("Invalid SurfaceTransferMode: " + enumString);
				}

				static string ToString(SurfaceTransferMode e)
				{
					if (e == SG_SURFACETRANSFER_FAST)
					{
						return "SG_SURFACETRANSFER_FAST";
					}
					else if (e == SG_SURFACETRANSFER_ACCURATE)
					{
						return "SG_SURFACETRANSFER_ACCURATE";
					}
					return "SG_SURFACETRANSFER_FAST";
				}
			};

			enum StopCondition
			{
				SG_STOPCONDITION_ANY = 0x0,
				SG_STOPCONDITION_ALL = 0x1
			};

			class  StopConditionUtil
			{
			public:
				static StopCondition Parse(string enumString, StopCondition defaultValue)
				{
					if (enumString == "SG_STOPCONDITION_ANY")
					{
						return SG_STOPCONDITION_ANY;
					}
					else if (enumString == "SG_STOPCONDITION_ALL")
					{
						return SG_STOPCONDITION_ALL;
					}
					return defaultValue;
				}

				static StopCondition Parse(string enumString)
				{
					if (enumString == "SG_STOPCONDITION_ANY")
					{
						return SG_STOPCONDITION_ANY;
					}
					else if (enumString == "SG_STOPCONDITION_ALL")
					{
						return SG_STOPCONDITION_ALL;
					}
					throw invalid_argument("Invalid StopCondition: " + enumString);
				}

				static string ToString(StopCondition e)
				{
					if (e == SG_STOPCONDITION_ANY)
					{
						return "SG_STOPCONDITION_ANY";
					}
					else if (e == SG_STOPCONDITION_ALL)
					{
						return "SG_STOPCONDITION_ALL";
					}
					return "SG_STOPCONDITION_ANY";
				}
			};

			enum TangentSpaceMethod
			{
				SG_TANGENTSPACEMETHOD_ORTHONORMAL = 0x0, /// Standard method, creates an orthonormal tangent space (right-handed)
				SG_TANGENTSPACEMETHOD_3DSMAX = 0x1, /// 3dsMax compatible method, creates tangent space that is compatible with the 3dsMax renderer
				SG_TANGENTSPACEMETHOD_ORTHONORMAL_LEFTHANDED = 0x2 /// Creates an orthonormal tangent space (left-handed, D3D compatible)
			};

			class  TangentSpaceMethodUtil
			{
			public:
				static TangentSpaceMethod Parse(string enumString, TangentSpaceMethod defaultValue)
				{
					if (enumString == "SG_TANGENTSPACEMETHOD_ORTHONORMAL")
					{
						return SG_TANGENTSPACEMETHOD_ORTHONORMAL;
					}
					else if (enumString == "SG_TANGENTSPACEMETHOD_3DSMAX")
					{
						return SG_TANGENTSPACEMETHOD_3DSMAX;
					}
					else if (enumString == "SG_TANGENTSPACEMETHOD_ORTHONORMAL_LEFTHANDED")
					{
						return SG_TANGENTSPACEMETHOD_ORTHONORMAL_LEFTHANDED;
					}
					return defaultValue;
				}

				static TangentSpaceMethod Parse(string enumString)
				{
					if (enumString == "SG_TANGENTSPACEMETHOD_ORTHONORMAL")
					{
						return SG_TANGENTSPACEMETHOD_ORTHONORMAL;
					}
					else if (enumString == "SG_TANGENTSPACEMETHOD_3DSMAX")
					{
						return SG_TANGENTSPACEMETHOD_3DSMAX;
					}
					else if (enumString == "SG_TANGENTSPACEMETHOD_ORTHONORMAL_LEFTHANDED")
					{
						return SG_TANGENTSPACEMETHOD_ORTHONORMAL_LEFTHANDED;
					}
					throw invalid_argument("Invalid TangentSpaceMethod: " + enumString);
				}

				static string ToString(TangentSpaceMethod e)
				{
					if (e == SG_TANGENTSPACEMETHOD_ORTHONORMAL)
					{
						return "SG_TANGENTSPACEMETHOD_ORTHONORMAL";
					}
					else if (e == SG_TANGENTSPACEMETHOD_3DSMAX)
					{
						return "SG_TANGENTSPACEMETHOD_3DSMAX";
					}
					else if (e == SG_TANGENTSPACEMETHOD_ORTHONORMAL_LEFTHANDED)
					{
						return "SG_TANGENTSPACEMETHOD_ORTHONORMAL_LEFTHANDED";
					}
					return "SG_TANGENTSPACEMETHOD_ORTHONORMAL";
				}
			};

			enum TexCoordGeneratorType
			{
				SG_TEXCOORDGENERATORTYPE_PARAMETERIZER = 0x0,
				SG_TEXCOORDGENERATORTYPE_CHARTAGGREGATOR = 0x1
			};

			class  TexCoordGeneratorTypeUtil
			{
			public:
				static TexCoordGeneratorType Parse(string enumString, TexCoordGeneratorType defaultValue)
				{
					if (enumString == "SG_TEXCOORDGENERATORTYPE_PARAMETERIZER")
					{
						return SG_TEXCOORDGENERATORTYPE_PARAMETERIZER;
					}
					else if (enumString == "SG_TEXCOORDGENERATORTYPE_CHARTAGGREGATOR")
					{
						return SG_TEXCOORDGENERATORTYPE_CHARTAGGREGATOR;
					}
					return defaultValue;
				}

				static TexCoordGeneratorType Parse(string enumString)
				{
					if (enumString == "SG_TEXCOORDGENERATORTYPE_PARAMETERIZER")
					{
						return SG_TEXCOORDGENERATORTYPE_PARAMETERIZER;
					}
					else if (enumString == "SG_TEXCOORDGENERATORTYPE_CHARTAGGREGATOR")
					{
						return SG_TEXCOORDGENERATORTYPE_CHARTAGGREGATOR;
					}
					throw invalid_argument("Invalid TexcoordGeneratorType: " + enumString);
				}

				static string ToString(TexCoordGeneratorType e)
				{
					if (e == SG_TEXCOORDGENERATORTYPE_PARAMETERIZER)
					{
						return "SG_TEXCOORDGENERATORTYPE_PARAMETERIZER";
					}
					else if (e == SG_TEXCOORDGENERATORTYPE_CHARTAGGREGATOR)
					{
						return "SG_TEXCOORDGENERATORTYPE_CHARTAGGREGATOR";
					}
					return "SG_TEXCOORDGENERATORTYPE_PARAMETERIZER";
				}
			};

			enum OcclusionModes
			{
				SG_OCCLUSIONMODE_OCCLUDER = 0x0,
				SG_OCCLUSIONMODE_OCCLUDEE = 0x1
			};

			class  OcclusionModesUtil
			{
			public:
				static OcclusionModes Parse(string enumString, OcclusionModes defaultValue)
				{
					if (enumString == "SG_OCCLUSIONMODE_OCCLUDER")
					{
						return SG_OCCLUSIONMODE_OCCLUDER;
					}
					else if (enumString == "SG_OCCLUSIONMODE_OCCLUDEE")
					{
						return SG_OCCLUSIONMODE_OCCLUDEE;
					}
					return defaultValue;
				}

				static OcclusionModes Parse(string enumString)
				{
					if (enumString == "SG_OCCLUSIONMODE_OCCLUDER")
					{
						return SG_OCCLUSIONMODE_OCCLUDER;
					}
					else if (enumString == "SG_OCCLUSIONMODE_OCCLUDEE")
					{
						return SG_OCCLUSIONMODE_OCCLUDEE;
					}
					throw invalid_argument("Invalid TexcoordGeneratorType: " + enumString);
				}

				static string ToString(OcclusionModes e)
				{
					if (e == SG_OCCLUSIONMODE_OCCLUDER)
					{
						return "SG_OCCLUSIONMODE_OCCLUDER";
					}
					else if (e == SG_OCCLUSIONMODE_OCCLUDEE)
					{
						return "SG_OCCLUSIONMODE_OCCLUDEE";
					}
					return "SG_OCCLUSIONMODE_OCCLUDER";
				}
			};
		}
	}
}