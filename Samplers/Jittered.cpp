#include "Jittered.h"
#include "Maths.h"
#include <cmath>

Jittered::Jittered()
:Sampler()
{
	generate_samples();
}

Jittered::Jittered(const int num)
:Sampler(num)
{
	generate_samples();
}

Jittered::Jittered(const int num,const int nsets)
:Sampler(num,nsets)
{
	generate_samples();
}


Jittered::~Jittered()
{}

void Jittered::generate_samples()
{
	int n = (int)sqrt((float)num_samples);

	for(int p = 0; p < num_sets;p++)
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
			{
				Point2D sp(( j + rand_float()) / n, ( i + rand_float()) / n );
				samples.push_back(sp);
			}
}