
#include <steam_api.h>
#include <stdint.h>

typedef bool (STEAM_CALL *SteamAPI_Init_Fn)();
typedef void (STEAM_CALL *SteamAPI_RunCallbacks_Fn)();
typedef void (STEAM_CALL *SteamAPI_Shutdown_Fn)();
typedef void (STEAM_CALL *SteamAPI_RegisterCallback_Fn)(class CCallbackBase *pCallback, int iCallback);
typedef void (STEAM_CALL *SteamAPI_UnregisterCallback_Fn)(class CCallbackBase *pCallback);
typedef void* (STEAM_CALL *SteamInternal_FindOrCreateUserInterface_Fn)(int32_t hSteamUser, const char* pszVersion);
typedef int32_t (STEAM_CALL *SteamAPI_GetHSteamUser_Fn)();

typedef struct steamapi_ptrs_
{
	SteamAPI_Init_Fn Init;
	SteamAPI_RunCallbacks_Fn RunCallbacks;
	SteamAPI_Shutdown_Fn Shutdown;
	SteamAPI_RegisterCallback_Fn RegisterCallback;
	SteamAPI_UnregisterCallback_Fn UnregisterCallback;
	SteamInternal_FindOrCreateUserInterface_Fn FindOrCreateUserInterface;
	SteamAPI_GetHSteamUser_Fn GetHSteamUser;
} steamapi_ptrs_t;

typedef struct steamapi_interfaces_
{
	ISteamApps* apps;
	ISteamRemoteStorage* remotestorage;
	ISteamScreenshots* screenshots;
	ISteamUser* user;
	ISteamUserStats* userstats;
	ISteamUtils* utils;
	ISteamVideo* video;
} steamapi_interfaces_t;

static steamapi_ptrs_t steamapi_ptrs;
static steamapi_interfaces_t steamapi_interfaces;
static int steamapi_initcount = 0;
static HINSTANCE steamapi_lib = NULL;

bool SteamAPI_Init()
{
	bool init_result;
	init_result = steamapi_initcount > 0;
	if (steamapi_initcount == 0)
	{
		HINSTANCE lib;
#if defined(_M_X64) || defined(__x86_64__)
		lib = LoadLibrary(TEXT("steam_api64.dll"));
#else
		lib = LoadLibrary(TEXT("steam_api.dll"));
#endif
		if (lib == NULL)
		{
			return init_result;
		}
		steamapi_ptrs.Init = (SteamAPI_Init_Fn)GetProcAddress(lib, "SteamAPI_Init");
		steamapi_ptrs.RunCallbacks = (SteamAPI_RunCallbacks_Fn)GetProcAddress(lib, "SteamAPI_RunCallbacks");
		steamapi_ptrs.Shutdown = (SteamAPI_Shutdown_Fn)GetProcAddress(lib, "SteamAPI_Shutdown");
		steamapi_ptrs.RegisterCallback = (SteamAPI_RegisterCallback_Fn)GetProcAddress(lib, "SteamAPI_RegisterCallback");
		steamapi_ptrs.UnregisterCallback = (SteamAPI_UnregisterCallback_Fn)GetProcAddress(lib, "SteamAPI_UnregisterCallback");
		steamapi_ptrs.FindOrCreateUserInterface = (SteamInternal_FindOrCreateUserInterface_Fn)GetProcAddress(lib, "SteamInternal_FindOrCreateUserInterface");
		steamapi_ptrs.GetHSteamUser = (SteamAPI_GetHSteamUser_Fn)GetProcAddress(lib, "SteamAPI_GetHSteamUser");
		if (
			steamapi_ptrs.Init == NULL ||
			steamapi_ptrs.RunCallbacks == NULL ||
			steamapi_ptrs.Shutdown == NULL ||
			steamapi_ptrs.RegisterCallback == NULL ||
			steamapi_ptrs.UnregisterCallback == NULL ||
			steamapi_ptrs.FindOrCreateUserInterface == NULL ||
			steamapi_ptrs.GetHSteamUser == NULL ||
			false
		)
		{
			return init_result;
		}
	}
	if (steamapi_ptrs.Init)
	{
		init_result = steamapi_ptrs.Init();

		if (init_result)
		{
			int32_t hsteamuser;
			hsteamuser = steamapi_ptrs.GetHSteamUser();
			steamapi_interfaces.apps = (ISteamApps*)steamapi_ptrs.FindOrCreateUserInterface(hsteamuser, STEAMAPPS_INTERFACE_VERSION);
			steamapi_interfaces.remotestorage = (ISteamRemoteStorage*)steamapi_ptrs.FindOrCreateUserInterface(hsteamuser, STEAMREMOTESTORAGE_INTERFACE_VERSION);
			steamapi_interfaces.screenshots = (ISteamScreenshots*)steamapi_ptrs.FindOrCreateUserInterface(hsteamuser, STEAMSCREENSHOTS_INTERFACE_VERSION);
			steamapi_interfaces.user = (ISteamUser*)steamapi_ptrs.FindOrCreateUserInterface(hsteamuser, STEAMUSER_INTERFACE_VERSION);
			steamapi_interfaces.userstats = (ISteamUserStats*)steamapi_ptrs.FindOrCreateUserInterface(hsteamuser, STEAMUSERSTATS_INTERFACE_VERSION);
			steamapi_interfaces.utils = (ISteamUtils*)steamapi_ptrs.FindOrCreateUserInterface(hsteamuser, STEAMUTILS_INTERFACE_VERSION);
			steamapi_interfaces.video = (ISteamVideo*)steamapi_ptrs.FindOrCreateUserInterface(hsteamuser, STEAMVIDEO_INTERFACE_VERSION);
		}
	}
	steamapi_initcount += 1;
	return init_result;
}

void SteamAPI_RunCallbacks()
{
	if (steamapi_ptrs.RunCallbacks)
	{
		steamapi_ptrs.RunCallbacks();
	}
}

void SteamAPI_Shutdown()
{
	if (steamapi_initcount != 0)
	{
		steamapi_initcount -= 1;
		if (steamapi_initcount == 0)
		{
			if (steamapi_ptrs.Shutdown)
			{
				steamapi_ptrs.Shutdown();
			}
			memset(&steamapi_ptrs, 0, sizeof(steamapi_ptrs));
			memset(&steamapi_interfaces, 0, sizeof(steamapi_ptrs));
			if (steamapi_lib != NULL)
			{
				FreeLibrary(steamapi_lib);
				steamapi_lib = NULL;
			}
		}
	}
}

void SteamAPI_RegisterCallback(class CCallbackBase *pCallback, int iCallback)
{
	if (steamapi_ptrs.RegisterCallback)
	{
		steamapi_ptrs.RegisterCallback(pCallback, iCallback);
	}
}

void SteamAPI_UnregisterCallback(class CCallbackBase *pCallback)
{
	if (steamapi_ptrs.UnregisterCallback)
	{
		steamapi_ptrs.UnregisterCallback(pCallback);
	}
}

ISteamApps* SteamApps()
{
	return steamapi_interfaces.apps;
}

ISteamRemoteStorage* SteamRemoteStorage()
{
	return steamapi_interfaces.remotestorage;
}

ISteamScreenshots* SteamScreenshots()
{
	return steamapi_interfaces.screenshots;
}

ISteamUser* SteamUser()
{
	return steamapi_interfaces.user;
}

ISteamUserStats* SteamUserStats()
{
	return steamapi_interfaces.userstats;
}

ISteamUtils* SteamUtils()
{
	return steamapi_interfaces.utils;
}

ISteamVideo* SteamVideo()
{
	return steamapi_interfaces.video;
}
