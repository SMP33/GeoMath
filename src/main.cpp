#include "../lib_src/GeoMath.h"

#include "server.h"


using namespace GeoMath;
using namespace std;



int main(int argc, char* argv[])
{	
	SimpleServer host(5000);
	
	quat q(0.958824, 0.00815178, -2.84799e-06, -0.283883);
	
	cout << q.to_eul() << endl;
	cout << q << endl;
	q = { q.to_eul() };
	cout << q << endl;
	
	

	v3 dir = v3(1, 0, 0).normalize_xyz(1);
	
	v3 rot_vec(0, 0, 0);
	
	dir = dir.rotate(q.to_eul());
	
	while (true)
	{
		stringstream out;
		usleep(1e5);
		
		dir = dir.rotate(rot_vec);	
		out << dir << endl;
		host.set_response(out.str());
		
	}
	
	return 0;
}
