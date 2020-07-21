message("这是lib.cmake!")
message(${CMAKE_CURRENT_SOURCE_DIR})
message(${CMAKE_SOURCE_DIR})

set(GLFW_ROOT "${CMAKE_SOURCE_DIR}/../lib/glfw")
set(GLFW_INCLUDEDIR "${GLFW_ROOT}/include")
set(GLFW_LIBRARYDIR "${GLFW_ROOT}/lib")

set(GLAD_ROOT "${CMAKE_SOURCE_DIR}/../lib/glad")
set(GLAD_INCLUDEDIR "${GLAD_ROOT}/include")
set(GLAD_LIBRARYDIR "${GLAD_ROOT}/lib")

# 相当于g++选项中的-I参数的作用
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}
    ${GLFW_INCLUDEDIR}
    ${GLAD_INCLUDEDIR}
)
# 相当于g++命令的-L选项的作用
LINK_DIRECTORIES(
    ${GLFW_LIBRARYDIR}
    ${GLAD_LIBRARYDIR}
)