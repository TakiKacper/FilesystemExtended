# Filesystem Extended
A little C++ helper library for the std::filesystem

```cpp
#include "filesystem_extended.hpp"

#include <filesystem>
#include <iostream>

int main()
{
	try
	{
		auto s1 = filesystem_extended::symbol{ "project", "C:/Projects/filesystem_extended" };
		auto s2 = filesystem_extended::symbol{ "games", "E:/Games" };

		std::string vs_path = "project/visual_studio";
		std::filesystem::path system_vs_path = filesystem_extended::expand_symbol(vs_path, { &s1, &s2 });

		std::cout << "expanded: " << system_vs_path.string() << " : " << std::filesystem::exists(system_vs_path);  // C:/Projects/filesystem_extended/visual_studio
		std::cout << "is subdir 1: " << filesystem_extended::is_subdir("E:/Games/MyGame/", "E:/Games/");    // True
    		std::cout << "is subdir 2 "  << filesystem_extended::is_subdir("E:/Games/MyGame/", "C:/Projects/"); // False
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what();
	}

	return 0;
}
```
