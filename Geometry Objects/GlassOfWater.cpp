#include "Disk.h"
#include "ConvexCylinder.h"
#include "ConcaveCylinder.h"
#include "Annulus.h"
#include "GlassOfWater.h"


GlassOfWater::GlassOfWater (void)
			: 	Compound(),
				height(2.0),
				inner_radius(0.9),
				wall_thickness(0.1),  
				base_thickness(0.3),
				water_height(1.5)
{	
	build_components();							
}


GlassOfWater::GlassOfWater (	const double _height, 
								const double _inner_radius,
								const double _wall_thickness,
								const double _base_thickness,
								const double _water_height)
			: 	Compound(),
				height(_height),
				inner_radius(_inner_radius),
				wall_thickness(_wall_thickness),
				base_thickness(_base_thickness),
				water_height(_water_height)

{	
	build_components();							
}


GlassOfWater::GlassOfWater (const GlassOfWater& gw)  			
			: 	Compound(gw),
				height(gw.height),
				inner_radius(gw.inner_radius),
				wall_thickness(gw.wall_thickness),
				base_thickness(gw.base_thickness),
				water_height(gw.water_height)
{}


GlassOfWater* GlassOfWater::clone(void) const 
{
	return(new GlassOfWater(*this));
}


GlassOfWater& GlassOfWater::operator= (const GlassOfWater& rhs) 
{
	if (this == &rhs)
		return (*this);

	Compound::operator=(rhs); 
	
	height 			= rhs.height;
	inner_radius 	= rhs.inner_radius;
	wall_thickness 	= rhs.wall_thickness;
	base_thickness 	= rhs.base_thickness;
	water_height 	= rhs.water_height;


	return (*this) ;
}


GlassOfWater::~GlassOfWater(void) {}


// Using named components would be better
// It would make the material functions below a lot clearer and maintainable

void GlassOfWater::build_components(void) 
{
	// build the glass parts
	
	objects.push_back(new Annulus(	Point3D(0, height, 0), 						// rim at top
									Normal(0, 1, 0), 
									inner_radius, 
									inner_radius + wall_thickness));
									   	
	objects.push_back(new Disk(	Point3D(), 									// bottom of glass
								Normal(0, -1, 0), 
								inner_radius + wall_thickness));  
													
	objects.push_back(new ConcaveCylinder(	water_height, // inner curved surface of glass
												height, 
												inner_radius )); 
																	 
	objects.push_back(new ConvexCylinder(	0, 								// outer curved surface of glass
											height, 
											inner_radius + wall_thickness));
	
	
	// build the water parts
	
	objects.push_back(new Disk(	Point3D(0, water_height, 0), 					// top of water
								Normal(0, 1, 0), 
								inner_radius));

								
	objects.push_back(new Disk(	Point3D(0, base_thickness, 0), 					// bottom of water
								Normal(0, -1, 0),  
								inner_radius));

								
	objects.push_back(new ConvexCylinder(	base_thickness,					// curved surface of water
												water_height, 
												inner_radius ));
												
	 											
}
																																																																									
void GlassOfWater::set_glass_air_material(Material* m_ptr) 
{
	for (int j = 0; j < 4; j++)
		objects[j]->set_material(m_ptr);
}

void GlassOfWater::set_water_air_material(Material* m_ptr) 
{
	objects[4]->set_material(m_ptr);	// top of water
}

void GlassOfWater::set_water_glass_material(Material* m_ptr) 
{
	for (int j = 5; j < 7; j++)
		objects[j]->set_material(m_ptr);
}


																			
															
																