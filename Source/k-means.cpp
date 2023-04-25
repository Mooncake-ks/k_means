#include "k-means.hpp"

#include <random>

void kMeans::LoadDataClustering(const Data<double>& _data) {
	m_data = _data;
}

void kMeans::SetDataCount(const uint32_t _dataCount) noexcept {
	m_dataCount = _dataCount;
}

void kMeans::SetClustersCentersCount(const uint32_t _clustersCentersCount) noexcept {
	m_clustersCentersCount = _clustersCentersCount;
}



//int main() {
//	std::vector<Iris> test {
//		{5.1,3.5,1.4,0.2},
//		{4.9,3.0,1.4,0.2},
//		{3.7,1.2,3.3,0.2},
//		{4.6,3.1,1.5,0.2},
//		{5.0,3.4,1.4,0.2},
//		{5.4,3.9,1.7,0.4},
//		{4.6,3.4,1.4,0.3},
//		{5.0,3.4,1.5,0.2},
//		{2.4,2.9,2.4,0.2},
//		{2.9,2.1,0.5,0.1}
//	};
//
//	//std::vector<Iris> test;
//	//set_data("C:/Users/User/Desktop/test_data.csv", test);
//
//	kMeans testClusterizator;
//	IMetric* metric = new EuclidMetric;
//
//	testClusterizator.SetDataCount(test.size());
//	testClusterizator.SetClustersCentersCount(3);
//	testClusterizator.SetMetric(metric);
//	testClusterizator.LoadDataClustering(ConvertInRawData(test));
//	testClusterizator.Clustering();
//	auto res = testClusterizator.GetClusteredData();
//
//	for (size_t i = 0; i < res.size(); ++i) {
//		std::cout << "Data[" << i + 1 << "]: ";
//		std::copy(res[i].first.begin(), res[i].first.end(), std::ostream_iterator< double >(std::cout, " "));
//		std::cout << "| Label: [" << res[i].second << "]: " << std::endl;
//	}
//	
//    return 0;
//}

void kMeans::Clustering() {

	FindInitialCentroids();

	while (true) {
		AssignClusters();

		if (UpdateCenters()) {
			break;
		}
	}
}

void kMeans::AssignClusters() {
	m_labels.clear();
	m_labels.shrink_to_fit();

	for (const auto& point : m_data) {
		double min_distance = std::numeric_limits<double>::max();
		uint32_t label = 0;

		for (size_t i = 0; i < m_centers.size(); ++i) {
			double distance = m_metric->GetDistanceBetweenPoints(point, m_centers[i]);

			if (distance < min_distance) {
				min_distance = distance;
				label = i;
			}
		}

		m_labels.push_back(label);
	}
}

bool kMeans::UpdateCenters() {
	std::vector<std::vector<double>> newCenters(m_clustersCentersCount, std::vector<double>(m_data[0].size(), 0));
	std::vector<uint32_t> counts(m_clustersCentersCount, 0);

	for (size_t i = 0; i < m_data.size(); ++i) {
		int label = m_labels[i];
		for (size_t j = 0; j < m_data[i].size(); ++j) {
			newCenters[label][j] += m_data[i][j];
		}
		counts[label]++;
	}

	for (size_t i = 0; i < m_centers.size(); ++i) {
		if (counts[i] == 0) {
			continue;
		}
		for (size_t j = 0; j < m_centers[i].size(); ++j) {
			newCenters[i][j] /= counts[i];
		}
	}

	if (newCenters == m_centers) {
		return true;
	}

	m_centers = std::move(newCenters);
	return false;
}

void kMeans::FindInitialCentroids() {
	// Создаем генератор случайных чисел
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, m_data.size() - 1);

	// Создаем вектор для хранения начальных центров кластеров
	Data<double> centroids(m_clustersCentersCount);

	// Выбираем случайные элементы из вектора данных в качестве начальных центров кластеров
	for (int i = 0; i < m_clustersCentersCount; ++i) {
		centroids[i] = m_data[distrib(gen)];
	}

	// Проверяем, что все начальные центры кластеров различны
	bool centersAreUnique = false;
	while (!centersAreUnique) {
		centersAreUnique = true;

		for (int i = 0; i < m_clustersCentersCount; ++i) {
			for (int j = i + 1; j < m_clustersCentersCount; ++j) {
				if (centroids[i] == centroids[j]) {
					centersAreUnique = false;
					centroids[i] = m_data[distrib(gen)];
					break;
				}
			}
		}
	}
	m_centers = std::move(centroids);
}

void kMeans::SetMetric(IMetric* _metric) {
	m_metric = std::move(_metric);
}

kMeans::~kMeans() {
	delete m_metric;
}

std::vector<std::pair<std::vector<double>, uint32_t>> kMeans::GetClusteredData() const {
	std::vector<std::pair<std::vector<double>, uint32_t>> clusteredData;
	for (size_t i = 0; i < m_data.size(); ++i) {
		clusteredData.push_back({ m_data[i], m_labels[i]});
	}
	return clusteredData;
}

//void set_data(const std::string& adres, std::vector<Iris>& mas)
//{
//	
//	try
//	{
//		std::ifstream  Iris;
//		Iris.exceptions(std::ifstream::badbit | std::ifstream::failbit);
//		std::string  m_sepal_length, m_sepal_width, m_petal_length, m_petal_width, header;
//		Iris.open(adres);
//		std::getline(Iris, header, '\n');
//		while (Iris.good())
//		{
//			std::getline(Iris, m_sepal_length, ';');
//			std::getline(Iris, m_sepal_width, ';');
//			std::getline(Iris, m_petal_length, ';');
//			std::getline(Iris, m_petal_width, '\n');
//
//			mas.push_back({std::stod(m_sepal_length), std::stod(m_sepal_width),std::stod(m_petal_length),std::stod(m_petal_width) });
//
//			m_sepal_length.clear();
//			m_sepal_width.clear();
//			m_petal_length.clear();
//			m_petal_width.clear();
//		}
//		Iris.close();
//	}
//	catch (const std::ifstream::failure& ex)
//	{
//		std::cout << ex.what() << " Error" << std::endl;
//	}
//}
