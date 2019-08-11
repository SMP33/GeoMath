#include "Figure.h"


GeoMath::FigureTemplate2D::FigureTemplate2D():
	reference_point_1_abs(0,0,0),
	reference_point_2_abs(0,0,0),
	reference_point_1_meters(0,0,0),
	reference_point_2_meters(0,0,0),
	state(GeoMath::FigureTemplate2D::NOT_SELECT),
	home_abs(0,0,0),
	home_meters(0,0),
	point_offset(1),
	point_home(1),
	scale(1),
	course(0)
{
	point_offset[0] = GeoMath::v2(0, 0);
	point_home[0] = GeoMath::v2(0, 0);
}

GeoMath::FigureTemplate2D::FigureTemplate2D(const FigureTemplate2D& route):
	reference_point_1_abs(0,0,0),
	reference_point_2_abs(0,0,0),
	reference_point_1_meters(0,0,0),
	reference_point_2_meters(0,0,0),
	state(GeoMath::FigureTemplate2D::NOT_SELECT),
	home_abs(0,0,0),
	home_meters(0,0),
	point_offset(route.point_offset),
	point_home(route.point_home),
	scale(1),
	course(0)
{
}

void GeoMath::FigureTemplate2D::add_next(PositionType position_type, v2 point)
{
	v2 home;
	v2 offset;
	switch (position_type)
	{
	case PositionType::HOME:
		
		home = point;
		offset = point_home.back() - home;
		
		break;
		
	case PositionType::OFFSET:
		
		offset = point;
		home = point_home.back() + offset;
		
		break;
	}
	
	point_home.push_back(home);
	point_offset.push_back(offset);
}

GeoMath::FigureTemplate2D::Position GeoMath::FigureTemplate2D::at(int i)
{
	Position pos;
	
	pos.home = point_home[i];
	pos.home = pos.home.rotateXY(course)*scale;
	
	pos.offset = point_offset[i];
	pos.offset = pos.offset.rotateXY(course)*scale;
	
	if (state == GeoMath::FigureTemplate2D::ABSOLUT)
		pos.abs = home_abs + pos.home;
	else
		pos.abs = v3geo(0, 0, 0);
	
	return pos;
}

GeoMath::FigureTemplate2D::Position GeoMath::FigureTemplate2D::operator[](const int i)
{
	return at(i);
}

int GeoMath::FigureTemplate2D::size()
{
	return point_home.size();
}

int GeoMath::SimpleFigure3D::size()
{
	return point_home.size();
}


GeoMath::FigureTemplate2D::~FigureTemplate2D()
{
}

bool GeoMath::FigureTemplate2D::set_reference_points(v3geo abs1, int index_1, v3geo abs2, int index_2)
{
	if (state != GeoMath::FigureTemplate2D::NOT_SELECT)
		return false;
	
	int size = this->size();
	if (index_1 >= size || index_2 >= size) 
		return false;
	
	if (abs1 == abs2)
		return false;
	
	if (index_1 == index_2)
		return false;
	
	v3 offset_abs_3d = abs2 - abs1;
	v2 offset_abs = v2(offset_abs_3d.x, offset_abs_3d.y);
	
	v2 p1 = point_home[index_1];
	v2 p2 = point_home[index_2];	
	v2 offset = p2 - p1;
	
	scale = offset_abs.length_xy() / offset.length_xy();
	course = offset_abs.angle_xy(offset);
	
	home_abs = abs1 +(p1.rotateXY(course)*scale*(-1));
	
	state = GeoMath::FigureTemplate2D::ABSOLUT;
	return true;
}

bool GeoMath::FigureTemplate2D::set_reference_points(v2 r1, int index_1, v2 r2, int index_2)
{
	if (state != GeoMath::FigureTemplate2D::NOT_SELECT)
		return false;
	
	int size = this->size();
	if (index_1 >= size || index_2 >= size) 
		return false;
	
	if (r1 == r2)
		return false;
	
	if (index_1 == index_2)
		return false;
	
	v3 offset_abs_3d = r2 - r1;
	v2 offset_abs = v2(offset_abs_3d.x, offset_abs_3d.y);
	
	v2 p1 = point_home[index_1];
	v2 p2 = point_home[index_2];	
	v2 offset = p2 - p1;
	
	scale = offset_abs.length_xy() / offset.length_xy();
	course = offset_abs.angle_xy(offset);
	
	home_meters = r1 + (p1.rotateXY(course)*scale*(-1));
	
	state = GeoMath::FigureTemplate2D::METERS;
	return true;
}

GeoMath::v2 GeoMath::FigureTemplate2D::get_home_meters()
{
	return home_meters;
}

GeoMath::SimpleFigure3D::SimpleFigure3D():
	point_home(1),
	point_offset(1)
{
	
}

void
GeoMath::SimpleFigure3D::add_next(PositionType position_type, v3 point)
{
	v3 home;
	v3 offset;
	switch (position_type)
	{
	case PositionType::HOME:
		
		home = point;
		offset = point_home.back() - home;
		
		break;
		
	case PositionType::OFFSET:
		
		offset = point;
		home = point_home.back() + offset;
		
		break;
	}
	
	point_home.push_back(home);
	point_offset.push_back(offset);
}

GeoMath::SimpleFigure3D::Position GeoMath::SimpleFigure3D::at(int i)
{
	Position pos;
	
	pos.home = point_home[i];
	pos.offset = point_offset[i];
	
	return pos;
}

GeoMath::SimpleFigure3D::Position GeoMath::SimpleFigure3D::operator[](const int i)
{
	return at(i);
}

GeoMath::SimpleFigure3D::~SimpleFigure3D()
{
}

void GeoMath::SimpleFigure3D::rotate(double rad, Axis axis, v3 from_point, Hand hand )
{
	for (std::size_t i = 0; i < size(); i++)
	{
		point_offset[i].rotate(rad, axis, from_point, hand);
		point_home[i].rotate(rad, axis, from_point, hand);
	}
}

GeoMath::v3 GeoMath::SimpleFigure3D::center()
{
	auto max_x = std::max_element(point_home.begin(), point_home.end(),[] (v3 const& l, v3 const& r) {return l.x < r.x;});
	auto max_y = std::max_element(point_home.begin(), point_home.end(),[] (v3 const& l, v3 const& r) {return l.y < r.y;});
	auto max_z = std::max_element(point_home.begin(), point_home.end(),[] (v3 const& l, v3 const& r) {return l.z < r.z;});
	
	auto min_x = std::min_element(point_home.begin(), point_home.end(), [](v3 const& l, v3 const& r) {return l.x < r.x;});
	auto min_y = std::min_element(point_home.begin(), point_home.end(), [](v3 const& l, v3 const& r) {return l.y < r.y;});
	auto min_z = std::min_element(point_home.begin(), point_home.end(), [](v3 const& l, v3 const& r) {return l.z < r.z;});
	
	double x = (*max_x + *min_x).x/2;
	double y = (*max_y + *min_y).y/2;
	double z = (*max_z + *min_z).z/2;
	
	return v3(x,y,z);
}