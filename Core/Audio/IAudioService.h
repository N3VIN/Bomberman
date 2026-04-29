#pragma once
#include <filesystem>

namespace fs = std::filesystem;

namespace dae {
    using SoundID = unsigned short;

    class IAudioService {
    public:
        virtual ~IAudioService() = default;

        virtual void LoadAudio(SoundID id, fs::path path) = 0;
        virtual void PlayAudio(SoundID id, float volume) = 0;
        virtual void StopAudio(SoundID id) = 0;
    };
}
