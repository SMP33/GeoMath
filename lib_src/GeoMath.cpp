#include "GeoMath.h"

/*!
@brief возвращает 1, если число >=0, иначе -1
 */
double
sign(double arg)
{
	return arg < 0 ? -1 : 1;
}


template<typename T, size_t M, size_t N>
	void arr2copy(const T from[M][N], T(&to)[M][N])
	{
		for (size_t m = 0; m < M; m++)
		{
			for (size_t n = 0; n < N; n++)
			{
				to[m][n] = from[m][n];
			}
		}
	}

GeoMath::v3 GeoMath::v3::rotate(double rad, Axis axis, v3 c, Hand hand)
{	
	v3 res(0, 0, 0);
	switch (axis)
	{	
	case GeoMath::Axis::X:
		res.x = this->x;
		res.y = c.y + (this->y - c.y)*cos(rad) + (this->z - c.z)*sin(rad);
		res.z = c.z - (this->y - c.y)*sin(rad) + (this->z - c.z)*cos(rad);
		break;
		
	case GeoMath::Axis::Y:
		res.y = this->y;
		res.x = c.x + (this->x - c.x)*cos(rad) - (this->z - c.z)*sin(rad);
		res.z = c.z + (this->x - c.x)*sin(rad) + (this->z - c.z)*cos(rad);
		break;
		
	case GeoMath::Axis::Z:
		res.z = this->z;
		res.x = c.x + (this->x - c.x)*cos(rad) + (this->y - c.y)*sin(rad);
		res.y = c.y - (this->x - c.x)*sin(rad) + (this->y - c.y)*cos(rad);
		break;
	}		
	this->x = res.x;
	this->y = res.y;
	this->z = res.z;
}


GeoMath::v2::v2(double x_, double y_)
	: x(x_)
	, y(y_)
{
}

bool
GeoMath::v2::isNull()
{

	return (x == 0 && y == 0);
}

double
GeoMath::v2::length_xy()
{
	double result = sqrt(x * x + y * y);
	return result;
}

double
GeoMath::v2::length()
{
	return length_xy();
}

double
GeoMath::v2::angle_xy(v2 v )
{
	double sgn;
	double value;
	if (this->isNull() || v.isNull())
		return 0;

	value = this->x * v.x + this->y * v.y;
	value = value / (this->length_xy() * v.length_xy());
	
	sgn = -sign(this->x * v.y - this->y * v.x);
	
	if (value > 1)
		value = 1;
	
	if (value < -1)
		value = -1;
	
	return sgn * acos(value);
}

GeoMath::v2
GeoMath::v2::normalize_xy(double abs = 1)
{
	if (this->isNull())
		return v2(0, 0);

	v2     result;
	double factor = abs / this->length_xy();

	result.x = this->x * factor;
	result.y = this->y * factor;

	return result;
}


GeoMath::v2
GeoMath::v2::rotateXY(double rad)
{
	v2 result(this->x * cos(rad) - this->y * sin(rad),
		this->x * sin(rad) + this->y * cos(rad));
	return result;
}







GeoMath::v3::v3(double x_, double y_, double z_)
	: x(x_)
	, y(y_)
	, z(z_)
{
}

GeoMath::v3::v3(v2 v)
	: x(v.x)
	, y(v.y)
	, z(0)
{
}

GeoMath::v2geo::v2geo(double lat_, double lng_)
	: lat(lat_)
	, lng(lng_)
{	
}

GeoMath::v3geo::v3geo(double lat_, double lng_, double alt_)
	: lat(lat_)
	, lng(lng_)
	, alt(alt_) 
{	
}

