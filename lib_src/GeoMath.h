#pragma once

#include <math.h>
#include <vector>
#include <ostream>
#include <iostream>
#include <algorithm>


///Возвращает 1, если число >=0, иначе -1
double sign(double arg);

namespace GeoMath
{
	/*!
	@brief Объявление используемых констант
	*/
	static  struct
	{
		const double Pi = 3.1415926535897932384626433832795;    ///< число Пи

		const double E_EARTH = 6378137.0;   	///< Экваториальный радиус Земли
		const double P_EARTH = 6356779.0;   	///< Полярный радиус Земли

		const double E_length = E_EARTH * 2 * Pi;   	///< Удвоенная длина меридиана
		const double P_length = P_EARTH * 2 * Pi;   	///< Длина экватора

		const double M_IN_LAT = P_length / 360;   	///< Число метров в одном градусе широты
		const double M_IN_LNG = E_length / 360;   	///< Число метров в одном градусе долготы

		const double DEG2RAD = 0.01745329252;   	///< Коэффициент преобразования градусов в радианы
		const double RAD2DEG = 57.2957795129;   	///< Коэффициент преобразования градиан в градусы
	} CONST;

	/// Оси
	enum Axis
	{
		X,   	///< Направление с Юга на Север
		Y,   	///< Направление с Запада на Восток
		Z	///< Направление вверх
	}
	;

	
	/// Вращение задается по правилу правой руки, либо по правилу левой руки
	enum Hand
	{
		LEFT,   	///< По правилу левой руки
		RIGHT	///< По правилу правой руки
	}
	;
	
	enum PositionType ///< Указывает, как именно задано смещение либо положение
	{
		OFFSET,
		///< Указывает, что положение задано относительно предыдущей точки
	  HOME	///< Указывает, что положение задано относительно домашней точки
	};

	/// Двумерный вектор
	class v2
	{
	public:
		double x;
		double y;

		v2(double x_ = 0, double y_ = 0);

		bool isNull();
		double	length_xy();
		double	length();
		double angle_xy(v2 v);

		v2 normalize_xy(double abs);
		v2 rotateXY(double rad);

		v2 operator+(v2 const& v);
		v2 operator-(v2 const& v);
		v2 operator*(double factor);
		v2 operator/(double factor);
		
		bool operator ==(v2 const& p2);
		
		friend std::ostream& operator<<(std::ostream& os, const GeoMath::v2& at);

	}
	;
	
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
		double	length();
		double angle_xy(v3 v);

		v3 normalize_xy(double abs);
		v3 normalize_xyz(double abs);
		v3 rotateXY(double rad);

		v3 rotate(double rad, Axis axis, Hand hand = RIGHT);
		v3 rotate(double rad, Axis axis, v3 from_point, Hand hand = RIGHT);

		v3 operator+(v3 const& v2);
		v3 operator-(v3 const& v2);
		v3 operator*(double factor);
		v3 operator/(double factor);
		
		bool operator ==(v3 const& v);
		
		friend std::ostream& operator<<(std::ostream& os, const GeoMath::v3& at);

	};

	
	class v2geo
	{
	public:
		double lat;
		double lng;
		
		bool isNull();
		
		v2geo(double lat_ = 0, double lng_ = 0);

		v2 operator-(v2geo const& p2);
		v2geo operator+(v2 const& p2);
		bool operator ==(v2geo const& p2);
		
		friend std::ostream& operator<<(std::ostream& os, const GeoMath::v2geo& at);
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
		bool operator ==(v3geo const& p2);
		
		friend std::ostream& operator<<(std::ostream& os, const GeoMath::v3geo& at);
	};

	template <typename T>
		class LineSegment
		{
		public:
			LineSegment(T P1_, T P2_)
				: P1(P1_)
				, P2(P2_)
			{
			}
			LineSegment()
			{
			}
			~LineSegment()
			{
			}
	
			T P1;
			T P2;
		
			auto vec()
			{
				return P2 - P1;
			}
		
			double length_xy()
			{
				return vec().length_xy();
			}
			double length()
			{
				return vec().length();
			}
		
			bool is_cross_xy(LineSegment<T> l2, bool crossed_if_match_up = false)
			{
				LineSegment<T> l1 = *this;
				auto v1 = l2.vec();
				auto v2 = l2.P2 - l1.P1;
				auto v3 = l2.P2 - l1.P2;
				
				double angle_1, angle_2;
				int sign_1, sign_2;
				
				angle_1 = v1.angle_xy(v2);
				angle_2 = v1.angle_xy(v3);
				
//				std::cout << angle_1 << " " << angle_2 << std::endl;
//				std::cout << v2.length_xy()*sin(angle_1) << " " << v3.length_xy()*sin(angle_2) << std::endl;
				
				if (angle_1 > 0)
					sign_1 = 1;
				else
					if (angle_1 < 0)
					sign_1 = -1;		
				else
					sign_1 = 0;
				
				if (angle_2 > 0)
					sign_2 = 1;
				else
					if (angle_2 < 0)
					sign_2 = -1;		
				else
					sign_2 = 0;
				
				
				
				if ((sign_2 == sign_1) || (!crossed_if_match_up&&(sign_2 == 0 || sign_1 == 0)))
					return false;
				else
					return true;			
			}
			
		};



	
}

