#include <GeoMath.h>
#include <iostream>
#include <unistd.h>

using namespace GeoMath;

int main(int argc, char* argv[])
{
	
	std::cout<<argv[0]<<std::endl;
	v2 v_2(1, 2);
	std::cout << v_2 << std::endl;
	v3 v_3(1,2,3);
	std::cout<<v_3<<std::endl;
	
	RouteTemplate2D line;
	
	for(int i=1;i<=11;i++)
	line.add_next(RouteTemplate2D::OFFSET, v2(i, i*i));
	
	for (int i = 0; i < line.size(); i++) ;
	
	
return 0;
}
