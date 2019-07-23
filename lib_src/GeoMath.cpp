#include "GeoMath.h"

double
sign(double arg)
{
	return arg < 0 ? -1 : 1;
}

GeoMath::v3::v3(double x_, double y_, double z_)
	: x(x_)
	, y(y_)
	, z(z_)
{
}

GeoMath::v3geo::v3geo(double lat_, double lng_, double alt_)
	: lat(lat_)
	, lng(lng_)
	, alt(alt_) {};

bool
GeoMath::v3::isNull()
{

	return (x == 0 && y == 0 && z==0);
}

double
GeoMath::v3::length_xy()
{
	double result = sqrt(x * x + y * y);
	return result;
}

double
GeoMath::v3::length_xyz()
{
	double result = sqrt(x * x + y * y + z * z);
	return result;
}

double
GeoMath::v3::angle_xy(v3 v = v3(1, 0, 0))
{
	double sgn;
	double value;
	if (this->isNull() || v.isNull())
		return 0;

	value = this->x * v.x + this->y * v.y;
	value = value / (this->length_xy() * v.length_xy());
	sgn = -sign(this->x * v.y - this->y * v.x);

	return sgn * acos(value);
}

GeoMath::v3
GeoMath::v3::normalize_xy(double abs = 1)
{
	if (this->isNull())
		return v3(0, 0, 0);

	v3     result;
	double factor = abs / this->length_xy();

	result.z = this->z;
	result.x = this->x * factor;
	result.y = this->y * factor;

	return result;
}

GeoMath::v3
GeoMath::v3::normalize_xyz(double abs = 1)
{
	if (this->isNull())
		return v3(0, 0, 0);

	v3     result;
	double factor = abs / this->length_xyz();

	result.z = this->z * factor;
	result.x = this->x * factor;
	result.y = this->y * factor;

	return result;
}

GeoMath::v3
GeoMath::v3::rotateXY(double rad)
{
	v3 result(this->x * cos(rad) - this->y * sin(rad),
		this->x * sin(rad) + this->y * cos(rad),
		this->z);
	return result;
}

GeoMath::v3
GeoMath::v3::rotate(double a, GeoMath::Axis axis, Hand hand )
{
	if(hand==RIGHT) a = -a;

	v3 res(0, 0, 0);
	switch (axis)
	{
	case GeoMath::X:
		/*
		������� �������� ������ X

		| 1     0    0   |
	    | 0     cos -sin |
		| 0     sin  cos |
		*/
		res.x = this->x;
		res.y = this->y * cos(a) + this->z * sin(a);
		res.z = this->y * -sin(a) + this->z * cos(a);
		break;
	case GeoMath::Y:
		/*
		������� �������� ������ Y

		| cos   0    sin |
		| 0     1    0   |
		|-sin   0    cos |
		*/
		res.x = this->x * cos(a) - this->z * sin(a);
		res.y = this->y;
		res.z = this->x * sin(a) + this->z * cos(a);
		break;
	case GeoMath::Z:
		/*
		������� �������� ������ Z

		| cos  -sin  0   |
		| sin   cos  0   |
		| 0     0    1   |
		*/
		res.x = this->x * cos(a) + this->y * sin(a);
		res.y = this->x * -sin(a) + this->y * cos(a);
		res.z = this->z;
		break;
	}
	return res;
}

GeoMath::v3
GeoMath::v3::operator+(v3 const& v2)
{
	v3 result(this->x + v2.x, this->y + v2.y, this->z + v2.z);
	return result;
}

GeoMath::v3
GeoMath::v3::operator-(v3 const& v2)
{
	v3 result(this->x - v2.x, this->y - v2.y, this->z - v2.z);
	return result;
}

GeoMath::v3 GeoMath::v3::operator*(double factor)
{
	v3 result(*this);
	result.x = result.x * factor;
	result.y = result.y * factor;
	result.z = result.z * factor;
	return result;
}

