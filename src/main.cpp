#include "../lib_src/GeoMath.h"

#include <iostream>
#include <unistd.h>

using namespace GeoMath;
using namespace std;

int main(int argc, char* argv[])
{	
	RouteTemplate2D heart_1;
	
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(2, -2));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(2, -4));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(0, -4));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(1, -2));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(1, -1));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(2, -2));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(6, 0));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(2, 1));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(2, 2));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(1, 3));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(-1, 2)); // p2
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(4, 2));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(1, 2));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(1, 4));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(-1, 2));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(-1, 1));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(-3, 1));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(-5, 1));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(-4, -1));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(-3, -1));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(-4, -2));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(-1, -1));
//	heart_1.add_next(RouteTemplate2D::OFFSET, v2(-2, -1));
//	heart_1.add_next(RouteTemplate2D::HOME, v2(0, 0));
	
	heart_1.add_next(RouteTemplate2D::HOME, v2(6, -6));
	heart_1.add_next(RouteTemplate2D::HOME, v2(9, -6));
	heart_1.add_next(RouteTemplate2D::HOME, v2(11, -4));
	heart_1.add_next(RouteTemplate2D::HOME, v2(11, -2));
	heart_1.add_next(RouteTemplate2D::HOME, v2(9, 0));
	heart_1.add_next(RouteTemplate2D::HOME, v2(11, 2));
	heart_1.add_next(RouteTemplate2D::HOME, v2(11, 4));
	heart_1.add_next(RouteTemplate2D::HOME, v2(9, 6));
	heart_1.add_next(RouteTemplate2D::HOME, v2(6, 6));
	heart_1.add_next(RouteTemplate2D::HOME, v2(0, 0));
	
	
	//line.set_reference_points(v3geo(55.894184, 37.250316, 0), 0, v3geo(55.894574, 37.250208, 0), 11);
	heart_1.set_reference_points(v2(0, 0), 0, v2(10, 0), 4);
	
	RouteLine line;
	
	for (size_t i = 0; i <heart_1.size(); i++)
	{
		cout << v3geo(55.894184, 37.250316, 0)+ heart_1[i].home << endl;
		line.add_next(heart_1[i].home, RouteLine::HOME);
	}

	

	
	
return 0;
}
