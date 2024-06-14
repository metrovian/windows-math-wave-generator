#include "MelodyFunction.h"
#include "Predefined.h"

bool MelodyFunction::isPlayable()
{
    if (pitch.size() != beat.size()) return false;
    if (dynamic.size() != beat.size()) return false;
    if (dynamic.size() < 1) return false;

    return true;
}

WaveFunction MelodyFunction::getWaveFunction(WaveFunction(*_wave)(double _namp, double _freq, double _dura))
{
    assert(isPlayable());

    WaveFunction ret = _wave(dynamic[0], pitch[0], beat[0]);
    for (int i = 1; i < dynamic.size(); i++)
    {
        ret = ret & _wave(dynamic[i], pitch[i], beat[i]);
    }
    
    return ret;
}

WaveFunction MelodyFunction::getWaveFunction(FourierFunction(*_wave)(double _namp, double _freq, double _dura))
{
    assert(isPlayable());

    typedef WaveFunction (*FuncPtr)(double, double, double);
    return getWaveFunction(reinterpret_cast<FuncPtr>(_wave));
}

MelodyFunction MelodyFunction::over_the_rainbow(double _bpm)
{
    MelodyFunction ret;
    
    ret.pitch =
    {
        C4, C5,
        B4, G4, A4, B4, C5,
        C4, A4,
        G4, Z0,
        A3, F4,
        E4, C4, D4, E4, F4,
        D4, B3, C4, D4, E4,
        C4, Z0,

        C4, C5,
        B4, G4, A4, B4, C5,
        C4, A4,
        G4, Z0,
        A3, F4,
        E4, C4, D4, E4, F4,
        D4, B3, C4, D4, E4,
        C4, Z0,
    };

    ret.beat =
    {
        2.0, 2.0,
        1.0, 0.5, 0.5, 1.0, 1.0,
        2.0, 2.0,
        3.0, 1.0,
        2.0, 2.0,
        1.0, 0.5, 0.5, 1.0, 1.0,
        1.0, 0.5, 0.5, 1.0, 1.0,
        3.0, 1.0,

        2.0, 2.0,
        1.0, 0.5, 0.5, 1.0, 1.0,
        2.0, 2.0,
        3.0, 1.0,
        2.0, 2.0,
        1.0, 0.5, 0.5, 1.0, 1.0,
        1.0, 0.5, 0.5, 1.0, 1.0,
        3.0, 1.0,
    };

    for (auto& pt : ret.beat)
    {
        ret.dynamic.push_back(0.02);
        pt *= 60.0 / _bpm;
    }
    
    return ret;
}