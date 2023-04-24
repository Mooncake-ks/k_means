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
	//���������� ��������.
	const uint32_t m_maxIterations = 200;

	//���������� ���������(�������).
	uint32_t m_clustersCentersCount = 0;
	//���������� ������.
	uint32_t m_dataCount = 0;

	//������.
	std::vector<Iris> m_centers;

	//������.
	Data<double> m_data;

	void show(std::vector<int>& result);
	void choice_centr();												//����� �������.
	double euclidean_distance(const Iris& p, const Iris& q)const;		//���������� �������. 
	double recalculation_centers(const double& a, const double& b);		//���������� �������.

};