GeoMath::v3
GeoMath::v3::operator/(double demiter)
{
	v3 result(*this);
	result.x = result.x / demiter;
	result.y = result.y / demiter;
	result.z = result.z / demiter;
	return result;
}


std::ostream& GeoMath::operator<<(std::ostream& os, const GeoMath::v3& at)
{
os <<"x: "<<at.x<<" y: "<<at.y<<" z: "<<at.z;
return os;
}

std::ostream& GeoMath::operator<<(std::ostream& os, const GeoMath::v3geo& at)
{
os <<"lat: "<<at.lat<<" lng: "<<at.lng<<" alt: "<<at.alt;
return os;
}

GeoMath::v3
GeoMath::v3geo::operator-(v3geo const& v2)
{

	v3geo P1(v2);
	v3geo P2(*this);

	P1.lat = P1.lat * CONST.DEG2RAD;
	P1.lng = P1.lng * CONST.DEG2RAD;

	P2.lat = P2.lat * CONST.DEG2RAD;
	P2.lng = P2.lng * CONST.DEG2RAD;

	v3 P0;
	P0.x = (P2.lat - P1.lat) * CONST.P_EARTH;
	P0.y = (P2.lng - P1.lng) * CONST.E_EARTH * cos(P1.lat);
	P0.z = P2.alt - P1.alt;

	return P0;
}

GeoMath::v3geo
GeoMath::v3geo::operator+(v3 const& v2)
{

	double dlat = v2.x / CONST.M_IN_LAT;
	double m_in_lng = (cos((this->lat + dlat) * CONST.DEG2RAD) * CONST.M_IN_LNG);
	double dlng = v2.y / m_in_lng;

	v3geo result(this->lat + dlat, this->lng + dlng, this->alt + v2.z);
	return result;
}

std::vector<GeoMath::v3geo>
GeoMath::absPosListGeo(GeoMath::v3geo           point,
	std::vector<GeoMath::v3> list,
	double                   course)
{
	std::size_t                      size = list.size();
	std::vector<GeoMath::v3geo> res(size);
	for (std::size_t i = 0; i < size; i++)
	{
		res[i] = point;
		for (std::size_t j = 0; j <= i; j++)
		{
			res[i] = res[i] + list[j];
		}
	}
	return res;
}

std::vector<GeoMath::v3>
GeoMath::absPosList(std::vector<GeoMath::v3> list,
	double                   course,
	GeoMath::v3              point)
{
	std::size_t                 size = list.size();
	std::vector<GeoMath::v3> res(size);
	for (std::size_t i = 0; i < size; i++)
	{
		res[i] = point;
		for (std::size_t j = 0; j <= i; j++)
		{
			res[i] = res[i] + list[j];
		}
	}
	return res;
}

GeoMath::RouteLine::RouteLine()
	:points(1)
{
	points[0] = v3(0, 0, 0);
}

bool 
GeoMath::RouteLine::append(v3 point, Notion notion)
{
	switch (notion)
	{
	case GeoMath::RouteLine::Centre:
		points.push_back(point);
		break;

	case GeoMath::RouteLine::Chain:
		points.push_back(points.back() + point);
		break;
	}
	return true;
}

GeoMath::v3 GeoMath::RouteLine::at(unsigned long i, Notion notion)
{
	return points[i];
}

std::vector<GeoMath::v3> GeoMath::RouteLine::get_points()
{
	return std::vector<GeoMath::v3>(points);
}

bool GeoMath::RouteLine::rotate(double rad, Axis axis, Hand hand)
{
	for (std::size_t i = 0; i < points.size(); i++)
	{
		points[i]=points[i].rotate(rad, axis, hand);
	}
	return true;
}

std::vector<GeoMath::v3geo> GeoMath::RouteLine::absPosition(v3geo home)
{
	std::size_t size = points.size();
	std::vector<GeoMath::v3geo> res(size);

	for (std::size_t i = 0; i < size; i++)
	{
		res[i] = home + points[i];
	}

	return res;
}

GeoMath::RouteLine::~RouteLine()
{
}
