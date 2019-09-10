cmake_minimum_required(VERSION 3.8)

############################################
# MSVC Compiler Setup for Xbox One / OneCore
# By: Billy Hulbert
############################################

set(SDK_VERSION "$ENV{WindowsSdkVersion}")

set(SDK_INCLUDE_DIRS)
list(APPEND SDK_INCLUDE_DIRS "$ENV{WindowSdkDir}/Include/${SDK_VERSION}winrt")
list(APPEND SDK_INCLUDE_DIRS "$ENV{WindowSdkDir}/Include/${SDK_VERSION}shared")
list(APPEND SDK_INCLUDE_DIRS "$ENV{WindowSdkDir}/Include/${SDK_VERSION}ucrt")

include_directories(
	${SDK_INCLUDE_DIRS}
	${OWN_INCLUDE_DIR}
)

# Setup OneCore libraries paths
set(ONECORE_LIBRARY_PATH)
list(APPEND ONECORE_LIBRARY_PATH "$ENV{VCToolsInstallDir}")
list(APPEND ONECORE_LIBRARY_PATH "$ENV{WindowsSdkDir}/lib/${SDK_VERSION}/ucrt/x64")
list(APPEND ONECORE_LIBRARY_PATH "$ENV{WindowsSdkDir}/lib/${SDK_VERSION}/um/x64")

set(PRECOMPILED_LIBRARY_PATH)
list(APPEND PRECOMPILED_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/Precompiled")

link_directories(
	${ONECORE_LIBRARY_PATH}
	${PRECOMPILED_LIBRARY_PATH}
)

# Ignore the default Win32 libraries
set(CMAKE_CXX_STANDARD_LIBRARIES "")

set(STATIC_CRT_LIB "libcmt$<$<OR:$<CONFIG:Debug>,$<CONFIG:Checked>>:d>.lib")
set(STATIC_CPP_LIB "libcpmt$<$<OR:$<CONFIG:Debug>,$<CONFIG:Checked>>:d>.lib")
set(STATIC_VCRT_LIB "libvcruntime$<$<OR:$<CONFIG:Debug>,$<CONFIG:Checked>>:d>.lib")
set(STATIC_UCRT_LIB "libucrt$<$<OR:$<CONFIG:Debug>,$<CONFIG:Checked>>:d>.lib")

# Set common libraries to prevent execution from being blocked
set(DEFAULT_STANDARD_LIBRARIES)
list(APPEND DEFAULT_STANDARD_LIBRARIES "onecore.lib")
list(APPEND DEFAULT_STANDARD_LIBRARIES "${STATIC_CRT_LIB}")
list(APPEND DEFAULT_STANDARD_LIBRARIES "${STATIC_UCRT_LIB}")
list(APPEND DEFAULT_STANDARD_LIBRARIES "${STATIC_VCRT_LIB}")
list(APPEND DEFAULT_STANDARD_LIBRARIES "${STATIC_CPP_LIB}")

# Default definitions
set(DEFAULT_DEFINITIONS
    -DAMD64
    -D_WIN64
    -D_AMD64
    -D_M_AMD64
    -D_APISET_WINDOWS_VERSION=0x601
    -D_APISET_MINWIN_VERSION=0x0101
    -D_APISET_MINCORE_VERSION=0x0100
    -DWIN32_LEAN_AND_MEAN=1
    -D_CRT_SECURE_NO_WARNINGS
)
string(REPLACE ";" " " DEFAULT_DEFINITIONS "${DEFAULT_DEFINITIONS}")

add_definitions(${DEFAULT_DEFINITIONS})

# Default flags to use (C++)
set(CXX_COMMON_FLAGS 
    /TP             # Compile as C++
    /d2Zi+          # Make optimized builds debugging easier
    /W3             # Set warning level to 3
    /wd4996         # Ignore deprecation warnings
    /Oi             # Enable intrinsics
    /GF             # Enable read-only string pooling
    /Gm             # Enable minimal rebuild
    /EHsc           # Enable C++ EH (w/ SEH exceptions)
    /Zp8            # Pack structs on 8-byte boundary
    /Gy             # Enable function level linking
    /Zc:wchar_t-    # Set wchar_t as an interal type
    /Zc:forScope    # Standard scoping rules
    /GS             # Enable buffer security check
    /Zi             # Enable debug info
)
string(REPLACE ";" " " CXX_COMMON_FLAGS "${CXX_COMMON_FLAGS}")

set(CMAKE_CXX_FLAGS "${CXX_COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CXX_COMMON_FLAGS} /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "${CXX_COMMON_FLAGS} /MT")

# Common linker flags
set(MSVC_LINKER_FLAGS "/NOLOGO /DYNAMICBASE /INCREMENTAL:NO ")

# Setup target specific flags
set(CMAKE_MODULE_LINKER_FLAGS "${MSVC_LINKER_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${MSVC_LINKER_FLAGS} /SUBSYSTEM:WINDOWS,6.00 /NXCOMPAT")
set(CMAKE_EXE_LINKER_FLAGS "${MSVC_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")

set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "/NOVCFEATURE")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${MSVC_LINKER_FLAGS}")

set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "/LTCG")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/LTCG /OPT:REF /OPT:ICF")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/LTCG /OPT:REF /OPT:ICF")