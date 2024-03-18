#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <fstream>
#include <string>
#pragma comment(lib, "wininet.lib")
using namespace std;

void downloadFile(const string& url, const string& dest) {
    HINTERNET hInternet, hConnect;
    DWORD bytesRead;

    hInternet = InternetOpen(L"Internet Connection", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        cout << "InternetOpen failed" << endl;
        return;
    }

    hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hConnect == NULL) {
        cout << "InternetOpenUrlA failed" << endl;
        InternetCloseHandle(hInternet);
        return;
    }

    char buffer[4096];
    ofstream destStream(dest, ios::binary);

    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        destStream.write(buffer, bytesRead);
    }

    destStream.close();
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
}

int main() {
    int q;
    cout << " Choose option : " << endl;
    cout << "1.Fix Steam." << endl;
    cout << "2.Revert Changes." << endl;
    cin >> q;
    if (q == 1) {
        remove("C:\\Program Files (x86)\\Steam\\GameOverlayRenderer.dll");
        downloadFile("https://github.com/finutz/Buffiware-cheat-SteamFixx/raw/main/steamfix_files/GameOverlayRenderer.dll", "C:\\Program Files (x86)\\Steam\\GameOverlayRenderer.dll");
        downloadFile("https://github.com/finutz/Buffiware-cheat-SteamFixx/raw/main/steamfix_files/steam.cfg", "C:\\Program Files (x86)\\Steam\\steam.cfg");
    }
    else if (q == 2) {
        remove("C:\\Program Files (x86)\\Steam\\steam.cfg");
    }
    else {
        cout << "Invalid option";
    }
    return 0;
}
