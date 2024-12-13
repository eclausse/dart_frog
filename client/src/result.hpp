#pragma once

#include <string>
#include <boost/uuid/uuid.hpp>

struct Result {
	Result(std::string id,
		std::string content,
		const bool code) : id(id), content(content), code(code){};
	const std::string id;
	const std::string content;
	const bool code;
};