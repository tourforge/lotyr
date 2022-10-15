# Lotyr
A library that wraps Valhalla with a tiny bit of code to make it easy to embed
in your own application written in any language.

Lotyr (**Lo**cal wrapper around Valhalla's **Tyr**) produces a shared library
that can be used from nearly any programming language.

## Building
### Linux
TODO: Full Linux instructions
```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
make -C build
```

### MacOS
1. Install [Xcode 14](https://developer.apple.com/xcode/).
2. Launch Xcode and proceed through the setup (if any). You may close it afterwards. This is to complete any first-run setup, which is sometimes required before being able to install Git.
3. Install Git by running the following the following command in Terminal and proceeding through the prompt to install Git (if one pops up):
   ```sh
   git --version
   ```
4. Install [Brew](https://brew.sh/).
5. Install CMake by running the following command in Terminal:
   ```sh
   brew install cmake
   ```
6. Download [Boost](https://www.boost.org/users/download/) and extract it somewhere (example: `$HOME/Downloads/boost_1_8_0`)
7. Clone the repository by running the following command in Terminal:
   ```sh
   git clone https://github.com/evresi/lotyr
   ```
8. Build Lotyr by running the following commands in the same Terminal:
   ```sh
   cd lotyr
   cmake -B build -DCMAKE_BUILD_TYPE=Release -DBOOST_ROOT=$HOME/Downloads/boost_1_8_0
   make -C build -j$(sysctl -n hw.physicalcpu)
   ```

### Windows
1. Install [Visual Studio](https://visualstudio.microsoft.com/) and [Git](https://git-scm.com/).
2. Download [Boost](https://www.boost.org/users/download/) for Windows and extract it somewhere (example: `C:/boost_1_8_0`)
3. Clone the repository by opening Command Prompt and running the following command:
   ```
   git clone https://github.com/evresi/lotyr
   ```
4. Generate build files by running the following in the same Command Prompt:
   ```
   cd lotyr
   cmake -B build -DCMAKE_BUILD_TYPE=Release -DBOOST_ROOT=C:/boost_1_8_0
   ```
   Don't forget to replace `C:/boost_1_8_0` with where you extracted Boost if you extracted it elsewhere.
5. Launch Visual Studio by running these commands in the same Command Prompt:
   ```
   cd build
   start lotyr.sln
   ```
   You could also navigate to this folder in Explorer and double-click on lotyr.sln to open Visual Studio.
6. Run the build by clicking Build in the top bar -> Build Solution.
