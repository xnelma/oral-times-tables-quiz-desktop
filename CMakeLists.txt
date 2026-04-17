cmake_minimum_required(VERSION 3.28)

project(OralTimesTablesQuizDesktop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Needed by clang-tidy.

find_package(Qt6
    REQUIRED COMPONENTS
        Widgets
)

qt_standard_project_setup(
    REQUIRES 6.8
    SUPPORTS_UP_TO 6.11
)

add_subdirectory(src/app)
