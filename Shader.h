//
// Created by kaguya on 2/5/24.
//

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <vector>

class Shader
{
public:
	static std::vector<char> readFile(const std::string &filename);
};

#endif // SHADER_H
