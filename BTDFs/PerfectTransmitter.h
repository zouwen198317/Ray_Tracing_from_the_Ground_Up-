#ifndef __PERFECT_TRANSMITTER__
#define __PERFECT_TRANSMITTER__

#include "BTDF.h"

class PerfectTransmitter:public BTDF
{
public:
	PerfectTransmitter();
	~PerfectTransmitter();

	virtual RGBColor f(const ShadeRec& sr,const Vector3D& wt,const Vector3D& wo)const;

	virtual RGBColor sample_f(const ShadeRec& sr,const Vector3D& wo,Vector3D& wt)const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt, float& pdf) const; 

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const ;

	virtual bool tir(const ShadeRec& sr)const;

	void set_kt(const float t);

	void set_ior(const float i);

protected:

	float	kt;
	float	ior;
};

inline void PerfectTransmitter::set_kt(const float t)
{
	kt = t;
}

inline void PerfectTransmitter::set_ior(const float i)
{
	ior = i;
}

#endif