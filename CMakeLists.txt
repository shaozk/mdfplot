cmake_minimum_required(VERSION 3.20)

project(
    mdfplot
    VERSION 0.0.1
)

set(SRC
    "main.cpp"
)

add_executable(${PROJECT_NAME}
    ${SRC}
)

