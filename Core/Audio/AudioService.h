#pragma once
#include <string_view>

namespace fs = std::filesystem;

namespace dae {
    using SoundID = unsigned short;

    class AudioService {
    public:
        virtual ~AudioService() = default;

        virtual void LoadAudio(SoundID id, fs::path path) = 0;
        virtual void PlayAudio(SoundID id, float volume) = 0;
        virtual void StopAudio(SoundID id) = 0;
    };
}
