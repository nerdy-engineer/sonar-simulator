#pragma once
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <memory>
#include <thread>
#include "scene.hpp"
#include "waveform.hpp"
#include "caster.hpp"


namespace render {


class SonarRenderer {
public:
    SonarRenderer(size_t sample_rate, double max_distance, std::shared_ptr<Scene> scene) :
        m_scene{scene},
        m_sample_rate{sample_rate},
        m_max_distance{max_distance}
    {

    }

    void render(Caster& caster, size_t parallel_threads=4) {
        std::vector<std::pair<std::thread, Waveform>> wavs{parallel_threads};
        double duration = m_max_distance/m_scene->environment().atmosphere.speed_of_sound;
        for (auto& pair : wavs) {
            pair.second = Waveform{m_sample_rate, duration};
            // Waveform have been created, now dispatch threads to render to them
            // We need a way to divy up the rays between render threads
            pair.first = std::thread([this](Caster raycaster, Waveform& destination){this->render_thread(raycaster, destination);}, caster, pair.second);

        }
    }

    void render_thread(Caster& raycaster, Waveform& destination) {
        // We need to generate the rays to send to the caster based on an observer object
        // But we need to define the observers and an illuminator too.
    }


private:
    std::shared_ptr<Scene> m_scene;
    size_t m_sample_rate;
    double m_max_distance;


};



}

#endif // RENDERER_HPP