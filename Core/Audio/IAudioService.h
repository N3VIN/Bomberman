#pragma once
#include <filesystem>

namespace fs = std::filesystem;

namespace dae {
    using SoundID = uint32_t; // this is the 32 bit version of the hashing function

    // i dont understand this blackmagic but a search for a simple branchless compile time hash function leads to this
    // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash
    consteval SoundID HashSoundID(std::string_view s) {
        SoundID h = 2166136261u;
        for (const char c: s) {
            h ^= static_cast<SoundID>(c);
            h *= 16777619u;
        }

        return h;
    }

    class IAudioService {
    public:
        virtual ~IAudioService() = default;

        virtual void LoadAudio(SoundID id, fs::path path) = 0;
        virtual void PlayAudio(SoundID id, float volume) = 0;
        virtual void StopAudio(SoundID id) = 0;
    };
}
