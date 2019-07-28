#include "../lib_src/GeoMath.h"

#include <iostream>
#include <unistd.h>

using namespace GeoMath;
using namespace std;

int main(int argc, char* argv[])
{	
	RouteTemplate2D heart_1;
	
	//	heart_1.add_next(OFFSET, v2(2, -2));
	//	heart_1.add_next(OFFSET, v2(2, -4));
	//	heart_1.add_next(OFFSET, v2(0, -4));
	//	heart_1.add_next(OFFSET, v2(1, -2));
	//	heart_1.add_next(OFFSET, v2(1, -1));
	//	heart_1.add_next(OFFSET, v2(2, -2));
	//	heart_1.add_next(OFFSET, v2(6, 0));
	//	heart_1.add_next(OFFSET, v2(2, 1));
	//	heart_1.add_next(OFFSET, v2(2, 2));
	//	heart_1.add_next(OFFSET, v2(1, 3));
	//	heart_1.add_next(OFFSET, v2(-1, 2)); // p2
	//	heart_1.add_next(OFFSET, v2(4, 2));
	//	heart_1.add_next(OFFSET, v2(1, 2));
	//	heart_1.add_next(OFFSET, v2(1, 4));
	//	heart_1.add_next(OFFSET, v2(-1, 2));
	//	heart_1.add_next(OFFSET, v2(-1, 1));
	//	heart_1.add_next(OFFSET, v2(-3, 1));
	//	heart_1.add_next(OFFSET, v2(-5, 1));
	//	heart_1.add_next(OFFSET, v2(-4, -1));
	//	heart_1.add_next(OFFSET, v2(-3, -1));
	//	heart_1.add_next(OFFSET, v2(-4, -2));
	//	heart_1.add_next(OFFSET, v2(-1, -1));
	//	heart_1.add_next(OFFSET, v2(-2, -1));
	//	heart_1.add_next(HOME, v2(0, 0));
	
		heart_1.add_next(HOME, v2(6, -6));
		heart_1.add_next(HOME, v2(9, -6));
		heart_1.add_next(HOME, v2(11, -4));
		heart_1.add_next(HOME, v2(11, -2));
		heart_1.add_next(HOME, v2(9, 0));
		heart_1.add_next(HOME, v2(11, 2));
		heart_1.add_next(HOME, v2(11, 4));
		heart_1.add_next(HOME, v2(9, 6));
		heart_1.add_next(HOME, v2(6, 6));
		heart_1.add_next(HOME, v2(0, 0));
		
		
		
		heart_1.set_reference_points(v2(0, 0), 0, v2(20, 0), 5);
		
		RouteLine line;
		SimpleFigure3D fig;
	
		for (size_t i = 0; i <heart_1.size(); i++)
		{
			//cout << v3geo(55.894184, 37.250316, 0)+ heart_1[i].home << endl;
			fig.add_next(HOME, heart_1[i].home);
		}

	
		//fig.rotate(90*CONST.DEG2RAD, Y, v3(0, 0, 0));
		for (size_t i = 0; i < fig.size(); i++)
		{
			cout << v3geo(55.894184, 37.250316, 10) + fig[i].home << endl;
		}
		
	cout << v3geo(55.894184, 37.250316, 10)+fig.center() << endl;
return 0;
}
