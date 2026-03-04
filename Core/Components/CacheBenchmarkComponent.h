#pragma once
#include "Component.h"
#include <vector>

namespace dae {
    struct TransformAlt {
        float matrix[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
    };

    struct GameObject3D {
        TransformAlt transform;
        int id;
    };

    struct GameObject3DAlt {
        TransformAlt *transform;
        int id;
    };

    class CacheBenchmarkComponent final : public Component {
    public:
        explicit CacheBenchmarkComponent(GameObject *owner);

        void Update(float deltaTime) override;
        void Render() const override;

    private:
        struct BenchmarkResult {
            int stepSize;
            float avgTimeMs;
        };

        template<typename T>
        std::vector<BenchmarkResult> RunBenchmark();

        std::vector<BenchmarkResult> m_results;
        std::vector<float> m_timings;
        std::vector<float> m_stepLabels;

        std::vector<BenchmarkResult> m_resultsPtr;
        std::vector<float> m_timingsPtr;

        mutable int m_samples = 10;

        mutable bool m_benchmarkDone = false;
        mutable bool m_benchmarkRequested = false;
    };
} // dae
