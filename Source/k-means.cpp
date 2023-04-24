#include "k-means.hpp"
#include "Iris.hpp"
#include "IClusterer.hpp"

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


	//kMeans testing(static_cast<int>(test.size()),test,5);
	//testing.clustering();

	
    return 0;
}

kMeans::kMeans()
{choice_centr();}

void kMeans::Сlustering()
{
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

void kMeans::choice_centr()
{
	srand((unsigned)time(NULL));

	Iris temp;
	std::vector<Iris> temp_centr(m_clustersCentersCount, {-1, -1, -1, -1});
	for (int i {0}; i < m_clustersCentersCount; ++i)
	{
		temp = m_data[rand() % m_dataCount];
		for (int j {i}; j < m_clustersCentersCount; ++j)
		{
			/*if (m_centers.empty())
			{
				m_centers.push_back(temp);
			}*/
			//Проверка на дублирование центров.
			 if (temp.m_sepal_length == temp_centr[j].m_sepal_length
				&& temp.m_sepal_width == temp_centr[j].m_sepal_width
				&& temp.m_petal_length == temp_centr[j].m_petal_length
				&& temp.m_petal_width == temp_centr[j].m_petal_width)
			{
				 --i;
				 break;
			}
			else
			{
				 temp_centr[j] = temp;
			}
		}
	}
	m_centers = temp_centr;
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
