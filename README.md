# XboxUnattend
Run unattended scripts at the highest privilege level.

## Usage
```
xboxunattend.exe -usb - Run an unattended script located on the root of USB device
xboxunattend.exe -script <Script File Path> - Run a script from file path
```

See: https://wiki.xosft.dev/index.php?title=Setup_Dev_Mode#Using_SSH

## How does it work?
Every Xbox One development kits contain the same developer tools environment has features that are common regardless of capability certificate but some 
applications will hide certain features intended for other development kit types. The feature this tool focuses on is known as "Unattended Utilities". It's a WinRT
interface that is intended for use by ERA kits for tools automation. While this feature is "hidden" by the Dev Home application and is not configured correctly via 
the Xbox Device Portal for UWA/SRA kits, we can still fortunately utilise this component manually via WinRT.

## What is an 'unattended' script?
An unattended script is just a fancier name for a simple batch script.

## References
* https://conference.hitb.org/files/hitbsecconf2018pek/materials/D1T2%20-%20The%20Inner%20Workings%20of%20the%20Windows%20Runtime%20-%20James%20Forshaw.pdf
* https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/intro-to-using-cpp-with-winrt
* https://docs.microsoft.com/en-us/windows/win32/learnwin32/what-is-a-com-interface-