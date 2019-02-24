option(${PROJECT_NAME}_coroutines_ts "Build with coroutines TS." OFF)

if(${PROJECT_NAME}_coroutines_ts)
    if(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
        add_compile_options(-fcoroutines-ts -stdlib=libc++)
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
        add_compile_options(/await)
    else()
        message(FATAL_ERROR "${PROJECT_NAME}_coroutines_ts not supported yet for ${CMAKE_CXX_COMPILER_ID}")
    endif()
endif()
