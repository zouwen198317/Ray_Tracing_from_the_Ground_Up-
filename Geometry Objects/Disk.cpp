#include "Disk.h"

const double Disk::kEpsilon = 0.001;

Disk::Disk()
:GeometryObject(),center(),radius(1.),normal(0,1,0)
{}

Disk::Disk(const Point3D &c, const Normal &n, const double r)
:GeometryObject(),center(c),radius(r),normal(n)
{}

Disk::Disk(Point3D c, float r, Normal n)
:       GeometryObject(),
center(c),
radius(r),
normal(n)
{}


Disk::~Disk()
{}

bool Disk::hit(const Ray& ray, double& tmin, ShadeRec& sr)const
{
	float t = (center - ray.o ) * normal / (ray.d * normal);

	if( t <= kEpsilon)
		return false;

	Point3D p = ray.o + t * ray.d;

	if(center.distance(p) < radius )
	{
		tmin = t;
		sr.normal = normal;
		sr.local_hit_point = ray.o + t * ray.d;
		return true;
	}

	else
		return false;
}

bool Disk::shadow_hit(const Ray& ray,float& tmin)const
{
	float t = (center - ray.o ) * normal / (ray.d * normal);

	if( t <= kEpsilon)
		return false;

	Point3D p = ray.o + t * ray.d;

	if(center.distance(p) < radius )
	{
		tmin = t;
		return true;
	}

	else
		return false;
}