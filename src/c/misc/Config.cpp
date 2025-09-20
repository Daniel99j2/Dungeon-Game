//
// Created by dj on 17/09/2025.
//

#include "Config.h"

bool Config::fullscreen = false;

void Config::load() {
	std::string userDir = getenv("USERPROFILE");
	std::ifstream file(userDir+"\\AppData\\Roaming\\Dungeon Game\\config.json");

	if (file.is_open()) {
		std::stringstream buffer;
		buffer << file.rdbuf();
		nlohmann::json data = nlohmann::json::parse(buffer.str());
		fullscreen = data["fullscreen"];
		save();
	} else {
		CoInitialize(NULL);

		IShellLink *psl;

		// we get the pointer
		HRESULT hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
										IID_IShellLink, (LPVOID *) &psl);

		IPersistFile *ppf;

		psl->SetPath((userDir+"\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Blockbench.lnk").c_str());
		psl->SetDescription("Dungeon Game Shortcut");

		// get and save
		hres = psl->QueryInterface(IID_IPersistFile, (LPVOID *) &ppf);
		std::wstring shortcutPath = std::wstring(userDir.begin(), userDir.end()) +
									L"\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Dungeon Game.lnk";
		ppf->Save(shortcutPath.c_str(), TRUE); // true means with unicode
		ppf->Release();
		psl->Release();

		CoUninitialize();
	}

	save();
};

void Config::save() {
	std::string userDir = getenv("USERPROFILE");

	nlohmann::json j;
	j["fullscreen"] = fullscreen;
	j["test"] = true;
	std::wstring shortcutPath = std::wstring(userDir.begin(), userDir.end()) +
							L"\\AppData\\Roaming\\DungeonGame\\config.json";
	std::ofstream out(shortcutPath);
	out << j.dump(2);
};