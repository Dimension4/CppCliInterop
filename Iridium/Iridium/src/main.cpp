#include <iridium/interop/IridiumApplication.hpp>
#include <iridium/Image.hpp>

#include <iostream>
#include <string>
#include <map>
#include <functional>

using namespace ir;
using namespace ir::interop;

std::map<std::string, ir::Image> imageCache;

std::map<std::string_view, std::function<void(IridiumApplication&, std::string_view)>> commands
{
	{ "show", [](IridiumApplication& app, std::string_view cmd)
	{
		app.showWindow();
	}},
	{ "hide", [](IridiumApplication& app, std::string_view cmd)
	{
		app.hideWindow();
	}},
	{ "get image", [](IridiumApplication& app, std::string_view cmd)
	{
		imageCache[std::string(cmd)] = app.getImage();
	}},
	{ "set image", [](IridiumApplication& app, std::string_view cmd)
	{
		if (auto it = imageCache.find(std::string(cmd)); it != imageCache.end())
			app.setImage(it->second);
	}},
	{ "exit", [](IridiumApplication& app, std::string_view cmd)
	{
		app.exit();
	}},
};

int main()
{
	auto app = ir::interop::IridiumApplication::run();

	std::cout << "Type \"show\" or \"hide\" to show or hide the window\n\n";

	std::string input;
	ir::Image img;

	while (std::getline(std::cin, input) && !input.empty() && !app.hasStopped())
	{
		std::string_view cmd = input;

		for (auto&& [name, func] : commands)
		{
			if (cmd.length() >= name.length() && cmd.find(name) == 0)
			{
				auto subCmd = cmd.substr(name.length());
				if (auto pos = subCmd.find_first_not_of(" \t\r\n"); pos != std::string_view::npos)
					subCmd.remove_prefix(pos);
				if (auto pos = subCmd.find_last_not_of(" \t\r\n"); pos != std::string_view::npos)
					subCmd.remove_suffix(subCmd.length() - pos);

				func(app, subCmd);
				break;
			}
		}
	}

	std::cout << "Waiting for application exit...\n";
	app.waitExit();
	return 0;
}