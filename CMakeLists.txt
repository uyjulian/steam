include(../tp_stub/krkrz.cmake)

krkrz_plugin(krkrsteam
    NCBIND
    SOURCES
        Main.cpp
        Storages.cpp
        SteamAchievements.cpp
    LIBRARIES
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