
SOURCES += Main.cpp Storages.cpp SteamAchievements.cpp osw_wrap/steam_api_osw.cpp

INCFLAGS += -Iexternal/open-steamworks/OpenSteamworks -Iosw_wrap

LDLIBS += -luuid -lole32

PROJECT_BASENAME = krkrsteam

RC_DESC ?= Steamworks interface for TVP(KIRIKIRI) (2/Z)
RC_PRODUCTNAME ?= Steamworks interface for TVP(KIRIKIRI) (2/Z)
RC_LEGALCOPYRIGHT ?= Copyright (C) 2015-2019 Go Watanabe; This product is licensed under the MIT license.

include external/ncbind/Rules.lib.make
