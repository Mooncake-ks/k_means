#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <optional>
#include "EuclidMetric.hpp"
#include "IClusterer.hpp"
#include "Iris.hpp"

template <typename T>
concept DerivedFromIData = std::is_base_of<IData, T>::value;

template <DerivedFromIData T>
std::vector<std::vector<double>> ConvertInRawData(const std::vector<T>& data) {
	std::vector<std::vector<double>> result;
	for (const auto& el : data) {
		result.push_back(el.getRawData());
	}
	return result;
}

template <class _Type>
using Data = std::vector<std::vector<_Type>>;

class kMeans : IClusterer {
public:

	virtual void LoadDataClustering(const Data<double>& _data) override;

	virtual void Clustering() override;

	void AssignClusters();
	bool UpdateCenters();



	void SetDataCount(const uint32_t _dataCount) noexcept;
	void SetClustersCentersCount(const uint32_t _clustersCentersCount) noexcept;
	void SetMetric(IMetric* _metric);

	std::vector<std::pair<std::vector<double>, uint32_t>> GetClusteredData() const;



	kMeans() = default;

	kMeans(const kMeans&) = delete;
	kMeans(kMeans&&) = delete;

	kMeans& operator = (const kMeans&) = delete;
	kMeans& operator = (kMeans&&) = delete;

	~kMeans();

private:
	//Количество кластеров(центров).
	uint32_t m_clustersCentersCount = 0;
	//Количество данных.
	uint32_t m_dataCount = 0;

	//Центры.
	Data<double> m_centers;
	//Данные.
	Data<double> m_data;

	std::vector<uint32_t> m_labels;

	//Метрика
	IMetric* m_metric = nullptr;

	void FindInitialCentroids();
};