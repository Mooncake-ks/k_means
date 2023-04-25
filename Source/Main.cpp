
#include <iostream>
#include <Iris.hpp>
#include <k-means.hpp>



int main() {
	std::vector<Iris> test{
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
	};

	//std::vector<Iris> test;
	//set_data("C:/Users/User/Desktop/test_data.csv", test);

	kMeans testClusterizator;
	IMetric* metric = new EuclidMetric;

	testClusterizator.SetDataCount(test.size());
	testClusterizator.SetClustersCentersCount(3);
	testClusterizator.SetMetric(metric);
	testClusterizator.LoadDataClustering(ConvertInRawData(test));
	testClusterizator.Clustering();
	auto res = testClusterizator.GetClusteredData();

	for (size_t i = 0; i < res.size(); ++i) {
		std::cout << "Data[" << i + 1 << "]: ";
		std::copy(res[i].first.begin(), res[i].first.end(), std::ostream_iterator<double>(std::cout, " "));
		std::cout << "| Label: [" << res[i].second << "]: " << std::endl;
	}

	return 0;
}