#ifndef REGISTRY_MANAGER_H
#define REGISTRY_MANAGER_H

#include <iostream>
#include <vector>
#include <Windows.h>

class RegistryManager {
public:
    explicit RegistryManager(HKEY rootKey = HKEY_CURRENT_USER); // Constructor with default root key
    void createKey(const std::string& path);
    void createVec(const std::string& path, const std::vector<BYTE>& data, const std::string& valName = "");
    void deleteVal(const std::string& path, const std::string& valName);
    void deleteKey(const std::string& path);
    LONG getStatusCode();

    template <typename T>
    void createVal(const std::string& path, const T data, const std::string& valName = "");

private:
    HKEY m_rootKey; // Member variable to store the root key
    LONG m_statusCode; // Member variable to store the status code
    LONG openKey(const std::string& subKey, REGSAM rights, HKEY* resultKey);
    void closeKey(HKEY hKey);
};

// Accepts char* or DWORD values for data
// char* values are saved as REG_SZ type
// DWORD values are saved as REG_DWORD type
template <typename T>
void RegistryManager::createVal(const std::string& path, const T data, const std::string& valName)
{
    HKEY hkey;
    LONG reg = openKey(path, KEY_ALL_ACCESS, &hkey);
    DWORD type;
    LPCVOID pData;
    DWORD dataSize;

    if constexpr (std::is_same_v<T, const char*> || std::is_same_v<T, char*>) {
        type = REG_SZ;
        pData = reinterpret_cast<const BYTE*>(data);
        dataSize = static_cast<DWORD>(strlen(data) + 1);

    } else if constexpr (std::is_same_v<T, DWORD>) {
        type = REG_DWORD;
        pData = reinterpret_cast<const BYTE*>(&data);
        dataSize = sizeof(DWORD);

    } else {
        // This will only cause a compile-time error if T is not char* or DWORD
        static_assert(std::is_same_v<T, const char*> || std::is_same_v<T, char*> || std::is_same<T, DWORD>::value,
            "This value type is not supported.");
    }

    if (reg == ERROR_SUCCESS) {
        reg = RegSetValueExA(hkey, valName.c_str(), 0, type,
            static_cast<const BYTE*>(pData), dataSize);

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

#endif // REGISTRY_MANAGER_H
