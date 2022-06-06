#include "Globals.hpp"

AssetMaps Globals::asmp_get_asset_maps()
{
	return asmp_asset_maps;
}

Camera Globals::cmra_get_camera()
{
	return cmra_camera;
}

std::filesystem::path Globals::path_get_roaming_data_path()
{
	return path_roaming_data_path;
}

void Globals::update_controllers()
{
	for (auto& [slot, controller] : m_i_cntr_controllers)
	{
		controller.update();
	}
}

void Globals::update_mouse_wheel_input(int i_wheel, float f_delta)
{
	for (auto& [slot, controller] : m_i_cntr_controllers)
	{
		controller.update_mouse_wheel_input(i_wheel, f_delta);
	}
}

Controller Globals::cntr_get_controller(int i_controller)
{
	if (m_i_cntr_controllers.contains(i_controller))
	{
		return m_i_cntr_controllers[i_controller];
	}

	return Controller();
}

// static function
// sets "path" to a pointer to a unicode string containing the path to the current user's Appdata/Roaming/NotoriousNations folder
// returns true if "path" is successfully set
std::filesystem::path Globals::generate_roaming_data_path()
{
	std::filesystem::path path_path;
	PWSTR pwst_path;

	if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &pwst_path) != S_OK)
	{
		std::throw_with_nested(std::runtime_error("cannot find ...Appdata\\Roaming, got " + (*((wchar_t*)pwst_path))));
	}

	path_path = std::filesystem::path(pwst_path);

	path_path += "\\NotoriousNations";

	if (path_path.empty())
	{
		if (std::filesystem::create_directories(path_path))
		{
			std::wcout << L"folder " << path_path.generic_wstring() << L" created" << "\n";
		}
		else
		{
			std::throw_with_nested(std::runtime_error("failed to create ...Appdata\\Roaming\\NotoriousNations"));
		}
	}
	else
	{
		std::wcout << L"folder " << path_path.generic_wstring() << L" found" << "\n";
	}

	return path_path;
}