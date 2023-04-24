#pragma once

#include <vector>
class IData {
public:
	virtual std::vector<double> getRawData() const = 0;
};