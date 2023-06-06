#pragma once
#ifdef WIN32
#include <System/DiscordRPC/discord_rpc.h>
#include <string>
#include <direct.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <System/Window.h>


namespace Discord {
    std::thread _discordThread;

    void CallbackThread(const Engine::Window& _w)
    {
        _discordThread = std::thread([&]{
            while(_w.isOpen())
            {
                Discord_RunCallbacks();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            Discord_Shutdown();
        });
    }

    void init(const char* exename, const char* _type, const char* _detail)
    {
        DiscordEventHandlers _handles;
        DiscordRichPresence _presence;

        memset((void*)&_handles, 0, sizeof(_handles));
        memset((void*)&_presence, 0, sizeof(_presence));

        std::string _state = _type;
        _state += "::";
        _state += _detail;

        _presence.startTimestamp = (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()*1000);
        _presence.smallImageKey = "statusnow";
        _presence.smallImageText = "Помоги";
        _presence.largeImageKey = "avatar";
#ifdef DEBUG
        _presence.details = "Debug build";
#else
        _presence.details = "Release build";
#endif
        _presence.state = _state.c_str();
        _presence.button1_label = "Discord";
        _presence.button1_url = "https://discord.gg/zFDNYNyCBa";
        _presence.button2_label = "Github";
        _presence.button2_url = "https://github.com/Fluiser/freakworld-githubt";

        Discord_Initialize("1094264443577303090", &_handles, 1, nullptr);
        Discord_UpdatePresence(&_presence);
    }
}
#else
#include <System/Window.h>
namespace Discord {
    void CallbackThread(const Engine::Window& _w) {}
    void init(const char* exename, const char* _type, const char* _detail){}
}

#endif
