#pragma once
#ifdef WIN32
#include <System/DiscordRPC/discord.h>
#include <string>
#include <direct.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <System/Window.h>


namespace Discord {
    #pragma pack(push, 1)
    struct BitmapImageHeader {
        uint32_t const structSize{sizeof(BitmapImageHeader)};
        int32_t width{0};
        int32_t height{0};
        uint16_t const planes{1};
        uint16_t const bpp{32};
        uint32_t const pad0{0};
        uint32_t const pad1{0};
        uint32_t const hres{2835};
        uint32_t const vres{2835};
        uint32_t const pad4{0};
        uint32_t const pad5{0};

        BitmapImageHeader& operator=(BitmapImageHeader const&) = delete;
    };

    struct BitmapFileHeader {
        uint8_t const magic0{'B'};
        uint8_t const magic1{'M'};
        uint32_t size{0};
        uint32_t const pad{0};
        uint32_t const offset{sizeof(BitmapFileHeader) + sizeof(BitmapImageHeader)};

        BitmapFileHeader& operator=(BitmapFileHeader const&) = delete;
    };
    #pragma pack(pop)

    struct DiscordState {
        discord::User currentUser;

        std::unique_ptr<discord::Core> core;
    };

    static std::thread discordThread;
    static DiscordState state;
    static discord::Core* core = 0;

    void CallbackThread(const Engine::Window& _w)
    {
        discordThread = std::thread([&] {
            while(_w.isOpen())
            {
                state.core->RunCallbacks();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
    }

    void init(const char* exename, const char* _type, const char* _detail)
    {

        auto res = discord::Core::Create(1094264443577303090, DiscordCreateFlags_Default, &core);
        state.core.reset(core);

        if(!state.core) {
            std::cerr << "Failed discord core: " << (int)res << "\n";
        }

        state.core->SetLogHook(
            discord::LogLevel::Debug, [](discord::LogLevel level, const char* message) {
                std::cerr << "Log(" << static_cast<uint32_t>(level) << "): " << message << "\n";
        });

        std::string path_to_program = _getcwd(NULL, 0);
        path_to_program += "\\";
        path_to_program += exename;

        std::string _state = _type;
        _state += "::";
        _state += _detail;

        state.core->ActivityManager().RegisterCommand(path_to_program.c_str());
        discord::Activity activity{};
        activity.SetDetails("Test build");
        activity.SetState(_state.c_str());
        activity.SetType(discord::ActivityType::Playing);

        activity.GetAssets().SetSmallImage("status");
        activity.GetAssets().SetSmallText("Помоги");
        activity.GetAssets().SetLargeImage("ava");
        // activity.GetAssets().SetLargeText("yeah");

        activity.GetTimestamps().SetStart(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()*1000);

        state.core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
            if(result != discord::Result::Ok) std::cout << "Failed update activity discord: " << (int)result << "\n";
            else std::cout << "Update activity discord ok";
        });
    }
}
#else
#include <System/Window.h>
namespace Discord {

    void CallbackThread(const Engine::Window& _w) {}
    void init(const char* exename, const char* _type, const char* _detail){}
}

#endif