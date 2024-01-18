#ifndef MOUSETWEAKS_H
#define MOUSETWEAKS_H

#include "RegistryManager.h"
#include <string>
#include <Windows.h>

class MouseTweaks {
public:
    // Default/Recommended Data Queue size is 20
    LONG applyDataQueue(DWORD buffer = 20);
    LONG applyBoostCsrss();
    LONG revertDataQueue();
    LONG revertBoostCsrss();
};

#endif // MOUSETWEAKS_H
