#
# Build PhysXExtensions common
#

SET(PHYSX_EXTENSIONS_SOURCE
	${LL_SOURCE_DIR}/ExtBroadPhase.cpp
	${LL_SOURCE_DIR}/ExtClothFabricCooker.cpp
	${LL_SOURCE_DIR}/ExtClothGeodesicTetherCooker.cpp
	${LL_SOURCE_DIR}/ExtClothMeshQuadifier.cpp
	${LL_SOURCE_DIR}/ExtClothSimpleTetherCooker.cpp
	${LL_SOURCE_DIR}/ExtCollection.cpp
	${LL_SOURCE_DIR}/ExtConvexMeshExt.cpp
	${LL_SOURCE_DIR}/ExtCpuWorkerThread.cpp
	${LL_SOURCE_DIR}/ExtD6Joint.cpp
	${LL_SOURCE_DIR}/ExtD6JointSolverPrep.cpp
	${LL_SOURCE_DIR}/ExtDefaultCpuDispatcher.cpp
	${LL_SOURCE_DIR}/ExtDefaultErrorCallback.cpp
	${LL_SOURCE_DIR}/ExtDefaultSimulationFilterShader.cpp
	${LL_SOURCE_DIR}/ExtDefaultStreams.cpp
	${LL_SOURCE_DIR}/ExtDistanceJoint.cpp
	${LL_SOURCE_DIR}/ExtDistanceJointSolverPrep.cpp
	${LL_SOURCE_DIR}/ExtExtensions.cpp
	${LL_SOURCE_DIR}/ExtFixedJoint.cpp
	${LL_SOURCE_DIR}/ExtFixedJointSolverPrep.cpp
	${LL_SOURCE_DIR}/ExtJoint.cpp
	${LL_SOURCE_DIR}/ExtMetaData.cpp
	${LL_SOURCE_DIR}/ExtParticleExt.cpp
	${LL_SOURCE_DIR}/ExtPrismaticJoint.cpp
	${LL_SOURCE_DIR}/ExtPrismaticJointSolverPrep.cpp
	${LL_SOURCE_DIR}/ExtPvd.cpp
	${LL_SOURCE_DIR}/ExtPxStringTable.cpp
	${LL_SOURCE_DIR}/ExtRaycastCCD.cpp
	${LL_SOURCE_DIR}/ExtRevoluteJoint.cpp
	${LL_SOURCE_DIR}/ExtRevoluteJointSolverPrep.cpp
	${LL_SOURCE_DIR}/ExtRigidBodyExt.cpp
	${LL_SOURCE_DIR}/ExtSceneQueryExt.cpp
	${LL_SOURCE_DIR}/ExtSimpleFactory.cpp
	${LL_SOURCE_DIR}/ExtSmoothNormals.cpp
	${LL_SOURCE_DIR}/ExtSphericalJoint.cpp
	${LL_SOURCE_DIR}/ExtSphericalJointSolverPrep.cpp
	${LL_SOURCE_DIR}/ExtTriangleMeshExt.cpp
	${LL_SOURCE_DIR}/ExtConstraintHelper.h
	${LL_SOURCE_DIR}/ExtCpuWorkerThread.h
	${LL_SOURCE_DIR}/ExtD6Joint.h
	${LL_SOURCE_DIR}/ExtDefaultCpuDispatcher.h
	${LL_SOURCE_DIR}/ExtDistanceJoint.h
	${LL_SOURCE_DIR}/ExtFixedJoint.h
	${LL_SOURCE_DIR}/ExtInertiaTensor.h
	${LL_SOURCE_DIR}/ExtJoint.h
	${LL_SOURCE_DIR}/ExtJointMetaDataExtensions.h
	${LL_SOURCE_DIR}/ExtPlatform.h
	${LL_SOURCE_DIR}/ExtPrismaticJoint.h
	${LL_SOURCE_DIR}/ExtPvd.h
	${LL_SOURCE_DIR}/ExtRevoluteJoint.h
	${LL_SOURCE_DIR}/ExtSerialization.h
	${LL_SOURCE_DIR}/ExtSharedQueueEntryPool.h
	${LL_SOURCE_DIR}/ExtSphericalJoint.h
	${LL_SOURCE_DIR}/ExtTaskQueueHelper.h	
)
SOURCE_GROUP(src FILES ${PHYSX_EXTENSIONS_SOURCE})

