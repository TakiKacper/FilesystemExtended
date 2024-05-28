#pragma once

namespace filesystem_extended
{
	/*
		is_subdir
		returns whether given item is located in the dir or deeper
	*/
	inline bool is_subdir(std::filesystem::path item, std::filesystem::path dir)
	{
		if (!std::filesystem::exists(item)) throw std::exception({"Failed to check for the path belongingness; item does not exists"});
		if (!std::filesystem::exists(dir)) throw std::exception({ "Failed to check for the path belongingness; dir does not exists" });

		item = std::filesystem::canonical(item);
		dir = std::filesystem::canonical(dir);

		auto _item = item.string();
		auto _dir = dir.string();

		if (_dir.size() >= _item.size()) return false;

		for (int i = 0; i < dir.string().size(); i++)
			if (_item.at(i) != _dir.at(i))
				return false;

		return true;
	}
}
