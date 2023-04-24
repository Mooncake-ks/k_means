#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>


class kMeans : IClusterer {
public:
	template <class _Type>
	using Data = std::vector<std::vector<_Type>>;

	virtual void LoadDataClustering(const Data<double>& _data) override;

	virtual void Clustering() override;



	void SetDataCount(const uint32_t _dataCount) noexcept;
	void SetClustersCentersCount(const uint32_t _clustersCentersCount) noexcept;



	kMeans() = default;

	kMeans(const kMeans&) = delete;
	kMeans(kMeans&&) = delete;

	kMeans& operator = (const kMeans&) = delete;
	kMeans& operator = (kMeans&&) = delete;

private:
	//Количество итераций.
	const uint32_t m_maxIterations = 200;

	//Количество кластеров(центров).
	uint32_t m_clustersCentersCount = 0;
	//Количество данных.
	uint32_t m_dataCount = 0;

	//Центры.
	std::vector<Iris> m_centers;

	//Данные.
	Data<double> m_data;

	void show(std::vector<int>& result);
	void choice_centr();												//Выбор центров.
	double euclidean_distance(const Iris& p, const Iris& q)const;		//Расстояние Евклида. 
	double recalculation_centers(const double& a, const double& b);		//Перерасчёт центров.

};