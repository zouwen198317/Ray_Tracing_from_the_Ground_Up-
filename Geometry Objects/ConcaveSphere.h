#ifndef __CONCAVE_SPHERE__
#define __CONCAVE_SPHERE__

#include "Sphere.h"

class ConcaveSphere:public Sphere
{
public:

	ConcaveSphere();

	ConcaveSphere(const Point3D& p,const double r);

	~ConcaveSphere();

	virtual	bool hit(const Ray& ray,double& tmin,ShadeRec &sr)const;
};

#endif