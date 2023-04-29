#include <Iris.hpp>

std::vector<double> Iris::getRawData() const {
	return { m_sepal_length, m_sepal_width, m_petal_length, m_petal_width };
}


Iris::Iris(const double _m_sepal_length, const double _m_sepal_width, const double _m_petal_length, const double _m_petal_width) noexcept
	:
	m_sepal_length(_m_sepal_length),
	m_sepal_width(_m_sepal_width),
	m_petal_length(_m_petal_length),
	m_petal_width(_m_petal_width)
{}

Iris& Iris::operator=(Iris&& other) noexcept {
	if (this != &other) {
		m_sepal_length = std::move(other.m_sepal_length);
		m_sepal_width = std::move(other.m_sepal_width);
		m_petal_length = std::move(other.m_petal_length);
		m_petal_width = std::move(other.m_petal_width);
	}
	return *this;
}

Iris& Iris::operator=(const Iris& other) noexcept {
	if (this != &other) {
		m_sepal_length = other.m_sepal_length;
		m_sepal_width = other.m_sepal_width;
		m_petal_length = other.m_petal_length;
		m_petal_width = other.m_petal_width;
	}
	return *this;
}