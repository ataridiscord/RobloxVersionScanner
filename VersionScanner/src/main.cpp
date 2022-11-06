#include <iostream>
#include <cpr/cpr.h>
#include <filesystem>
#include <shlobj_core.h>
#include <KnownFolders.h>

#pragma warning(push)
#pragma warning(disable:4996)
inline std::string get_appdata_path()
{
    PWSTR appdata_path{};
    if (SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &appdata_path))
        return EXIT_FAILURE;

    char buff[MAX_PATH];
    wcstombs(buff, appdata_path, MAX_PATH);
    delete appdata_path;

    return buff;
}
#pragma warning(pop)

int main()
{
    SetConsoleTitleA("Version Scanner");

    const auto current_version = cpr::Get(cpr::Url{"http://setup.roblox.com/version"}).text;
    std::printf("Looking for version %s...\n", current_version);

    const auto path = (get_appdata_path() + "\\Roblox\\Versions\\" + current_version);

    if (!std::filesystem::exists(path))
        std::printf("Unable to find latest Roblox version.\n");
    else
        std::printf("Found latest Roblox version.\n");

    std::cin.get();
    return EXIT_SUCCESS;
}
