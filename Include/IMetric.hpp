#pragma once

#include <vector>
class IMetric {
public:
	virtual double GetDistanceBetweenPoints(const std::vector<double>& p1, const std::vector<double>& p2) const = 0;
};