SET(PHYSX_EXTENSIONS_METADATA_SOURCE
	${PHYSX_SOURCE_DIR}/PhysXMetaData/extensions/src/PxExtensionAutoGeneratedMetaDataObjects.cpp
	${PHYSX_SOURCE_DIR}/PhysXMetaData/extensions/include/PxExtensionAutoGeneratedMetaDataObjectNames.h
	${PHYSX_SOURCE_DIR}/PhysXMetaData/extensions/include/PxExtensionAutoGeneratedMetaDataObjects.h
	${PHYSX_SOURCE_DIR}/PhysXMetaData/extensions/include/PxExtensionMetaDataObjects.h
)
SOURCE_GROUP(src\\metadata FILES ${PHYSX_EXTENSIONS_METADATA_SOURCE})

SET(PHYSX_EXTENSIONS_INCLUDE
	${PHYSX_ROOT_DIR}/Include/extensions/PxBinaryConverter.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxBroadPhaseExt.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxClothFabricCooker.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxClothMeshDesc.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxClothMeshQuadifier.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxClothTetherCooker.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxCollectionExt.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxConstraintExt.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxConvexMeshExt.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxD6Joint.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxDefaultAllocator.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxDefaultCpuDispatcher.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxDefaultErrorCallback.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxDefaultSimulationFilterShader.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxDefaultStreams.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxDistanceJoint.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxExtensionsAPI.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxFixedJoint.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxJoint.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxJointLimit.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxJointRepXSerializer.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxMassProperties.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxParticleExt.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxPrismaticJoint.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxRaycastCCD.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxRepXSerializer.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxRepXSimpleType.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxRevoluteJoint.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxRigidActorExt.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxRigidBodyExt.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxSceneQueryExt.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxSerialization.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxShapeExt.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxSimpleFactory.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxSmoothNormals.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxSphericalJoint.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxStringTableExt.h
	${PHYSX_ROOT_DIR}/Include/extensions/PxTriangleMeshExt.h
)
SOURCE_GROUP(include FILES ${PHYSX_EXTENSIONS_INCLUDE})

SET(PHYSX_EXTENSIONS_SERIALIZATION_SOURCE
	${LL_SOURCE_DIR}/serialization/SnSerialization.cpp
	${LL_SOURCE_DIR}/serialization/SnSerializationRegistry.cpp
	${LL_SOURCE_DIR}/serialization/SnSerializationRegistry.h
	${LL_SOURCE_DIR}/serialization/SnSerialUtils.cpp
	${LL_SOURCE_DIR}/serialization/SnSerialUtils.h
)
SOURCE_GROUP(serialization FILES ${PHYSX_EXTENSIONS_SERIALIZATION_SOURCE})

SET(PHYSX_EXTENSIONS_SERIALIZATION_XML_SOURCE
	${LL_SOURCE_DIR}/serialization/Xml/SnJointRepXSerializer.cpp
	${LL_SOURCE_DIR}/serialization/Xml/SnRepXCoreSerializer.cpp
	${LL_SOURCE_DIR}/serialization/Xml/SnRepXUpgrader.cpp
	${LL_SOURCE_DIR}/serialization/Xml/SnXmlSerialization.cpp
	${LL_SOURCE_DIR}/serialization/Xml/SnPxStreamOperators.h
	${LL_SOURCE_DIR}/serialization/Xml/SnRepX1_0Defaults.h
	${LL_SOURCE_DIR}/serialization/Xml/SnRepX3_1Defaults.h
	${LL_SOURCE_DIR}/serialization/Xml/SnRepX3_2Defaults.h
	${LL_SOURCE_DIR}/serialization/Xml/SnRepXCollection.h
	${LL_SOURCE_DIR}/serialization/Xml/SnRepXCoreSerializer.h
	${LL_SOURCE_DIR}/serialization/Xml/SnRepXSerializerImpl.h
	${LL_SOURCE_DIR}/serialization/Xml/SnRepXUpgrader.h
	${LL_SOURCE_DIR}/serialization/Xml/SnSimpleXmlWriter.h
	${LL_SOURCE_DIR}/serialization/Xml/SnXmlDeserializer.h
	${LL_SOURCE_DIR}/serialization/Xml/SnXmlImpl.h
	${LL_SOURCE_DIR}/serialization/Xml/SnXmlMemoryAllocator.h
	${LL_SOURCE_DIR}/serialization/Xml/SnXmlMemoryPool.h
	${LL_SOURCE_DIR}/serialization/Xml/SnXmlMemoryPoolStreams.h
	${LL_SOURCE_DIR}/serialization/Xml/SnXmlReader.h
	${LL_SOURCE_DIR}/serialization/Xml/SnXmlSerializer.h
	${LL_SOURCE_DIR}/serialization/Xml/SnXmlSimpleXmlWriter.h
	${LL_SOURCE_DIR}/serialization/Xml/SnXmlStringToType.h
	${LL_SOURCE_DIR}/serialization/Xml/SnXmlVisitorReader.h
	${LL_SOURCE_DIR}/serialization/Xml/SnXmlVisitorWriter.h
	${LL_SOURCE_DIR}/serialization/Xml/SnXmlWriter.h
)
SOURCE_GROUP(serialization\\xml FILES ${PHYSX_EXTENSIONS_SERIALIZATION_XML_SOURCE})

