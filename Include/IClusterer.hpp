#pragma once


class IClusterer {
public:
	template <class _Type>
	using Data = std::vector<std::vector<_Type>>;

	virtual void Clustering() = 0;
	virtual void LoadDataClustering(const Data<double>& _data) = 0;
};