#include "triangles.hh"

struct triangle_type
{
	point1;
	point2;
	point3;	
};

int check_illegal(tri_t triangle1, tri_t triangle2)
{
	tri_t maybeTriangle1, maybeTriangle2;
	maybeTriangle1 = makeNewTriangle(triangle1, triangle2).tr1;
	maybeTriangle1 = makeNewTriangle(triangle1, triangle2).tr2;

	if(min_ang(get_angles(triangle1, triangle2)) < min_ang(get_angles(maybeTriangle1, maybeTriangle2)))
	{
		//Illegal configuration
		return 666;
	}
	else
	{
		//Legal combination
		return 0;
	}

}

void flip_edges()
{


	
}