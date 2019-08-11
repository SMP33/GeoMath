#include "../lib_src/GeoMath.h"

namespace GeoMath
{
    class FigureTemplate2D
	{
	public:
		
		enum TemplateState
		{
			NOT_SELECT,
			ABSOLUT,
			METERS
		};
		
		
		struct Position
		{
			GeoMath::v2 offset;
			GeoMath::v2 home;
			GeoMath::v3geo abs;
		};
		
		FigureTemplate2D();
		FigureTemplate2D(const FigureTemplate2D& route);
		~FigureTemplate2D();
		
		void add_next(PositionType position,v2 point);
		
		TemplateState state;
		Position at(int i);
		int size();
		Position operator[](const int i);
		bool set_reference_points(v3geo abs1, int index_1, v3geo abs2, int index_2);
		bool set_reference_points(v2 p1, int index_1, v2 p2, int index_2);
		
		GeoMath::v2 get_home_meters();
	private:
		
		GeoMath::v3geo home_abs;
		GeoMath::v2 home_meters;
		
		GeoMath::v3geo reference_point_1_abs;
		GeoMath::v3geo reference_point_2_abs;
		
		GeoMath::v3 reference_point_1_meters;
		GeoMath::v3 reference_point_2_meters;
		
		float course;
		float scale;
		

		std::vector<GeoMath::v2> point_offset;
		std::vector<GeoMath::v2> point_home;
		
		
	};


	
	class SimpleFigure3D
	{
	public:
		
		struct Position
		{
			GeoMath::v3 offset;
			GeoMath::v3 home;
		};
		
		SimpleFigure3D();
		~SimpleFigure3D();
		
		void add_next(PositionType position, v3 point);
		Position at(int i);		
		int size();
		void rotate(double rad, Axis axis, v3 from_point, Hand hand = RIGHT);
		Position operator[](const int i);
		
		GeoMath::v3 center();

	private:
		std::vector<GeoMath::v3> point_offset;
		std::vector<GeoMath::v3> point_home;
	};
}