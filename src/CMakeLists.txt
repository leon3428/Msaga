add_executable(${PROJECT_NAME} 
    Msaga.cpp
    SyntaxTree.cpp
    Expressions.cpp
    Leafs.cpp
    Common.cpp
    OtherNodes.cpp
    Context.cpp
    Serialization.cpp
    Commands.cpp
    Declarations.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_BINARY_DIR}"
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)