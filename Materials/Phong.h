#ifndef __PHONG__
#define __PHONG__

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"


class Phong:public Material
{
public:

	Phong(void);

	virtual ~Phong(void);


	void set_ka(const float ka);

	void set_kd(const float kd);
	
	void set_ks(const float ks);

	void set_cd(float r,float g,float b);

	void set_cd(float a);

	void set_cd(const RGBColor& c);

	void set_cs(float r,float g,float b);

	void set_cs(const RGBColor& c);

	void set_exp(const float e);

	virtual RGBColor shade(ShadeRec& sr)const;

	virtual RGBColor area_light_shade(ShadeRec& sr)const;

protected:

	Lambertian*		ambient_brdf;
	Lambertian*		diffuse_brdf;
	GlossySpecular*	specular_brdf;

};

#endif