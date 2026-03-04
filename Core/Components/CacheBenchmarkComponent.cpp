#include "CacheBenchmarkComponent.h"

#include <algorithm>
#include <chrono>
#include <numeric>

#include <imgui.h>
#include <imgui_plot.h>

namespace dae {
    CacheBenchmarkComponent::CacheBenchmarkComponent(GameObject *owner)
        : Component(owner) {}

    template<typename T>
    std::vector<CacheBenchmarkComponent::BenchmarkResult> CacheBenchmarkComponent::RunBenchmark() {
        constexpr int size = 10'000'000;
        const auto buffer = new T[size];

        std::vector<BenchmarkResult> results;
        std::vector<float> timings;

        for (int stepSize = 1; stepSize <= 1024; stepSize *= 2) {
            timings.clear();

            for (int run = 0; run < 10; run++) {
                const auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < size; i += stepSize) {
                    buffer[i].id *= 2;
                }
                const auto end = std::chrono::high_resolution_clock::now();
                const float elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.f;
                timings.push_back(elapsed);
            }

            // remove outliers
            std::ranges::sort(timings);
            timings.erase(timings.begin());
            timings.pop_back();

            const float sum = std::accumulate(timings.begin(), timings.end(), 0.0f);
            const float avg = sum / static_cast<float>(timings.size());

            results.push_back({stepSize, avg});
        }

        delete[] buffer;
        return results;
    }

    void CacheBenchmarkComponent::Update(float /*deltaTime*/) {
        if (!m_benchmarkRequested)
            return;

        m_results = RunBenchmark<GameObject3D>();
        m_resultsPtr = RunBenchmark<GameObject3DAlt>();

        m_timings.clear();
        m_timingsPtr.clear();
        m_stepLabels.clear();

        for (size_t i = 0; i < m_results.size(); i++) {
            m_timings.push_back(m_results[i].avgTimeMs);
            m_timingsPtr.push_back(m_resultsPtr[i].avgTimeMs);
            m_stepLabels.push_back(static_cast<float>(m_results[i].stepSize));
        }

        m_benchmarkDone = true;
        m_benchmarkRequested = false;
    }

    void CacheBenchmarkComponent::Render() const {
        ImGui::Begin("Cache Benchmark");

        if (!m_benchmarkDone && !m_benchmarkRequested) {
            if (ImGui::Button("Run Benchmark")) {
                m_benchmarkRequested = true;
            }
        }
        else {
            if (ImGui::Button("Re-run Benchmark")) {
                m_benchmarkRequested = true;
                m_benchmarkDone = false;
            }

            ImGui::Text("Results (step size vs avg time in ms):");

            if (ImGui::BeginTable("BenchResults", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
                ImGui::TableSetupColumn("Step Size");
                ImGui::TableSetupColumn("Object (ms)");
                ImGui::TableSetupColumn("Pointer (ms)");
                ImGui::TableHeadersRow();

                for (size_t i = 0; i < m_results.size(); i++) {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::Text("%d", m_results[i].stepSize);
                    ImGui::TableNextColumn();
                    ImGui::Text("%.2f", m_results[i].avgTimeMs);
                    ImGui::TableNextColumn();
                    ImGui::Text("%.2f", m_resultsPtr[i].avgTimeMs);
                }
                ImGui::EndTable();
            }

            ImGui::Spacing();

            if (!m_timings.empty()) {
                const float maxObj = *std::ranges::max_element(m_timings);
                const float maxPtr = *std::ranges::max_element(m_timingsPtr);
                const float maxVal = std::max(maxObj, maxPtr);

                const float *ysList[] = {m_timings.data(), m_timingsPtr.data()};
                const ImU32 colors[] = {ImColor(0, 255, 0), ImColor(255, 80, 80)};

                ImGui::PlotConfig conf{};
                conf.values.xs = m_stepLabels.data();
                conf.values.ys_list = ysList;
                conf.values.ys_count = 2;
                conf.values.colors = colors;
                conf.values.count = static_cast<int>(m_timings.size());
                conf.scale.min = 0;
                conf.scale.max = maxVal * 1.1f;
                conf.tooltip.show = false;
                conf.grid_y.show = true;
                conf.grid_y.size = maxVal / 5.f;
                conf.frame_size = ImVec2(400, 200);
                conf.line_thickness = 2.f;

                ImGui::Plot("cache_plot", conf);

                ImGui::TextColored(ImVec4(0, 1, 0, 1), "Green: Object Transform");
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 0.3f, 0.3f, 1), "Red: Pointer Transform");
            }
        }

        ImGui::End();
    }
} // dae
