cmake_minimum_required(VERSION 3.28)
cmake_policy(SET CMP0167 NEW)

project(Quiz)

find_package(Crow)

# Specify asset and template directories
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_OUTPUT_DIR "${CMAKE_BINARY_DIR}/assets")
set(TEMPLATES_SOURCE_DIR "${CMAKE_SOURCE_DIR}/templates")
set(TEMPLATES_OUTPUT_DIR "${CMAKE_BINARY_DIR}/templates")

# Copy assets to the build directory
file(COPY ${ASSETS_SOURCE_DIR} DESTINATION ${ASSETS_OUTPUT_DIR})
file(COPY ${TEMPLATES_SOURCE_DIR} DESTINATION ${TEMPLATES_OUTPUT_DIR})

# Add the executable
add_executable(server src/main.cpp src/CardService.cpp)

# Link libraries
target_link_libraries(server PUBLIC Crow::Crow)

# Include directories
target_include_directories(server PRIVATE include)

# Define ASSETS_DIR and TEMPLATES_DIR as preprocessor macros
target_compile_definitions(server PRIVATE
    ASSETS_DIR="${ASSETS_OUTPUT_DIR}"
    TEMPLATES_DIR="${TEMPLATES_OUTPUT_DIR}"
)

# Ensure that the assets and templates are copied before the main executable is built
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_SOURCE_DIR} ${ASSETS_OUTPUT_DIR}
    DEPENDS ${ASSETS_SOURCE_DIR}
    COMMENT "Copying assets to build directory"
)

add_custom_target(copy_templates ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${TEMPLATES_SOURCE_DIR} ${TEMPLATES_OUTPUT_DIR}
    DEPENDS ${TEMPLATES_SOURCE_DIR}
    COMMENT "Copying templates to build directory"
)

# Make sure the assets and templates are copied before building the main executable
add_dependencies(server copy_assets copy_templates)

