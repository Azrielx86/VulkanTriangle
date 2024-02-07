//
// Created by kaguya on 2/5/24.
//

#include "Shader.h"

#include <boost/format.hpp>
#include <fstream>
#include <ios>

std::vector<char> Shader::readFile(const std::string &filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);
	if (!file.is_open())
	{
		auto errMsg = boost::format("Cant read file: %s") % filename;
		throw std::runtime_error(errMsg.str());
	}

	size_t fileSize = file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}