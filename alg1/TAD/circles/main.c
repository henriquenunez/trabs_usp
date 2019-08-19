#include <stdio.h>
#include "circle.h"
#include "point.h"
#include <locale.h>

int main(){
	setlocale(LC_ALL, "Portuguese");
	float x_tmp, y_tmp, r_tmp;
	POINT* a_point;
	CIRCLE* a_circle;
	float dist;

	scanf("%f %f", &x_tmp, &y_tmp);
	a_point = new_point(x_tmp, y_tmp);
	scanf("%f %f %f", &x_tmp, &y_tmp, &r_tmp);
	a_circle = new_circle(x_tmp, y_tmp, r_tmp);

	dist = circle_point_dist(a_point, a_circle);

	//printf("%f\n", area_circle(a_circle));
	//printf("%f : %f\n", get_coordinates(a_point, 0), get_coordinates(a_point, 1));

	if (dist < get_circle_radius(a_circle)) printf("O ponto é interior à circunferência.\nDistância: %.2f\n", dist);
	else if (dist > get_circle_radius(a_circle)) printf("O ponto é exterior à circunferência.\nDistância: %.2f\n", dist);
	else printf("O ponto pertence à circunferência.\nDistância: %.2f\n", dist);

	return 0;
}