SET(PHYSX_EXTENSIONS_SERIALIZATION_FILE_SOURCE
	${LL_SOURCE_DIR}/serialization/File/SnFile.h
)
SOURCE_GROUP(serialization\\file FILES ${PHYSX_EXTENSIONS_SERIALIZATION_FILE_SOURCE})

SET(PHYSX_EXTENSIONS_SERIALIZATION_BINARY_SOURCE
	${LL_SOURCE_DIR}/serialization/Binary/SnBinaryDeserialization.cpp
	${LL_SOURCE_DIR}/serialization/Binary/SnBinarySerialization.cpp
	${LL_SOURCE_DIR}/serialization/Binary/SnConvX.cpp
	${LL_SOURCE_DIR}/serialization/Binary/SnConvX_Align.cpp
	${LL_SOURCE_DIR}/serialization/Binary/SnConvX_Convert.cpp
	${LL_SOURCE_DIR}/serialization/Binary/SnConvX_Error.cpp
	${LL_SOURCE_DIR}/serialization/Binary/SnConvX_MetaData.cpp
	${LL_SOURCE_DIR}/serialization/Binary/SnConvX_Output.cpp
	${LL_SOURCE_DIR}/serialization/Binary/SnConvX_Union.cpp
	${LL_SOURCE_DIR}/serialization/Binary/SnSerializationContext.cpp
	${LL_SOURCE_DIR}/serialization/Binary/SnConvX.h
	${LL_SOURCE_DIR}/serialization/Binary/SnConvX_Align.h
	${LL_SOURCE_DIR}/serialization/Binary/SnConvX_Common.h
	${LL_SOURCE_DIR}/serialization/Binary/SnConvX_MetaData.h
	${LL_SOURCE_DIR}/serialization/Binary/SnConvX_Output.h
	${LL_SOURCE_DIR}/serialization/Binary/SnConvX_Union.h
	${LL_SOURCE_DIR}/serialization/Binary/SnSerializationContext.h
)
SOURCE_GROUP(serialization\\binary FILES ${PHYSX_EXTENSIONS_SERIALIZATION_BINARY_SOURCE})

ADD_LIBRARY(PhysXExtensions STATIC 
	${PHYSXEXTENSIONS_PLATFORM_SRC_FILES}
	
	${PHYSX_EXTENSIONS_SOURCE}
	${PHYSX_EXTENSIONS_METADATA_SOURCE}
	
	${PHYSX_EXTENSIONS_INCLUDE}
	
	${PHYSX_EXTENSIONS_SERIALIZATION_SOURCE}
	${PHYSX_EXTENSIONS_SERIALIZATION_XML_SOURCE}
	${PHYSX_EXTENSIONS_SERIALIZATION_FILE_SOURCE}
	${PHYSX_EXTENSIONS_SERIALIZATION_BINARY_SOURCE}
)

