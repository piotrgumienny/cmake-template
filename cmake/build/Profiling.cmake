option(${PROJECT_NAME}_profiling "Build for performance analysis." OFF)

if(${PROJECT_NAME}_profiling)
    if(MSVC)
        message(FATAL_ERROR "${PROJECT_NAME}_profiling not supported yet for MSVC")
    else()
        string(APPEND CMAKE_C_FLAGS " -pg")
        string(APPEND CMAKE_CXX_FLAGS " -pg")
    endif()
endif()
