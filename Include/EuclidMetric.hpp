#pragma once

#include "IMetric.hpp"

class EuclidMetric : public IMetric {
public:
	virtual double GetDistanceBetweenPoints(const std::vector<double>& p1, const std::vector<double>& p2) const override;
};