#include "FishEye.h"
#include "Maths.h"
#include "World.h"
#include "Sampler.h"

FishEye::FishEye()
:Camera()
{}

FishEye::~FishEye()
{}


Vector3D FishEye::ray_direction(const Point2D &pp, const int hres, const int vres, const float s, float &r_squared) const
{
	Point2D pn(2.0 / (s * hres) * pp.x , 2.0 / (s * vres) * pp.y);
	r_squared = pn.x * pn.x + pn.y * pn.y;

	if(r_squared <= 1.0)
	{
		float r = sqrt(r_squared);
		float psi = r * psi_max * PI_ON_180;
		float sin_psi = sin(psi);
		float cos_psi = cos(psi);
		float sin_alpha = pn.y / r;
		float cos_alpha = pn.x / r;
		Vector3D dir = sin_psi * cos_alpha * u + sin_psi * sin_alpha * v - cos_psi * w;

		return dir;
	}
	else
		return Vector3D();
}

void FishEye::set_fov(float fov)
{
	psi_max = fov / 2.0;
}

void FishEye::render_scene(const World &world)
{
	RGBColor	L;
	ViewPlane	vp(world.vp);					
	int 		hres		= vp.hres;
	int 		vres 		= vp.vres;
	float		s 			= vp.s;
	Ray			ray;
	Point2D 	sp; 					// sample point in [0, 1] X [0, 1]
	Point2D 	pp;						// sample point on the pixel
	float		r_squared;				// sum of squares of normallised device coordinates
	ray.o = eye;

	world.open_window(vp.hres,vp.vres);
		
	for (int r = 0; r < vres; r++)		// up
		for (int c = 0; c < hres; c++) {	// across 					
			L = black; 
						
			for (int j = 0; j < vp.num_samples; j++) {	
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = s * (c - 0.5 * hres + sp.x);
				pp.y = s * (r - 0.5 * vres + sp.y);
				ray.d = ray_direction(pp, hres, vres, s, r_squared);
				
				if (r_squared <= 1.0)
					L += world.tracer_ptr->trace_ray(ray, 0);
			}
										
			L /= vp.num_samples;	
			//L *= exposure_time;	
			world.display_pixel(r, c, L);
		}
}