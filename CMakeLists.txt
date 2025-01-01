cmake_minimum_required(VERSION 3.20)

project(
    mdfplot
    VERSION 0.0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC
    "main.cpp"
)

add_executable(${PROJECT_NAME}
    ${SRC}
)

# 链接mdf库
target_include_directories(mdfplot PUBLIC "/usr/local/include")
target_link_libraries(mdfplot PRIVATE "/usr/local/lib/libmdf.a")

# 链接mdf依赖库
include("./script/zlib.cmake")
include("./script/expat.cmake")

target_compile_definitions(mdfplot PRIVATE xml_static)
target_link_libraries(mdfplot PRIVATE ${EXPAT_LIBRARIES})
target_link_libraries(mdfplot PRIVATE ${ZLIB_LIBRARIES})
