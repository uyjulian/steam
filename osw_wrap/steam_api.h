
#ifndef _STEAM_API_H
#define _STEAM_API_H

#include "SteamTypes.h"

#if defined(__GNUC__) && defined(_WIN32)
	// This ugly hack allows us to provide GCC compatibility on windows without much effort
	#pragma push_macro("virtual")
	#undef virtual
	#define virtual virtual __thiscall
#endif

#include "CCallback.h"

#include "ISteamApps004.h"
#include "ISteamRemoteStorage014.h"
#include "ISteamScreenshots001.h"
#include "ISteamUser004.h"
#include "ISteamUserStats011.h"
#include "ISteamUtils003.h"
#include "ISteamVideo001.h"

#if defined(__GNUC__) && defined(_WIN32)
	#pragma pop_macro("virtual")
#endif

extern bool SteamAPI_Init();
extern void SteamAPI_RunCallbacks();
extern void SteamAPI_Shutdown();
extern void SteamAPI_RegisterCallback(class CCallbackBase *pCallback, int iCallback);
extern void SteamAPI_UnregisterCallback(class CCallbackBase *pCallback);
extern void* SteamInternal_FindOrCreateUserInterface(int32_t hSteamUser, const char* pszVersion);
extern int32_t SteamAPI_GetHSteamUser();

typedef ISteamApps004 ISteamApps;
typedef ISteamRemoteStorage014 ISteamRemoteStorage;
typedef ISteamScreenshots001 ISteamScreenshots;
typedef ISteamUser004 ISteamUser;
typedef ISteamUserStats011 ISteamUserStats;
typedef ISteamUtils003 ISteamUtils;
typedef ISteamVideo001 ISteamVideo;

#define STEAMAPPS_INTERFACE_VERSION STEAMAPPS_INTERFACE_VERSION_004
#define STEAMREMOTESTORAGE_INTERFACE_VERSION STEAMREMOTESTORAGE_INTERFACE_VERSION_014
#define STEAMSCREENSHOTS_INTERFACE_VERSION STEAMSCREENSHOTS_INTERFACE_VERSION_001
#define STEAMUSER_INTERFACE_VERSION STEAMUSER_INTERFACE_VERSION_004
#define STEAMUSERSTATS_INTERFACE_VERSION STEAMUSERSTATS_INTERFACE_VERSION_011
#define STEAMUTILS_INTERFACE_VERSION STEAMUTILS_INTERFACE_VERSION_003
#define STEAMVIDEO_INTERFACE_VERSION STEAMVIDEO_INTERFACE_VERSION_001

extern ISteamApps* SteamApps();
extern ISteamRemoteStorage* SteamRemoteStorage();
extern ISteamScreenshots* SteamScreenshots();
extern ISteamUser* SteamUser();
extern ISteamUserStats* SteamUserStats();
extern ISteamUtils* SteamUtils();
extern ISteamVideo* SteamVideo();

#endif
