#include <stdio.h>
#include "circle.h"
#include "point.h"
#include <locale.h>

int main(){
	setlocale(LC_ALL, "Portuguese");
	int x_tmp, y_tmp, r_tmp;
	POINT* a_point;
	CIRCLE* a_circle;
	float dist;

	scanf("%d %d", &x_tmp, &y_tmp);
	a_point = new_point(x_tmp, y_tmp);
	scanf("%d %d %d", &x_tmp, &y_tmp, &r_tmp);
	a_circle = new_circle(x_tmp, y_tmp, r_tmp);

	dist = circle_point_dist(a_point, a_circle);

	if (dist < get_circle_radius(a_circle)) printf("O ponto é interior à circunferência.\nDistância: %.2f\n", dist);
	else if (dist > get_circle_radius(a_circle)) printf("O ponto é exterior à circunferência.\nDistância: %.2f\n", dist);
	else printf("O ponto pertence à circunferência.\nDistância: %.2f\n", dist);

	return 0;
}
