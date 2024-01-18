#ifndef MARKC_H
#define MARKC_H
#include "RegistryManager.h"
#include <string>
#include <vector>
#include <Windows.h>

// Declaration of an enum class named Scale
// Each member represents a different scaling factor
enum class Scale {
    Default,
    Scale100,
    Scale125,
    Scale150,
    Scale175,
    Scale200,
    Scale225,
    Scale250,
    Scale300,
    Scale350
};

class MouseScaleFix {
public:
    MouseScaleFix(Scale scale = Scale::Default)
        : m_scale(scale)
    {
    } // Default constructor
    LONG applyMouseFix();
    void setScale(Scale newScale) { m_scale = newScale; }

private:
    // Member variable to store the current scale
    Scale m_scale;

    LONG setScale100();
    LONG setScale125();
    LONG setScale150();
    LONG setScale175();
    LONG setScale200();
    LONG setScale225();
    LONG setScale250();
    LONG setScale300();
    LONG setScale350();
    LONG setScaleDefault();
    LONG applyMarkC(const std::vector<BYTE>& xData, const std::vector<BYTE>& yData, const char* scale = "(Default)");
};

#endif // MARKC_H
