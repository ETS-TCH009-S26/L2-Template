# TCH009 - Configuration de compilation (CMake)
# Vous n'avez normalement PAS besoin de modifier ce fichier.
# Ajoutez simplement vos fichiers .c dans src/ et vos tests dans tests/ :
# ils sont detectes automatiquement.

cmake_minimum_required(VERSION 3.21)
project(tch009 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Tous les executables se retrouvent dans build/bin/, peu importe l'IDE.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin")

if(MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra)
endif()

# --- Programme principal ---------------------------------------------------
# Tous les .c de src/ sont compiles ; main.c est mis a part pour que les
# tests puissent reutiliser vos autres fichiers sans conflit de main().
file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/exercice0.c")

add_executable(programme src/exercice0.c ${SOURCES})
target_include_directories(programme PRIVATE src)

# --- Tests unitaires (Unity) -----------------------------------------------
# Desactivable si vous n'avez pas d'acces Internet : -DTCH009_TESTS=OFF
option(TCH009_TESTS "Compiler les tests unitaires (telecharge Unity au 1er build)" ON)

if(TCH009_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        unity
        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
        GIT_TAG v2.6.0
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(unity)

    enable_testing()

    # Un executable de test par fichier tests/*.c (chacun a son propre main()).
    file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c")
    foreach(test_file ${TEST_SOURCES})
        get_filename_component(test_name "${test_file}" NAME_WE)
        add_executable(${test_name} "${test_file}" ${SOURCES})
        target_include_directories(${test_name} PRIVATE src)
        target_link_libraries(${test_name} PRIVATE unity)
        add_test(NAME ${test_name} COMMAND ${test_name})
    endforeach()
endif()