TARGET_INCLUDE_DIRECTORIES(PhysXExtensions 

	PRIVATE ${PHYSXEXTENSIONS_PLATFORM_INCLUDES}

	PRIVATE ${PXSHARED_ROOT_DIR}/include
	PRIVATE ${PXSHARED_ROOT_DIR}/src/foundation/include
	PRIVATE ${PXSHARED_ROOT_DIR}/src/fastxml/include
	PRIVATE ${PXSHARED_ROOT_DIR}/src/pvd/include

	PRIVATE ${PHYSX_ROOT_DIR}/Include
	PRIVATE ${PHYSX_ROOT_DIR}/Include/common
	PRIVATE ${PHYSX_ROOT_DIR}/Include/geometry
	PRIVATE ${PHYSX_ROOT_DIR}/Include/pvd
	PRIVATE ${PHYSX_ROOT_DIR}/Include/cooking
	PRIVATE ${PHYSX_ROOT_DIR}/Include/extensions
	PRIVATE ${PHYSX_ROOT_DIR}/Include/vehicle
	PRIVATE ${PHYSX_ROOT_DIR}/Include/cloth
	PRIVATE ${PHYSX_ROOT_DIR}/Include/GeomUtils

	PRIVATE ${PHYSX_SOURCE_DIR}/Common/include
	PRIVATE ${PHYSX_SOURCE_DIR}/Common/src
	
	PRIVATE ${PHYSX_SOURCE_DIR}/GeomUtils/headers
	PRIVATE ${PHYSX_SOURCE_DIR}/GeomUtils/src
	PRIVATE ${PHYSX_SOURCE_DIR}/GeomUtils/src/contact
	PRIVATE ${PHYSX_SOURCE_DIR}/GeomUtils/src/common
	PRIVATE ${PHYSX_SOURCE_DIR}/GeomUtils/src/convex
	PRIVATE ${PHYSX_SOURCE_DIR}/GeomUtils/src/distance
	PRIVATE ${PHYSX_SOURCE_DIR}/GeomUtils/src/sweep
	PRIVATE ${PHYSX_SOURCE_DIR}/GeomUtils/src/gjk
	PRIVATE ${PHYSX_SOURCE_DIR}/GeomUtils/src/intersection
	PRIVATE ${PHYSX_SOURCE_DIR}/GeomUtils/src/mesh
	PRIVATE ${PHYSX_SOURCE_DIR}/GeomUtils/src/hf
	PRIVATE ${PHYSX_SOURCE_DIR}/GeomUtils/src/pcm

	PRIVATE ${PHYSX_SOURCE_DIR}/PhysXMetaData/core/include
	PRIVATE ${PHYSX_SOURCE_DIR}/PhysXMetaData/extensions/include
	
	PRIVATE ${PHYSX_SOURCE_DIR}/PhysXExtensions/src
	PRIVATE ${PHYSX_SOURCE_DIR}/PhysXExtensions/src/serialization/Xml
	PRIVATE ${PHYSX_SOURCE_DIR}/PhysXExtensions/src/serialization/Binary
	PRIVATE ${PHYSX_SOURCE_DIR}/PhysXExtensions/src/serialization/File

	PRIVATE ${PHYSX_SOURCE_DIR}/PvdSDK/src
	PRIVATE ${PHYSX_SOURCE_DIR}/PhysX/src
)

TARGET_LINK_LIBRARIES(PhysXExtensions PUBLIC PsFastXml)

# Use generator expressions to set config specific preprocessor definitions
TARGET_COMPILE_DEFINITIONS(PhysXExtensions 
	PRIVATE ${PHYSXEXTENSIONS_COMPILE_DEFS}
)


SET_TARGET_PROPERTIES(PhysXExtensions PROPERTIES
	OUTPUT_NAME PhysX3Extensions
)

SET_TARGET_PROPERTIES(PhysXExtensions PROPERTIES 
	COMPILE_PDB_NAME_DEBUG "PhysX3Extensions${CMAKE_DEBUG_POSTFIX}"
	COMPILE_PDB_NAME_CHECKED "PhysX3Extensions${CMAKE_CHECKED_POSTFIX}"
	COMPILE_PDB_NAME_PROFILE "PhysX3Extensions${CMAKE_PROFILE_POSTFIX}"
	COMPILE_PDB_NAME_RELEASE "PhysX3Extensions${CMAKE_RELEASE_POSTFIX}"
)