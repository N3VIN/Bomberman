#pragma once
#include "AudioService.h"

namespace dae {
    class SDLAudioService final : public AudioService {
    public:
        SDLAudioService();
        ~SDLAudioService() override;

        SDLAudioService(const SDLAudioService &) = delete;
        SDLAudioService &operator=(const SDLAudioService &) = delete;
        SDLAudioService(SDLAudioService &&) noexcept;
        SDLAudioService &operator=(SDLAudioService &&) noexcept;

        void LoadAudio(SoundID id, fs::path path) override;
        void PlayAudio(SoundID id, float volume) override;
        void StopAudio(SoundID id) override;

    private:
        class SDLAudioImpl;
        std::unique_ptr<SDLAudioImpl> pImpl;
    };
}
