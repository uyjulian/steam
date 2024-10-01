cmake_minimum_required(VERSION 3.16)

# UTF-8 source
add_compile_options("$<$<AND:$<C_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:C>>:/utf-8>")
add_compile_options("$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/utf-8>")
add_compile_options("$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<COMPILE_LANGUAGE:CXX>>:/Zc:__cplusplus>")

set(PROJECT_NAME krkrsteam)
set(PROJECT_VERSION 1.00)

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

if(NOT TARGET ncbind)
add_subdirectory(../ncbind ${CMAKE_CURRENT_BINARY_DIR}/ncbind)
endif()

add_library(${PROJECT_NAME} SHARED
    Main.cpp
    Storages.cpp
    SteamAchievements.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ncbind
    steam_api
)

# 環境変数 STEAMWORKS_SDK の設定を強制する
if(DEFINED ENV{STEAMWORKS_SDK})
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$ENV{STEAMWORKS_SDK}/public/steam"
    )
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$ENV{STEAMWORKS_SDK}/redistributable_bin"
    )
else()
    message(FATAL_ERROR "ERR: Please set environmental variable: STEAMWORKS_SDK")
endif()