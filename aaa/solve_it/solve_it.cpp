#include <iostream>
#include <iomanip>
#include <cmath>
//#include <unistd.h>
#include <cstdio>

#define ERROR 0.0000001
const double EPSILON = 1e-15;

//int counter = 0;

double compute_equation(double x,
			double p,
			double q,
			double r,
			double s,
			double t,
			double u)
{
    double sol = 0;

    sol += p * exp(x * (-1));
    sol += q * sin(x); 
    sol += r * cos(x);
    sol += s * tan(x);
    sol += t * x * x;
    sol += u;

    return sol;
    //p * exp(x * (-1)) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

bool check_same_sign(double low,
                     double up,
                     double p,
                     double q,
                     double r,
                     double s,
                     double t,
                     double u)
{
    return compute_equation(low, p, q, r, s, t, u)*
	    compute_equation(up, p, q, r, s, t, u) > 0;
}

double binary_search(double p, double q, double r, double s, double t, double u)
{
    double lower_bound = 0.0, upper_bound = 1.0, mid;
    bool lower_changed = true, upper_changed = true;

    double temp, temp_l, temp_u;

    do
    {
    	mid = (lower_bound + upper_bound)/2;
    	temp = compute_equation(mid, p, q, r, s, t, u);

    	//sleep(1);
    	//std::cout << "line" << counter << " x:" << mid << " f(x): " << temp << "\n";

    	if (lower_changed)
    	    temp_l = compute_equation(lower_bound, p, q, r, s, t, u);

    	if (upper_changed)
    	    temp_u = compute_equation(upper_bound, p, q, r, s, t, u);

        //if (counter == 51)
            //printf(">>>%f %f %f\n", temp_l, temp, temp_u);

    	upper_changed = lower_changed = false;
    	if ((temp * temp_l) < EPSILON)
    	{
            //printf("changin upper\n");
    	    upper_bound = mid;
    	    upper_changed = true;
    	    continue;
    	}
    	if ((temp * temp_u) < EPSILON)
    	{
            //printf("changin lower\n");
    	    lower_bound = mid;
    	    lower_changed = true;
    	    continue;
    	}
    }
    while(std::abs(temp) > ERROR);

    return mid;
}

int main()
{
    double p, q, r, s, t, u;

    

    while(true)
    {
        //counter++;
        //printf("line: %d\n", counter);

	if(std::cin >> p >> q >> r >> s >> t >> u)
	{
	    if (!check_same_sign(0, 1, p, q, r, s, t, u))
		fprintf(stdout, "%.4f", binary_search(p, q, r, s, t, u));
	    else
		printf("No solution");
	}
	else break;

	printf("\n");
    }
}
