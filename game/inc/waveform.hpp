#pragma once
#ifndef WAVEFORM_HPP
#define WAVEFORM_HPP

#include <stdint.h>
#include <cmath>
#include <stdexcept>

namespace render {

class Waveform {
public:
    Waveform(size_t sample_rate, double duration):
        m_sr{sample_rate},
        m_dt{1.0/sample_rate},
        m_buffer_length{size_t(std::ceil(duration*sample_rate))},
        m_buffer{new double[m_buffer_length]}
    {
        for (auto i=0; i < m_buffer_length; i++) { m_buffer[i] = 0; }
    }

    ~Waveform() {
        delete [] m_buffer;
    }

    void superposition(double start_time, double (*generate)(double t, bool& finished)) {
        size_t idx = std::round(start_time/m_sr);
        bool finished = false;
        double t = 0.0;
        while (!finished && idx < m_buffer_length) {
            m_buffer[idx++] += generate(t, finished);
            t += m_dt;
        }
    }

    Waveform& operator+(const Waveform& wav) {
        if (wav.m_buffer_length != m_buffer_length) {
            throw (std::length_error("Waveforms must be of the identical dimensionality to be added"));
        }
        for (auto idx=0; idx < m_buffer_length; idx++) {
            m_buffer[idx] += wav.m_buffer[idx];
        }
        return *this;
    }

    template <typename T>
    Waveform& operator+(T value) {
        for (auto idx=0; idx < m_buffer_length; idx++) {
            m_buffer[idx] += value;
        }
        return *this;
    }

    Waveform& operator-(const Waveform& wav) {
        if (wav.m_buffer_length != m_buffer_length) {
            throw (std::length_error("Waveforms must be of the identical dimensionality to be added"));
        }
        for (auto idx=0; idx < m_buffer_length; idx++) {
            m_buffer[idx] -= wav.m_buffer[idx];
        }
        return *this;
    }

    template <typename T>
    Waveform& operator-(T value) {
        for (auto idx=0; idx < m_buffer_length; idx++) {
            m_buffer[idx] -= value;
        }
        return *this;
    }

    Waveform& operator*(const Waveform& wav) {
        if (wav.m_buffer_length != m_buffer_length) {
            throw (std::length_error("Waveforms must be of the identical dimensionality to be added"));
        }
        for (auto idx=0; idx < m_buffer_length; idx++) {
            m_buffer[idx] *= wav.m_buffer[idx];
        }
        return *this;
    }

    template <typename T>
    Waveform& operator*(T value) {
        for (auto idx=0; idx < m_buffer_length; idx++) {
            m_buffer[idx] *= value;
        }
        return *this;
    }

    Waveform& operator/(const Waveform& wav) {
        if (wav.m_buffer_length != m_buffer_length) {
            throw (std::length_error("Waveforms must be of the identical dimensionality to be added"));
        }
        for (auto idx=0; idx < m_buffer_length; idx++) {
            m_buffer[idx] /= wav.m_buffer[idx];
        }
        return *this;
    }

    template <typename T>
    Waveform& operator/(T value) {
        for (auto idx=0; idx < m_buffer_length; idx++) {
            m_buffer[idx] /= value;
        }
        return *this;
    }



private:
    size_t m_sr;
    double m_dt;
    size_t m_buffer_length;
    double* m_buffer;


};

};

#endif