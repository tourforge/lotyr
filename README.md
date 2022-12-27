# Lotyr
[![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/opentourbuilder/lotyr/CICD.yml?style=for-the-badge)](https://github.com/evresi/lotyr/actions/workflows/CICD.yml)

A thin wrapper around [Valhalla](https://github.com/valhalla/valhalla) that statically links all
dependencies and provides a simple C API for querying the Valhalla API within a single process.
You can use exactly the same JSON routing API as you would if you were connecting to a Valhalla
server over a network.

Current limitations:
- Only Windows, MacOS, and Linux builds are supported right now. Android builds should be pretty
  easy to implement, and iOS should also be possible.
- Only the routing API endpoint is usable from the library. Support for more of the endpoints can
  be very easily added.

## Building
### Linux
1. Install a C/C++ compiler, Git, and CMake.

   Example - Ubuntu:
   ```sh
   sudo apt update
   sudo apt upgrade
   sudo apt install build-essential git cmake
   ```
   
   Example - Fedora:
   ```sh
   sudo dnf groupinstall "Development Tools" "Development Libraries"
   sudo dnf install gcc-c++ cmake
   ```
   
   Example - Arch Linux:
   ```sh
   sudo pacman -Syu base-devel git cmake
   ```
2. Download [Boost](https://www.boost.org/users/download/) and extract it somewhere (example: `$HOME/Downloads/boost_1_80_0`)
3. Clone and change directory to the repository by running the following commands in a terminal:
   ```sh
   git clone https://github.com/evresi/lotyr
   cd lotyr
   git submodule update --init --recursive
   ```
5. Build Lotyr by running the following commands in the same terminal:
   ```sh
   cmake -B build -DCMAKE_BUILD_TYPE=Release -DBOOST_ROOT=$HOME/Downloads/boost_1_80_0
   make -C build
   ```
   Don't forget to replace `$HOME/Downloads/boost_1_80_0` with where you extracted Boost if you extracted it elsewhere.
   
   Tip: to speed up compilation, you can add `-jX` to the end of the `make` command, where X is the number of physical
   CPU cores you have. If you're not sure how many you have, you can add `-j$(nproc)` instead, which should still be faster.

### MacOS
1. Install [Xcode 14](https://developer.apple.com/xcode/).
2. Launch Xcode and proceed through the setup (if any). You may close it afterwards. This is to complete any first-run setup, which is sometimes required before being able to install Git.
3. Install Git by running the following the following command in Terminal and proceeding through the prompt to install Git (if any):
   ```sh
   git --version
   ```
4. Install [Brew](https://brew.sh/).
5. Install CMake by running the following command in Terminal:
   ```sh
   brew install cmake
   ```
6. Download [Boost](https://www.boost.org/users/download/) and extract it somewhere (example: `$HOME/Downloads/boost_1_80_0`)
7. Clone and change directory to the repository by running the following commands in Terminal:
   ```sh
   git clone https://github.com/evresi/lotyr
   cd lotyr
   git submodule update --init --recursive
   ```
8. Build Lotyr by running the following commands in the same Terminal:
   ```sh
   cmake -B build -DCMAKE_BUILD_TYPE=Release -DBOOST_ROOT=$HOME/Downloads/boost_1_80_0
   make -C build -j$(sysctl -n hw.physicalcpu)
   ```
   Don't forget to replace `$HOME/Downloads/boost_1_80_0` with where you extracted Boost if you extracted it elsewhere.

### Windows
1. Install [Visual Studio](https://visualstudio.microsoft.com/), [Git](https://git-scm.com/), and [CMake](https://cmake.org/download/).
2. Download [Boost](https://www.boost.org/users/download/) for Windows and extract it somewhere (example: `C:/boost_1_80_0`)
3. Clone and change directory to the repository by opening Command Prompt and running the following commands:
   ```
   git clone https://github.com/evresi/lotyr
   cd lotyr
   git submodule update --init --recursive
   ```
4. Build Lotyr by running the following commands in the same Command Prompt:
   ```
   cmake -B build -DCMAKE_BUILD_TYPE=Release -DBOOST_ROOT=C:/boost_1_80_0
   cmake --build build --config Release
   ```
   Don't forget to replace `C:/boost_1_80_0` with where you extracted Boost if you extracted it elsewhere.
