#pragma once

#include <math.h>
#include <vector>
#include <ostream>

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
	
	
	class v2
	{
	public:
		double x;
		double y;

		v2(double x_ = 0, double y_ = 0);

		bool isNull();
		double	length_xy();
		double	length_xyz();
		double angle_xy(v2 v);

		v2 normalize_xy(double abs);
		v2 rotateXY(double rad);

		v2 operator+(v2 const& v);
		v2 operator-(v2 const& v);
		v2 operator*(double factor);
		v2 operator/(double factor);
		
		friend std::ostream& operator<<(std::ostream& os, const GeoMath::v2& at);

	};
	
	class v3
	{
	public:
		double x;
		double y;
		double z;

		v3(double x_ = 0, double y_ = 0, double z_ = 0);
		v3(v2 v);

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
		
		friend std::ostream& operator<<(std::ostream& os, const GeoMath::v3& at);

	};

	class v3geo
	{
	public:
		double lat;
		double lng;
		double alt;
		
		bool isNull();
		
		v3geo(double lat_ = 0, double lng_ = 0, double alt_ = 0);

		v3 operator-(v3geo const& v2);
		v3geo operator+(v3 const& v2);
		
		friend std::ostream& operator<<(std::ostream& os, const GeoMath::v3geo& at);
	};

	
	
	
	
	
	

	
	class RouteTemplate2D
	{
	public:
		enum PositionType
		{
			OFFSET,
			HOME
		};
		
		struct Position
		{
			GeoMath::v2 offset;
			GeoMath::v2 home;
			GeoMath::v3geo abs;
		};
		
RouteTemplate2D();
		~RouteTemplate2D();
		
		GeoMath::v3geo home_abs;
		GeoMath::v3geo reference_point;
		
		void add_next(PositionType position,v2 point);
		
		Position at(int i);
		int size();
	private:
		
		float course;
		float scale;
		
		GeoMath::v3geo calc_abs(int i);
		std::vector<GeoMath::v2> point_offset;
		std::vector<GeoMath::v2> point_home;
		
		Position operator[](const int i);
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

