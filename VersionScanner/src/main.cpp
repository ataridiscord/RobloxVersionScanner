#include <iostream>
#include <curl/curl.h>
#include <Windows.h>
#include <string>
#include <format>
#include <filesystem>

__forceinline std::size_t writeFunction(void* ptr, unsigned long long size, unsigned long long nmemb, std::string* data)
{
    (std::string)data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

int main()
{
    std::string response{};
    std::string header{};
    auto response_code{0ul};

    const auto versions_path = "C:\\Users\\" + std::string(getenv("username")) + "\\AppData\\Local\\Roblox\\Versions\\";
    const auto latest_version_path = "C:\\Users\\" + std::string(getenv("username")) + "\\AppData\\Local\\Roblox\\Versions\\" + response;

    SetConsoleTitleA("Version Scanner - atari#5297");

    std::printf("This project is licensed under: GNU GENERAL PUBLIC LICENSE\nhttps://github.com/atari-1337/VersionScanner/blob/main/LICENSE\n\n");
    std::printf("Fetching current Roblox version...\n");

    curl_global_init(CURL_GLOBAL_DEFAULT);
    auto session = curl_easy_init();

    if (!session)
        return EXIT_FAILURE;

    curl_easy_setopt(session, CURLOPT_URL, "http://setup.roblox.com/version");
    curl_easy_setopt(session, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(session, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(session, CURLOPT_TCP_KEEPALIVE, 1L);

    curl_easy_setopt(session, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(session, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(session, CURLOPT_HEADERDATA, &header);

    auto code = curl_easy_perform(session);

    curl_easy_getinfo(session, CURLINFO_RESPONSE_CODE, &response_code);
    if (response_code != 200)
    {
        std::printf("Failed to fetch latest Roblox version.\n");
        std::cin.get();
        return EXIT_FAILURE;
    }

    curl_easy_cleanup(session);
    curl_global_cleanup();

    std::printf("Current Roblox Version: %s\n", response);

    if (!std::filesystem::exists(versions_path))
    {
        std::printf("Failed to locate the Roblox path.\n");
        std::cin.get();
        return EXIT_FAILURE;
    }

    if (!std::filesystem::exists(latest_version_path))
    {
        std::printf("[INFO]: Your Roblox Client is outdated, would you like to update?\n");
        std::printf("Y/N: ");
        if (std::cin.get() != 'y')
            return EXIT_SUCCESS;
        const auto sh_path = "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Roblox\\Roblox Player";
        switch (std::filesystem::exists(sh_path))
        {
        case true:
            system(std::format("runas.exe / savecred / user:administrator {}", sh_path).c_str());
            std::this_thread::sleep_for(std::chrono::seconds(3));
            break;

        default:
            std::printf("[ERROR]: Failed to locate Roblox Player.\n");
            std::cin.get();
            return EXIT_FAILURE;
            break;
        }
        return EXIT_SUCCESS;
    }
}
