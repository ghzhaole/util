project(maoUtilTest)

file(GLOB_RECURSE SRC_FILES "*.cpp")
file(GLOB_RECURSE HDR_FILES "*.h")

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HDR_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR})