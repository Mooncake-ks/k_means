#include "k-means.hpp"

//Данные
struct Data
{
	double sepal_length;  //Длина чашелистника.
	double sepal_width;	  //Ширина чашелистника.
	double petal_length;  //Длина лепестка.
	double petal_width;	  //Ширина лепестка.

};

class k_means
{
public:
	k_means(int n,const std::vector<Data>& data,int n_klasters);
	void clustering();

private:
	const int max_iter=200;			//Количество операций.

	std::vector<Data> m_centers;	//Центры.
	int n_klaster{0};				//Количество кластеров(центров).
	int n_data{0};					//Количество данных.
	std::vector<Data> m_data;		//Данные.

	void show( std::vector<int>& result);
	void choice_centr();												//Выбор центров.
	double euclidean_distance(const Data& p,const Data& q)const;		//Расстояние Евклида. 
	double recalculation_centers(const double& a, const double& b);		//Перерасчёт центров.

};

void set_data(const std::string& adres, std::vector<Data>& mas);

int main()
{
	/*std::vector<Data> test
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

	std::vector<Data> test;
	set_data("C:/Users/User/Desktop/test_data.csv", test);
	//for (auto& el : testing)
	//{
	//	std::cout << el.sepal_length << " " << el.sepal_width << " " << el.petal_length << " " << el.petal_width << std::endl;
	//}

	k_means testing(static_cast<int>(test.size()),test,5);
	testing.clustering();

	
    return 0;
}

k_means::k_means(int n, const std::vector<Data>& data, int n_klasters):n_data{n},m_data{data},n_klaster{n_klasters}
{choice_centr();}

void k_means::clustering()
{
	//std::cout << "The beginning of clustering:" << std::endl;
	std::vector<int> result_iter_1(n_data, -1), result_iter_2(n_data, -2);
	int iter{ 0 };
	while(true)
	{
		//Централизация центров.
		for (int j {0}; j < n_data; ++j)
		{
			std::vector<double> mas;
			for (int i {0}; i < n_klaster; ++i)
			{
				double temp = euclidean_distance(m_data[j], m_centers[i]);
				mas.push_back(temp);
				//std::cout << "Distance from data " << j << " to the center " << i << " : " << mas[i] << std::endl;
			}
			double min_dist = mas[0];
			int numder_centr{ 0 };
			for (int i {0}; i < n_klaster; ++i)
			{
				if (min_dist>mas[i])
				{
					min_dist = mas[i];
					numder_centr = i;
				}
			}
			//std::cout << "Minimum distance to the center #" << numder_centr << std::endl;
			//std::cout << "Recalculate the center #" << numder_centr << std::endl;
			m_centers[numder_centr].sepal_length = recalculation_centers(m_data[j].sepal_length,m_centers[numder_centr].sepal_length);
			m_centers[numder_centr].sepal_width = recalculation_centers(m_data[j].sepal_width, m_centers[numder_centr].sepal_width);
			m_centers[numder_centr].petal_length = recalculation_centers(m_data[j].petal_length, m_centers[numder_centr].petal_length);
			m_centers[numder_centr].petal_width = recalculation_centers(m_data[j].petal_width, m_centers[numder_centr].petal_width);
			/*std::cout << "Center # " << numder_centr << " " << m_centers[numder_centr].sepal_length <<
				" " << m_centers[numder_centr].sepal_width <<
				" " << m_centers[numder_centr].petal_length <<
				" " << m_centers[numder_centr].petal_width << std::endl;*/
		}
		//Классифицируем данные по кластерам.
		std::vector<int> mass(n_data,-1);
		//std::cout << "Let's classify Data:" << std::endl;
		for (int k {0}; k < n_data; ++k)
		{
			std::vector<double> mas;
			for (int i {0}; i < n_klaster; ++i)
			{
				mas.push_back(euclidean_distance(m_data[k], m_centers[i]));
				//std::cout << "Distance from data " << k << "to the center " << i << " : " << mas[i] << std::endl;
			}
			double min_dist = mas[0];
			int numder_centr{ 0 };
			for (int i{ 0 }; i < n_klaster; ++i)
			{
				if (min_dist > mas[i])
				{
					min_dist = mas[i];
					numder_centr = i;
				}
			}
			mass[k] = numder_centr;
			//std::cout << "Data " << k << " closest to the center " << numder_centr << std::endl;
		}
		//std::cout << "Array of matching pixels and centers: " << std::endl;
		for (int i {0}; i < n_data; ++i)
		{
			//std::cout << mass[i] << " ";
			result_iter_1[i]=mass[i];
		}
		//std::cout << "\n"<<std::endl;

		//Вывод результата.
		/*std::cout << "Clustering result:" << std::endl;
		int itr = 10 + 1;
		for (int i {0}; i < n_klaster; ++i)
		{
			std::cout << "Claster #" << i + 1 << std::endl;
			for (int j {0}; j < n_data; ++j)
			{
				if (mass[j]==i)
				{
					std::cout << m_data[j].sepal_length <<
						" " << m_data[j].sepal_width <<
						" " << m_data[j].petal_length <<
						" " << m_data[j].petal_width << std::endl;
					mass[j] = ++itr;
				}
			}
		}*/
		++iter;
		if (result_iter_1==result_iter_2 || iter>=max_iter)
		{
			break;
		}
		result_iter_2 = result_iter_1;
	}
	//std::cout << "End" << std::endl;
	show(result_iter_1);
}

void k_means::show( std::vector<int>& result)
{
	std::cout << "Clustering result:" << std::endl;
	int itr = 10 + 1;
	for (int i{ 0 }; i < n_klaster; ++i)
	{
		std::cout << "Claster #" << i + 1 << std::endl;
		for (int j{ 0 }; j < n_data; ++j)
		{
			if (result[j] == i)
			{
				std::cout << m_data[j].sepal_length <<
					" " << m_data[j].sepal_width <<
					" " << m_data[j].petal_length <<
					" " << m_data[j].petal_width << std::endl;
				result[j] = ++itr;
			}
		}
		std::cout  << std::endl;
	}
}

void k_means::choice_centr()
{
	srand((unsigned)time(NULL));

	Data temp{ 0 };
	std::vector<Data> temp_centr(n_klaster, {-1, -1, -1, -1});
	for (int i {0}; i < n_klaster; ++i)
	{
		temp = m_data[rand() % n_data];
		for (int j {i}; j < n_klaster; ++j)
		{
			/*if (m_centers.empty())
			{
				m_centers.push_back(temp);
			}*/
			//Проверка на дублирование центров.
			 if (temp.sepal_length == temp_centr[j].sepal_length
				&& temp.sepal_width == temp_centr[j].sepal_width
				&& temp.petal_length == temp_centr[j].petal_length
				&& temp.petal_width == temp_centr[j].petal_width)
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

double k_means::euclidean_distance(const Data& p, const Data& q) const
{
	double temp = sqrt(pow((p.sepal_length - q.sepal_length), 2)
		+ pow((p.sepal_width - q.sepal_width), 2)
		+ pow((p.petal_length - q.petal_length), 2)
		+ pow((p.petal_width - q.petal_width), 2));
	return	temp;
}

double k_means::recalculation_centers(const double& a, const double& b)
{
	return (a + b) / 2;
}

void set_data(const std::string& adres, std::vector<Data>& mas)
{
	
	try
	{
		std::ifstream  data;
		data.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		std::string  sepal_length, sepal_width, petal_length, petal_width, header;
		data.open(adres);
		std::getline(data, header, '\n');
		while (data.good())
		{
			std::getline(data, sepal_length, ';');
			std::getline(data, sepal_width, ';');
			std::getline(data, petal_length, ';');
			std::getline(data, petal_width, '\n');

			mas.push_back({ std::stod(sepal_length),std::stod(sepal_width),std::stod(petal_length),std::stod(petal_width) });

			sepal_length.clear();
			sepal_width.clear();
			petal_length.clear();
			petal_width.clear();
		}
		data.close();
	}
	catch (const std::ifstream::failure& ex)
	{
		//std::cout << ex.what() << " Error" << std::endl;
	}
}
