#include "RegistryManager.h"
#include <iostream>
#include <vector>
#include <Windows.h>

RegistryManager::RegistryManager(HKEY rootKey)
    : m_rootKey(rootKey)
    , m_statusCode(ERROR_SUCCESS)
{
}

void RegistryManager::createKey(const std::string& path)
{
    HKEY hkey;
    LONG reg = RegCreateKeyExA(
        m_rootKey, // Use the member variable m_rootKey instead of a hardcoded key
        path.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
        &hkey, NULL);

    if (reg == ERROR_SUCCESS) {
        std::cout << "Registry key created successfully." << std::endl;
    } else {
        std::cout << "Failed to create registry key. Error code: " << reg
                  << std::endl;
    }

    RegCloseKey(hkey);

    m_statusCode = reg;
}

// Creates a string value vector
void RegistryManager::createVec(const std::string& path,
    const std::vector<BYTE>& data,
    const std::string& valName)
{
    HKEY hkey;
    LONG reg = openKey(path, KEY_ALL_ACCESS, &hkey);

    if (reg == ERROR_SUCCESS) {
        reg = RegSetValueExA(hkey, valName.c_str(), 0, REG_BINARY, data.data(),
            static_cast<DWORD>(data.size()));

        if (reg == ERROR_SUCCESS) {
            std::cout << "Registry value has been edited successfully." << std::endl;
        } else {
            std::cout << "Failed to edit registry value. Error code: " << reg
                      << std::endl;
        }
    } else {
        std::cout << "Failed to open registry key. Error code: " << reg
                  << std::endl;
    }

    closeKey(hkey);

    m_statusCode = reg;
}

void RegistryManager::deleteVal(const std::string& path,
    const std::string& valName)
{
    HKEY hkey;
    LONG reg = openKey(path, KEY_ALL_ACCESS, &hkey);

    if (reg == ERROR_SUCCESS) {
        reg = RegDeleteValueA(hkey, valName.c_str());

        if (reg == ERROR_SUCCESS) {
            std::cout << "Registry value has been deleted successfully." << std::endl;
        } else {
            std::cout << "Failed to delete registry value. Is it already deleted? "
                         "Error code: "
                      << reg << std::endl;
        }
    } else {
        std::cout << "Failed to open registry key. Error code: " << reg
                  << std::endl;
    }

    closeKey(hkey);

    m_statusCode = reg;
}

void RegistryManager::deleteKey(const std::string& path)
{
    LONG reg = RegDeleteKeyA(m_rootKey, path.c_str());

    if (reg == ERROR_SUCCESS) {
        std::cout << "Registry key has been deleted successfully." << std::endl;
    } else {
        std::cout << "Failed to delete registry key. Error code: " << reg
                  << std::endl;
    }

    m_statusCode = reg;
}

LONG RegistryManager::getStatusCode()
{
    return m_statusCode;
}

LONG RegistryManager::openKey(const std::string& subKey, REGSAM rights,
    HKEY* resultKey)
{
    return RegOpenKeyExA(
        m_rootKey, // Use the member variable m_rootKey instead of a hardcoded key
        subKey.c_str(), 0, rights, resultKey);
}

void RegistryManager::closeKey(HKEY hKey) { RegCloseKey(hKey); }
