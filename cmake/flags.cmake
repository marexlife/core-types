if (MSVC)
    set(CORETYPES_FLAGS /W4)
else()
    set(CORETYPES_FLAGS 
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Werror
    )
endif()