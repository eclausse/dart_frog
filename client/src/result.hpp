#pragma once

#include <string>
#include <boost/uuid/uuid.hpp>

struct Result {
	/*Result(const boost::uuids::uuid& id,
		std::string contents,
		bool success);*/
	const boost::uuids::uuid id;
	const std::string contents;
	const bool success;
};