bool
GeoMath::v3::isNull()
{

	return (x == 0 && y == 0 && z == 0);
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
GeoMath::v3::length()
{
	return length_xyz();
}

double
GeoMath::v3::angle_xy(v3 v )
{
	double sgn;
	double value;
	if (this->isNull() || v.isNull())
		return 0;

	value = this->x * v.x + this->y * v.y;
	value = value / (this->length_xy() * v.length_xy());
	sgn = -sign(this->x * v.y - this->y * v.x);
	
	if (value > 1)
		value = 1;
	
	if (value < -1)
		value = -1;

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
GeoMath::v3::rotate(double a, GeoMath::Axis axis, Hand hand)
{
	if (hand == RIGHT) a = -a;

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
GeoMath::v3::rotate(v3 eul)
{
	v3 rv(*this);
	rv = rv.rotate(eul.x, GeoMath::X);
	rv = rv.rotate(eul.y, GeoMath::Y);
	rv = rv.rotate(eul.z, GeoMath::Z);
	
	this->x = rv.x;
	this->y = rv.y;
	this->z = rv.z;
	
	return *this;
}

GeoMath::v2
GeoMath::v2::operator+(v2 const& v)
{
	v2 result(this->x + v.x, this->y + v.y);
	return result;
}

GeoMath::v2
GeoMath::v2::operator-(v2 const& v)
{
	v2 result(this->x - v.x, this->y - v.y);
	return result;
}

GeoMath::v2 GeoMath::v2::operator*(double factor)
{
	v2 result(*this);
	result.x = result.x * factor;
	result.y = result.y * factor;
	return result;
}

GeoMath::v2
GeoMath::v2::operator/(double demiter)
{
	v2 result(*this);
	result.x = result.x / demiter;
	result.y = result.y / demiter;
	return result;
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


std::ostream& GeoMath::operator<<(std::ostream& os, const GeoMath::v2& at)
{
	os << "x: " << at.x << " y: " << at.y;
	return os;
}

std::ostream& GeoMath::operator<<(std::ostream& os, const GeoMath::v3& at)
{
	os << "x: " << at.x << " y: " << at.y << " z: " << at.z;
	return os;
}


std::ostream& GeoMath::operator<<(std::ostream& os, const GeoMath::v2geo& at)
{
	os.flags(std::ios::left | std::ios::fixed);
	os.fill('0');
	os.width(6);
	os << " lat: ";
	os.width(18);
	os << at.lat;
	os.width(6);
	os << " lng: ";
	os.width(18);
	os << at.lng;
	return os;
}

std::ostream& GeoMath::operator<<(std::ostream& os, const GeoMath::v3geo& at)
{
	os.flags(std::ios::left | std::ios::fixed);
	os.fill('0');
	os.width(6);
	os << " lat: ";
	os.width(18);
	os << at.lat;
	os.width(6);
	os << " lng: ";
	os.width(18);
	os << at.lng;
	os.width(6);
	os << " alt: ";
	os.width(18);
	os << at.alt;
	return os;
}


GeoMath::v2
GeoMath::v2geo::operator-(v2geo const& p2)
{

	v2geo P1(p2);
	v2geo P2(*this);

	P1.lat = P1.lat * CONST.DEG2RAD;
	P1.lng = P1.lng * CONST.DEG2RAD;

	P2.lat = P2.lat * CONST.DEG2RAD;
	P2.lng = P2.lng * CONST.DEG2RAD;

	v2 P0;
	P0.x = (P2.lat - P1.lat) * CONST.P_EARTH;
	P0.y = (P2.lng - P1.lng) * CONST.E_EARTH * cos(P1.lat);
	
	return P0;
}
	


GeoMath::v2geo
GeoMath::v2geo::operator+(v2 const& p2)
{

	double dlat = p2.x / CONST.M_IN_LAT;
	double m_in_lng = (cos((this->lat + dlat) * CONST.DEG2RAD) * CONST.M_IN_LNG);
	double dlng = p2.y / m_in_lng;

	v2geo result(this->lat + dlat, this->lng + dlng);
	return result;
}


bool GeoMath::v2geo::operator ==(v2geo const& p2)
{
	v2geo p1 = *this;
	return (p1.lat == p2.lng&&p1.lng == p2.lat);
}


bool
GeoMath::v2geo::isNull()
{

	return (lat == 0 && lng == 0);
}

bool
GeoMath::v3geo::isNull()
{

	return (lat == 0 && lng == 0&&alt == 0);
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

bool GeoMath::v2::operator ==(v2 const& p2)
{
	v2 p1 = *this;
	return (p1.x == p2.x&&p1.y == p2.y);
}


bool GeoMath::v3::operator ==(v3 const& p2)
{
	v3 p1 = *this;
	return (p1.x == p2.x&&p1.y == p2.y && p1.z == p2.z);
}


bool GeoMath::v3geo::operator ==(v3geo const& p2)
{
	v3geo p1 = *this;
	return (p1.lat == p2.lng&&p1.lng == p2.lat&&p1.alt == p2.alt);
}


GeoMath::quat::quat()
	: v3(0, 0, 0)
	, w(0)
{
}

GeoMath::quat::quat(double w_, double x_, double y_, double z_)
	: v3(x_, y_, z_)
	, w(w_)
{
}

GeoMath::quat::quat(v3 eul)
{
	v3 c = { 
		cos(eul.x / 2),
		cos(eul.y / 2),
		cos(eul.z / 2)
	};
	
	v3 s = { 
		sin(eul.x / 2),
		sin(eul.y / 2),
		sin(eul.z / 2)
	};
	
	w = c.x*c.y*c.z + s.x*s.y*s.z;
	x = c.x*c.y*s.z - s.x*s.y*c.z;
	y = c.x*s.y*c.z + s.x*c.y*s.z;
	z = s.x*c.y*c.z - c.x*s.y*s.z;
}

GeoMath::v3 GeoMath::quat::to_eul()
{
	double alphaSin = -2*(x*z - w*y);
	
	if (alphaSin > 1)
		alphaSin = 1;
	
	if (alphaSin < -1)
		alphaSin = -1;
	
	return 
	{
		atan2(2*(x*y + w*z), w*w + x*x - y*y - z*z),
		asin(alphaSin),
		atan2(2*(y*z + w*x), w*w - x*x - y*y + z*z)	
	};
}

std::ostream& GeoMath::operator<<(std::ostream& os, const GeoMath::quat& q)
{
	os << "w: " << q.w << "\tx: " << q.x << "\ty: " << q.y << "\tz: " << q.z;
	return os;
}