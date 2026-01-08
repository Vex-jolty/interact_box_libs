# Interact Box Libraries

This repository contains the code for the libraries Interact Box and its auxiliary programs require to function.

For now, the only officially supported compiler is MinGW, specifically with MSVCRT, as this project was cross-compiled from Arch Linux.

While contributions to add support to other compilers, such as MSVC and Clang, are more than welcome, please make sure to specify the exact version you used, along with any specific modifications such as custom toolchains or libraries. Otherwise, it'll be very difficult for me to ensure your code is indeed compatible with the project.

This project makes use of the [pthread9x library](https://github.com/JHRobotics/pthread9x) for Windows 98 through XP, and [dotnet9x](https://github.com/itsmattkc/dotnet9x) for Windows 98 and ME.

Support for versions older than Windows 98 is not currently planned.
