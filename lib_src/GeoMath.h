#pragma once

#include <math.h>
#include <vector>
double sign(double arg);

namespace GeoMath
{
	static  struct
	{
		const double Pi = 3.1415926535897932384626433832795;

		const double E_EARTH = 6378137.0;
		const double P_EARTH = 6356779.0;

		const double E_length = E_EARTH * 2 * Pi;
		const double P_length = P_EARTH * 2 * Pi;

		const double M_IN_LAT = P_length / 360;
		const double M_IN_LNG = E_length / 360;

		const double DEG2RAD = 0.01745329252;
		const double RAD2DEG = 57.2957795129;
	} CONST;
	enum Axis
	{
		X, Y, Z
	};
	enum Hand
	{
		LEFT,
		RIGHT
	};
	class v3
	{
	public:
		double x;
		double y;
		double z;

		v3(double x_ = 0, double y_ = 0, double z_ = 0);

		bool isNull();
		double	length_xy();
		double	length_xyz();
		double angle_xy(v3 v);

		v3 normalize_xy(double abs);
		v3 normalize_xyz(double abs);
		v3 rotateXY(double rad);

		v3 rotate(double rad, Axis axis,Hand hand=RIGHT);

		v3 operator+(v3 const& v2);
		v3 operator-(v3 const& v2);
		v3 operator*(double factor);
		v3 operator/(double factor);

	};

	class v3geo
	{
	public:
		double lat;
		double lng;
		double alt;
		v3geo(double lat_ = 0, double lng_ = 0, double alt_ = 0);

		v3 operator-(v3geo const& v2);
		v3geo operator+(v3 const& v2);
	};


	class RouteLine
	{
	public:
		enum Notion
		{
			Centre,
			Chain
		};
		std::vector<v3> points;//points in Centre notion
		bool append(v3 point, Notion notion);
		v3 at(unsigned long i, Notion notion);
		std::vector<v3> get_points();
		bool rotate(double rad, Axis axis, Hand hand = RIGHT);
		std::vector<v3geo> absPosition(v3geo home);
		RouteLine();
		~RouteLine();

	private:

	};

	





	std::vector<v3geo>
		absPosListGeo(v3geo  point, std::vector<v3> list, double course);

	std::vector<v3>
		absPosList(std::vector<v3> list,
			double          course,
			v3              point = GeoMath::v3(0, 0, 0));

}

