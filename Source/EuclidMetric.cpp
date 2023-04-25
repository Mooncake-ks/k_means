#include "EuclidMetric.hpp"
#include <cmath>


double EuclidMetric::GetDistanceBetweenPoints(const std::vector<double>& p1, const std::vector<double>& p2) const {
	double dist = 0;
	for (size_t i = 0; i < p1.size(); ++i) {
		dist += std::pow(p1[i] - p2[i], 2);
	}
	return std::sqrt(dist);
}