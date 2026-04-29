#pragma once
#include "IAudioService.h"

namespace dae {
    class NullAudioService final : public IAudioService {
    public:
        void LoadAudio(SoundID id, fs::path path) override {}
        void PlayAudio(SoundID id, float volume) override {}
        void StopAudio(SoundID id) override {}
    };
}
