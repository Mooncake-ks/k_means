#include "k-means.hpp"
#include "Iris.hpp"
#include "IClusterer.hpp"

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









void set_data(const std::string& adres, std::vector<Iris>& mas);

int main()
{
	/*std::vector<Iris> test
	{
		{5.1,3.5,1.4,0.2},
		{4.9,3.0,1.4,0.2},
		{3.7,1.2,3.3,0.2},
		{4.6,3.1,1.5,0.2},
		{5.0,3.4,1.4,0.2},
		{5.4,3.9,1.7,0.4},
		{4.6,3.4,1.4,0.3},
		{5.0,3.4,1.5,0.2},
		{2.4,2.9,2.4,0.2},
		{2.9,2.1,0.5,0.1}
	};*/

	std::vector<Iris> test;
	set_data("C:/Users/User/Desktop/test_data.csv", test);

	kMeans testClusterizator;
	testClusterizator.SetDataCount(test.size());
	testClusterizator.SetClustersCentersCount(5);
	testClusterizator.LoadDataClustering(ConvertInRawData(test));
	testClusterizator.Clustering();


	//kMeans testing(static_cast<int>(test.size()),test,5);
	//testing.clustering();

	
    return 0;
}

void kMeans::Clustering() {

	FindInitialCentroids();

	//std::cout << "The beginning of clustering:" << std::endl;
	std::vector<int> result_iter_1(m_dataCount, -1), result_iter_2(m_dataCount, -2);
	int iter{ 0 };
	while(true)
	{
		//Централизация центров.
		for (int j {0}; j < m_dataCount; ++j)
		{
			std::vector<double> mas;
			for (int i {0}; i < m_clustersCentersCount; ++i)
			{
				double temp = euclidean_distance(m_data[j], m_centers[i]);
				mas.push_back(temp);
				//std::cout << "Distance from Iris " << j << " to the center " << i << " : " << mas[i] << std::endl;
			}
			double min_dist = mas[0];
			int numder_centr{ 0 };
			for (int i {0}; i < m_clustersCentersCount; ++i)
			{
				if (min_dist>mas[i])
				{
					min_dist = mas[i];
					numder_centr = i;
				}
			}
			//std::cout << "Minimum distance to the center #" << numder_centr << std::endl;
			//std::cout << "Recalculate the center #" << numder_centr << std::endl;
			m_centers[numder_centr].m_sepal_length = recalculation_centers(m_data[j].m_sepal_length,m_centers[numder_centr].m_sepal_length);
			m_centers[numder_centr].m_sepal_width = recalculation_centers(m_data[j].m_sepal_width, m_centers[numder_centr].m_sepal_width);
			m_centers[numder_centr].m_petal_length = recalculation_centers(m_data[j].m_petal_length, m_centers[numder_centr].m_petal_length);
			m_centers[numder_centr].m_petal_width = recalculation_centers(m_data[j].m_petal_width, m_centers[numder_centr].m_petal_width);
			/*std::cout << "Center # " << numder_centr << " " << m_centers[numder_centr].m_sepal_length <<
				" " << m_centers[numder_centr].m_sepal_width <<
				" " << m_centers[numder_centr].m_petal_length <<
				" " << m_centers[numder_centr].m_petal_width << std::endl;*/
		}
		//Классифицируем данные по кластерам.
		std::vector<int> mass(m_dataCount,-1);
		//std::cout << "Let's classify Iris:" << std::endl;
		for (int k {0}; k < m_dataCount; ++k)
		{
			std::vector<double> mas;
			for (int i {0}; i < m_clustersCentersCount; ++i)
			{
				mas.push_back(euclidean_distance(m_data[k], m_centers[i]));
				//std::cout << "Distance from Iris " << k << "to the center " << i << " : " << mas[i] << std::endl;
			}
			double min_dist = mas[0];
			int numder_centr{ 0 };
			for (int i{ 0 }; i < m_clustersCentersCount; ++i)
			{
				if (min_dist > mas[i])
				{
					min_dist = mas[i];
					numder_centr = i;
				}
			}
			mass[k] = numder_centr;
			//std::cout << "Iris " << k << " closest to the center " << numder_centr << std::endl;
		}
		//std::cout << "Array of matching pixels and centers: " << std::endl;
		for (int i {0}; i < m_dataCount; ++i)
		{
			//std::cout << mass[i] << " ";
			result_iter_1[i]=mass[i];
		}

		++iter;
		if (result_iter_1==result_iter_2 || iter>=m_maxIterations)
		{
			break;
		}
		result_iter_2 = result_iter_1;
	}
	//std::cout << "End" << std::endl;
	show(result_iter_1);
}

void kMeans::show( std::vector<int>& result)
{
	std::cout << "Clustering result:" << std::endl;
	int itr = 10 + 1;
	for (int i{ 0 }; i < m_clustersCentersCount; ++i)
	{
		std::cout << "Claster #" << i + 1 << std::endl;
		for (int j{ 0 }; j < m_dataCount; ++j)
		{
			if (result[j] == i)
			{
				std::cout << m_data[j].m_sepal_length <<
					" " << m_data[j].m_sepal_width <<
					" " << m_data[j].m_petal_length <<
					" " << m_data[j].m_petal_width << std::endl;
				result[j] = ++itr;
			}
		}
		std::cout  << std::endl;
	}
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

double kMeans::euclidean_distance(const Iris& p, const Iris& q) const
{
	double temp = sqrt(pow((p.m_sepal_length - q.m_sepal_length), 2)
		+ pow((p.m_sepal_width - q.m_sepal_width), 2)
		+ pow((p.m_petal_length - q.m_petal_length), 2)
		+ pow((p.m_petal_width - q.m_petal_width), 2));
	return	temp;
}

double kMeans::recalculation_centers(const double& a, const double& b)
{
	return (a + b) / 2;
}

void set_data(const std::string& adres, std::vector<Iris>& mas)
{
	
	try
	{
		std::ifstream  Iris;
		Iris.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		std::string  m_sepal_length, m_sepal_width, m_petal_length, m_petal_width, header;
		Iris.open(adres);
		std::getline(Iris, header, '\n');
		while (Iris.good())
		{
			std::getline(Iris, m_sepal_length, ';');
			std::getline(Iris, m_sepal_width, ';');
			std::getline(Iris, m_petal_length, ';');
			std::getline(Iris, m_petal_width, '\n');

			mas.push_back({std::stod(m_sepal_length), std::stod(m_sepal_width),std::stod(m_petal_length),std::stod(m_petal_width) });

			m_sepal_length.clear();
			m_sepal_width.clear();
			m_petal_length.clear();
			m_petal_width.clear();
		}
		Iris.close();
	}
	catch (const std::ifstream::failure& ex)
	{
		std::cout << ex.what() << " Error" << std::endl;
	}
}
