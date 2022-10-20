# VersionScanner
Simple tool which compares the latest version of Roblox with the current installed version.

## Summary
Grabs the latest Roblox version from the internet and compares it to the one which is currently installed on your PC.

## How to Compile

NOTE: Ensure you follow these steps or it'll most likely fail to build.

1. If you want to use build this project, you need to setup a few things. First, install [Visual Studio 2022](https://www.visualstudio.com/downloads/).

2. Install [vcpkg](https://github.com/Microsoft/vcpkg)

3. Open Command Prompt and type the following:

```dos
cd /path/to/vckpg
```

4. Once you've changed your directory to the vcpkg path - you can continue by typing in the following:

```dos
vcpkg install curl:x64-windows
```

5. Wait for it to install - once done, type the following:

```dos
vcpkg integrate install
```

6. Download the source code.

7. Enjoy <3

## License
This project is licensed under the GNU General Public License v3.0. See the [LICENSE](https://github.com/atari-1337/VersionScanner/blob/main/LICENSE) file for more information.
