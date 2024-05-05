#pragma once
#include <filesystem>
#include <vector>

namespace filesystem_extended
{
	/*
		symbol
		allows for creating relative paths by replacing it's unknow part with a symbol
	*/
	class symbol
	{
	private:
		std::string _symbol_name;
		std::filesystem::path _path;
	public:
		symbol(std::string symbol_name, std::filesystem::path path)
		{
			if (!std::filesystem::exists(path)) throw std::exception({ "Symbol must be initialized with a path to existing directory" });

			_path = std::filesystem::canonical(path);
			_symbol_name = std::move(symbol_name);
		}
		inline const std::string& get_name() { return _symbol_name; };
		inline const std::filesystem::path& get_path() { return _path; };
	};

	/*
		expand_symbol
		replaces symbol with the path assigned to it
	*/
	std::filesystem::path expand_symbol(std::string path_with_symbol, std::vector<symbol*> available_symbols)
	{
		size_t symbol_end = path_with_symbol.find_first_of('/');

		std::string to_expand;
		std::string rest;

		if (symbol_end == path_with_symbol.size())
		{
			rest = "";
			to_expand = std::move(path_with_symbol);
		}
		else
		{
			rest = path_with_symbol.substr(symbol_end, path_with_symbol.size());
			to_expand = path_with_symbol.substr(0, symbol_end);
		}

		for (auto& symbol : available_symbols)
		{
			if (to_expand == symbol->get_name())
				return (symbol->get_path().string() + rest);
		}

		throw std::exception{(std::string("Failed to expand_symbol; No symbol named: ") + to_expand).c_str()};
		return "";
	}
}
