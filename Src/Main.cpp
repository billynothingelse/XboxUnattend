#include <iostream>
#include "UnattendedUtilities.h"

int main(int argc, const char* argv[])
{
    HRESULT hResult = S_OK;
    IUnattendedUtilitiesStatics* pUnattend = nullptr;
    HSTRING hStrRuntimeClass = 0;
    HSTRING_HEADER hStrHeader = { 0 };

    //
    // Initialize WinRT
    //
    hResult = RoInitialize(RO_INIT_SINGLETHREADED);
    if (hResult != S_OK)
    {
        printf("Failed to initialize WinRT: %d\n", GetLastError());
        return hResult;
    }

    printf("Initialized WinRT!\n");

    UINT32 nLength = wcslen(RuntimeClass_UnattendedUtilities);
    hResult = WindowsCreateStringReference(RuntimeClass_UnattendedUtilities, nLength, &hStrHeader, &hStrRuntimeClass);
    if (hResult != S_OK)
    {
        printf("Failed to create string reference: %d\n", GetLastError());
        return hResult;
    }

    //
    // Activate UnattendedUtilities interface
    //
    hResult = RoGetActivationFactory(hStrRuntimeClass, IID_IUnattendedUtilitiesStatics, reinterpret_cast<void**>(&pUnattend));
    if (hResult != S_OK)
    {
        printf("Failed to activate class: %d\n", GetLastError());
        return hResult;
    }

    printf("Activated class instance!\n");

    //
    // Execute our script
    //
    hResult = pUnattend->RunUnattendedScriptOnUsbAsync();
    if (hResult != S_OK)
    {
        printf("Failed to execute unattended script!\n");
        return hResult;
    }

    printf("Executed script!\n");

    //
    // Cleanup
    //
    hResult = WindowsDeleteString(hStrRuntimeClass);
    if (hResult != S_OK)
    {
        printf("Failed to delete string reference: %d\n", GetLastError());
        return hResult;
    }

    return hResult;
}