#include "SV_Matte.h"
#include "World.h"


SV_Matte::SV_Matte()
:Material(),ambient_brdf(new SV_Lambertian),  diffuse_brdf(new SV_Lambertian)
{
}

SV_Matte::~SV_Matte()
{
	if(ambient_brdf)
	{
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	if(diffuse_brdf)
	{
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
}


void SV_Matte::set_ka(const float ka)
{
	ambient_brdf->set_kd(ka);
}

void SV_Matte::set_kd(const float kd)
{
	diffuse_brdf->set_kd(kd);
}



void SV_Matte::set_cd(Texture* tex)
{
	ambient_brdf->set_cd(tex);
	diffuse_brdf->set_cd(tex);
}

RGBColor SV_Matte::shade(ShadeRec& sr)const
{
	Vector3D wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr,wo) * sr.w.ambient_ptr->L(sr);

	int numLights = sr.w.lights.size();

	for(int j = 0;j < numLights;j++)
	{
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		wi.normalize(); 
		float ndotwi = sr.normal * wi; 

		if(ndotwi> 0.0) 
		{
			bool in_shadow = false;
			
			if(sr.w.lights[j]->casts_shadows())
			{
				Ray shadowRay(sr.hit_point,wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadowRay,sr);
			}
			
			if(!in_shadow)
				L += diffuse_brdf->f(sr,wo,wi) * sr.w.lights[j]->L(sr) * ndotwi; 
		}
	}

	return L;
}

RGBColor SV_Matte::area_light_shade(ShadeRec& sr)const
{
	Vector3D wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr,wo) * sr.w.ambient_ptr->L(sr);

	int num_lights = sr.w.lights.size();

	for(int i = 0; i < num_lights; i++ )
	{
		Vector3D wi = sr.w.lights[i]->get_direction(sr);
		float ndotwi = sr.normal * wi;

		if( ndotwi > 0.0 )
		{
			bool in_shadow = false;

			if(sr.w.lights[i]->casts_shadows())
			{
				Ray shadow_ray(sr.hit_point,wi);
				in_shadow = sr.w.lights[i]->in_shadow(shadow_ray,sr);
			}

			if(!in_shadow)
			{
				L += diffuse_brdf->f(sr,wo,wi) * sr.w.lights[i]->L(sr) * sr.w.lights[i]->G(sr) * ndotwi / sr.w.lights[i]->pdf(sr); 
			}
		}
	}
	return L;
}

RGBColor SV_Matte::path_shade(ShadeRec& sr)const
{
	Vector3D wi;
	Vector3D wo = -sr.ray.d;
	float pdf;
	RGBColor f = diffuse_brdf->sample_f(sr,wo,wi,pdf);
	float ndotwi = sr.normal * wi;
	Ray reflected_ray(sr.hit_point,wi);

	return (f * sr.w.tracer_ptr->trace_ray(reflected_ray,sr.depth+1) * ndotwi / pdf);
}


RGBColor SV_Matte::global_shade(ShadeRec&	sr)const
{
	RGBColor L;

	if( sr.depth == 0 )
		L = area_light_shade(sr);

	Vector3D wi;
	Vector3D wo = -sr.ray.d;
	float pdf;
	RGBColor f = diffuse_brdf->sample_f(sr,wo,wi,pdf);
	float ndotwi = sr.normal * wi;
	Ray reflected_ray(sr.hit_point,wi);
	L += (f * sr.w.tracer_ptr->trace_ray(reflected_ray,sr.depth+1) * ndotwi / pdf);

	return L;
}

void SV_Matte::set_sampler(Sampler* s)
{
	diffuse_brdf->set_sampler(s);
}