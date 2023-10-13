
cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 手动指定SFML库的位置，将路径替换为您的SFML库所在的路径
set(SFML_DIR "D:/Lib/SFML-2.6.0/lib/cmake/SFML")

# 查找SFML包
find_package(SFML 2.5 REQUIRED COMPONENTS system window graphics)
message(STATUS "SFML library status:")
message(STATUS "  version: ${SFML_VERSION}")
message(STATUS "  include: ${SFML_INCLUDE_DIR}")

include_directories(
	"D:/Lib/SFML-2.6.0/include"
)
get_directory_property(dirs INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
    message("Include Directory: ${dir}")
endforeach()
# WIN32
if(WIN32)
    add_executable(CMakeSFMLProject  src/main.cpp)
else()
    add_executable(CMakeSFMLProject src/main.cpp)
endif()
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)
# target_compile_options(CMakeSFMLProject PRIVATE "/utf-8")

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        # PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

# install(TARGETS CMakeSFMLProject )
install(TARGETS CMakeSFMLProject) 
