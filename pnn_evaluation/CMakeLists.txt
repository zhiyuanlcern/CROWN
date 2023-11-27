cmake_minimum_required(VERSION 3.12)
project(HiggsAnalysis)

# Find ROOT package
find_package(ROOT REQUIRED COMPONENTS TMVA ROOTDataFrame ROOTTMVASofie  )
find_package(LAPACK)
if(LAPACK_FOUND)
    include_directories(${LAPACK_INCLUDE_DIRS})
    link_libraries(${LAPACK_LIBRARIES})
endif()
# Include directories
include(${ROOT_USE_FILE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${ROOT_INCLUDE_DIRS})

# Define the executable
add_executable(HiggsAnalysis higgs_analysis.cpp)

# Link against ROOT libraries
target_link_libraries(HiggsAnalysis ${ROOT_LIBRARIES})
