#ifndef __GLOSSY_SPECULAR__
#define __GLOSSY_SPECULAR__

#include "BRDF.h"

class GlossySpecular:public BRDF
{
public:
	GlossySpecular();

	~GlossySpecular();

	void set_ks(const float _ks);

	void set_cs(const float r, const float g, const float b);

	void set_cs(const RGBColor&	c);

	void set_exp(const float& e);

	void set_samples(const int num_samples, const float exp);

	virtual RGBColor f(const ShadeRec& sr,const Vector3D& wo,const Vector3D& wi)const; 

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo,Vector3D& wi)const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const;

private:

	float		ks;
	RGBColor 	cs;			// specular color
	float		exp;

};

#endif
