#
# Build PhysX (PROJECT not SOLUTION)
#

SET(PHYSX_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../../../)

SET(PX_SOURCE_DIR ${PHYSX_SOURCE_DIR}/PhysX/src)
SET(MD_SOURCE_DIR ${PHYSX_SOURCE_DIR}/PhysXMetaData)

FIND_PACKAGE(nvToolsExt REQUIRED)

SET(PHYSX_PLATFORM_INCLUDES
	${NVTOOLSEXT_INCLUDE_DIRS}
)

SET(PHYSX_PLATFORM_SRC_FILES
	${PX_SOURCE_DIR}/device/linux/PhysXIndicatorLinux.cpp
	${PX_SOURCE_DIR}/gpu/NpPhysicsGpu.cpp
	${PX_SOURCE_DIR}/gpu/PxGpu.cpp
	${PX_SOURCE_DIR}/gpu/PxParticleDeviceExclusive.cpp
	${PX_SOURCE_DIR}/gpu/PxParticleGpu.cpp
	${PX_SOURCE_DIR}/gpu/PxPhysXGpuModuleLoader.cpp
	${PX_SOURCE_DIR}/gpu/PxPhysXIndicatorDeviceExclusive.cpp
	$<TARGET_OBJECTS:LowLevel>
	$<TARGET_OBJECTS:LowLevelAABB>
	$<TARGET_OBJECTS:LowLevelCloth>
	$<TARGET_OBJECTS:LowLevelDynamics>
	$<TARGET_OBJECTS:LowLevelParticles>
	$<TARGET_OBJECTS:PxTask>
	$<TARGET_OBJECTS:SceneQuery>
	$<TARGET_OBJECTS:SimulationController>	  
)


# Use generator expressions to set config specific preprocessor definitions
SET(PHYSX_COMPILE_DEFS
	# Common to all configurations
	${PHYSX_ANDROID_COMPILE_DEFS};PX_PHYSX_STATIC_LIB;
)

if(${CMAKE_BUILD_TYPE_LOWERCASE} STREQUAL "debug")
	LIST(APPEND PHYSX_COMPILE_DEFS
		${PHYSX_ANDROID_DEBUG_COMPILE_DEFS};
	)
elseif(${CMAKE_BUILD_TYPE_LOWERCASE} STREQUAL "checked")
	LIST(APPEND PHYSX_COMPILE_DEFS
		${PHYSX_ANDROID_CHECKED_COMPILE_DEFS};
	)
elseif(${CMAKE_BUILD_TYPE_LOWERCASE} STREQUAL "profile")
	LIST(APPEND PHYSX_COMPILE_DEFS
		${PHYSX_ANDROID_PROFILE_COMPILE_DEFS};
	)
elseif(${CMAKE_BUILD_TYPE_LOWERCASE} STREQUAL "release")
	LIST(APPEND PHYSX_COMPILE_DEFS
		${PHYSX_ANDROID_RELEASE_COMPILE_DEFS}
	)
else(${CMAKE_BUILD_TYPE_LOWERCASE} STREQUAL "debug")
	MESSAGE(FATAL_ERROR "Unknown configuration ${CMAKE_BUILD_TYPE}")
endif(${CMAKE_BUILD_TYPE_LOWERCASE} STREQUAL "debug")

SET(PHYSX_LIBTYPE STATIC)

# include common PhysX settings
INCLUDE(../common/PhysX.cmake)


# Add linked libraries
# TARGET_LINK_LIBRARIES(PhysX PUBLIC -Wl,--start-group LowLevel LowLevelAABB LowLevelCloth LowLevelDynamics LowLevelParticles PhysXCommon PxFoundation PxPvdSDK PxTask SceneQuery SimulationController -Wl,--end-group)

TARGET_LINK_LIBRARIES(PhysX PUBLIC PhysXCommon PxFoundation PxPvdSDK)

# enable -fPIC so we can link static libs with the editor
SET_TARGET_PROPERTIES(PhysX PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
