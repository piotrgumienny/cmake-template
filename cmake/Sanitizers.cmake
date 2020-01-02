set(${PROJECT_NAME}_sanitizer "" CACHE STRING
    "Sanitizer types: thread, address, leak, memory, undefined.")

if(${PROJECT_NAME}_sanitizer)
    if(MSVC)
        message(FATAL_ERROR "${PROJECT_NAME}_sanitizer not supported yet for MSVC")
    else()
        add_compile_options(-fsanitize=${${PROJECT_NAME}_sanitizer})
        add_link_options(-fsanitize=${${PROJECT_NAME}_sanitizer})
    endif()
    if(${PROJECT_NAME}_sanitizer STREQUAL thread)
        set(MEMORYCHECK_TYPE ThreadSanitizer)
    elseif(${PROJECT_NAME}_sanitizer STREQUAL address)
        set(MEMORYCHECK_TYPE AddressSanitizer)
        if(HAVE_GLIBCXX)
            add_compile_definitions(
                $<$<COMPILE_LANGUAGE:CXX>:_GLIBCXX_SANITIZE_VECTOR>
            )
        endif()
    elseif(${PROJECT_NAME}_sanitizer STREQUAL leak)
        set(MEMORYCHECK_TYPE LeakSanitizer)
    elseif(${PROJECT_NAME}_sanitizer STREQUAL memory)
        set(MEMORYCHECK_TYPE MemorySanitizer)
    elseif(${PROJECT_NAME}_sanitizer STREQUAL undefined)
        set(MEMORYCHECK_TYPE UndefinedBehaviorSanitizer)
    else()
        message(FATAL_ERROR
            "${PROJECT_NAME}_sanitizer=${${PROJECT_NAME}_sanitizer} not supported yet")
    endif()
endif()
