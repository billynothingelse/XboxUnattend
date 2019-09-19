#include <iostream>
#include "UnattendedUtilities.h"

#define CMD_USB "-usb"
#define CMD_SCRIPT "-script"

#define CMD_DESC_USB "xboxunattend.exe -usb"
#define CMD_DESC_SCRIPT "xboxunattend.exe -script D:\\DevelopmentFiles\\MyScript.cmd"

constexpr wchar_t g_szDefaultLogPath[] = L"D:\\boot\\result.txt";

int main(int argc, const char* argv[])
{
    HRESULT hResult = S_OK;
    IUnattendedUtilitiesStatics* pUnattend = nullptr;
    HSTRING hStrRuntimeClass = 0;
    HSTRING hStrScriptPath = 0;
    HSTRING hStrScriptOutput = 0;
    HSTRING hStrScriptLogPath = 0;
    HSTRING_HEADER hStrHeader = { 0 };
    HRESULT hScriptResult = 0;
    const wchar_t* szScriptOutput;
    wchar_t szScriptFilePath[WCHAR_MAX];
    UINT32 nScriptFilePathLength = 0;
    bool bUseUSB = false;

    if (argc < 2) {
        printf("Usage:\n[%s] %s\n[%s] %s\n", CMD_USB, CMD_DESC_USB, CMD_SCRIPT, CMD_DESC_SCRIPT);
        return 1;
    }

    //
    // Initialize WinRT
    //
    hResult = RoInitialize(RO_INIT_SINGLETHREADED);
    if (hResult != S_OK) {
        printf("Failed to initialize WinRT: %d\n", GetLastError());
        return hResult;
    }

    printf("Initialized WinRT!\n");

    hResult = WindowsCreateStringReference(RuntimeClass_UnattendedUtilities, static_cast<UINT32>(wcslen(RuntimeClass_UnattendedUtilities)), &hStrHeader, &hStrRuntimeClass);
    if (hResult != S_OK) {
        printf("Failed to create string reference: %d\n", GetLastError());
        return hResult;
    }

    //
    // Activate UnattendedUtilities interface
    //
    hResult = RoGetActivationFactory(hStrRuntimeClass, IID_IUnattendedUtilitiesStatics, reinterpret_cast<void**>(&pUnattend));
    if (hResult != S_OK) {
        printf("Failed to activate class: %d\n", GetLastError());
        return hResult;
    }

    printf("Activated class instance!\n");

    //
    // Parse command line arguments
    //
    if (strncmp(CMD_USB, argv[1], strlen(CMD_USB)) == 0) {
        bUseUSB = true;
    } else if (strncmp(CMD_SCRIPT, argv[1], strlen(CMD_SCRIPT)) == 0) {
        size_t nSize = strlen(argv[2]);
        size_t nLength = 0;
        mbstowcs_s(&nLength, szScriptFilePath, argv[2], nSize + 1);
        nScriptFilePathLength = static_cast<UINT32>(wcslen(szScriptFilePath));
    }

    if (bUseUSB) {
        boolean bUsbScriptExists = false;

        // Make sure we have a script to run
        hResult = pUnattend->HasUnattendedScriptOnUsb(&bUsbScriptExists);
        if (hResult != S_OK) {
            printf("HasUnattendedScriptOnUsb(...) failed: %d\n", GetLastError());
            return hResult;
        }

        if (bUsbScriptExists != 1) {
            printf("No script found on device!\nPlease place an unattend script on the root of your USB\n");
            return 1;
        }

        printf("Script found. Preparing to run...\n");

        // Run script and receive the output result
        hResult = pUnattend->RetrieveAndRunUnattendedScript(&hScriptResult, &hStrScriptOutput);
        if (hResult != S_OK) {
            printf("RetrieveAndRunUnattendedScript(...) failed: %d\n", GetLastError());
            return hResult;
        }

        UINT32 nLength = 0;
        szScriptOutput = WindowsGetStringRawBuffer(hStrScriptOutput, &nLength);
        if (nLength > 0) {
            printf("Result: %d\n", hScriptResult);
            wprintf(L"Output: %s\n", szScriptOutput);
        }

        return hResult;
    }

    HSTRING_HEADER hStrHdr2;
    hResult = WindowsCreateStringReference(szScriptFilePath, nScriptFilePathLength, &hStrHdr2, &hStrScriptPath);
    if (hResult != S_OK) {
        printf("Failed to create string reference for path: %d\n", GetLastError());
        return 1;
    }

    HSTRING_HEADER hStrHdr3;
    hResult = WindowsCreateStringReference(g_szDefaultLogPath, static_cast<UINT32>(wcslen(g_szDefaultLogPath)), &hStrHdr3, &hStrScriptLogPath);
    if (hResult != S_OK) {
        printf("Failed to create string reference for log path: %d\n", GetLastError());
        return 1;
    }

    //
    // Execute our script
    //
    hResult = pUnattend->RunUnattendedScript(hStrScriptPath, hStrScriptLogPath, &hScriptResult, &hStrScriptOutput);
    if (hResult != S_OK) {
        printf("RunUnattendedScript(...) failed: %d\n", GetLastError());
        printf("Last result: %d\n", hResult);
        return hResult;
    }

    printf("Running unattended script.\n");

    UINT32 nLength = 0;
    szScriptOutput = WindowsGetStringRawBuffer(hStrScriptOutput, &nLength);
    printf("Result: %d\n", hScriptResult);
    wprintf(L"Output: %s\n", szScriptOutput);

    return hResult;
}