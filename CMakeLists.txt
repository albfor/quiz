cmake_minimum_required(VERSION 3.28)

project(Quiz)

# Specify asset and template directories
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_OUTPUT_DIR "${CMAKE_BINARY_DIR}/assets")
set(TEMPLATES_SOURCE_DIR "${CMAKE_SOURCE_DIR}/templates")
set(TEMPLATES_OUTPUT_DIR "${CMAKE_BINARY_DIR}/templates")

# Copy assets to the build directory
file(COPY ${ASSETS_SOURCE_DIR} DESTINATION ${ASSETS_OUTPUT_DIR})
file(COPY ${TEMPLATES_SOURCE_DIR} DESTINATION ${TEMPLATES_OUTPUT_DIR})

# Add the executable
add_executable(main src/main.cpp src/CardService.cpp)

# Include directories
target_include_directories(main PRIVATE include)

# Define ASSETS_DIR and TEMPLATES_DIR as preprocessor macros
target_compile_definitions(main PRIVATE 
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
add_dependencies(main copy_assets copy_templates)

