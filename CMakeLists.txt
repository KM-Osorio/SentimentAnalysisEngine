cmake_minimum_required(VERSION 4.0)
project(hi)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

# --- 1. Modularidad: CREAR LA LIBRERÍA DE LÓGICA ---
# ¡Apunta a la IMPLEMENTACIÓN!
add_library(SentimentLib src/Functions.cpp)

# --- 2. GoogleTest Setup: DESCARGAR LA HERRAMIENTA ---
enable_testing()
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # Truco para Windows
FetchContent_MakeAvailable(googletest)

# --- 3. Ejecutable de Pruebas ---
# Corregido el nombre a run_tests (Línea 19)
add_executable(run_tests tests/SentimentTests.cpp)
# Corregido el nombre del ejecutable a run_tests (Línea 20)
target_link_libraries(run_tests PRIVATE SentimentLib gtest_main)
include(GoogleTest)
gtest_discover_tests(run_tests)

# --- 4. Ejecutable Principal ---
add_executable(SentimentAnalysisEngine src/main.cpp)
target_link_libraries(SentimentAnalysisEngine PRIVATE SentimentLib)