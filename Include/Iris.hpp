#pragma once

#include "IData.hpp"

class Iris : public IData {
public:
	virtual std::vector<double> getRawData() const override;

	Iris() {}

	Iris(const double _m_sepal_length, const double _m_sepal_width, const double _m_petal_length, const double _m_petal_width) noexcept;
	Iris(Iris&& i) noexcept = default;
	Iris(const Iris& i) noexcept = default;

	Iris& operator=(Iris&& i) noexcept;
	Iris& operator=(const Iris& i) noexcept;

private:
	double m_sepal_length = 0;  //Длина чашелистника.
	double m_sepal_width = 0;	  //Ширина чашелистника.
	double m_petal_length = 0;  //Длина лепестка.
	double m_petal_width = 0;	  //Ширина лепестка.
};