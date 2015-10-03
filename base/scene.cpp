#include <math.h>

#include "include/scene.h"
#include "include/transparentIntersection.h"


// the fenomenon is explained in details in (Raytracing from the ground up p.301)
#define EPSILON_FACTOR 0.001
#define WORLD_REFRACTION_INDEX 1

Scene::Scene() {
	scache = 0;
	obj_list = (Object *) 0;
	light_list = (Light *) 0;
}

void Scene::addObject(Object &obj) {
	obj.link(obj_list);
	obj_list = &obj;
}

void Scene::addLight(Light &lt) {
	lt.link(light_list);
	light_list = &lt;
}

Colour Scene::raytrace(Ray &ray, int level, TransparentIntersection *intersec_stack) {
	float ta, t;
	Colour col;
	Object *obj;
	Object *closest;
	Light *lt;
	Hit hit;
	Vertex position;
	Vector normal;


	if (level == 0) {
		col.clear();
		return col; // stop if recursed deep enough
	}

    // TEST EACH OBJECT AGAINST RAY, FIND THE CLOSEST

    t = 1000000000.0; // a long way aways
    closest = (Object *) 0;
    obj = obj_list;

    while (obj != (Object *) 0) {
    	if (obj->transformedintersect(ray, &hit, t) == true) {
    		if (hit.t < t) {
    			closest = hit.obj;
    			t = hit.t;
    			normal = hit.n;
				// just in case
    			normal.normalise();
    			position = hit.p;
    		}
    	}
    	obj = obj->next();
    }

    // Recreate the colour
    
    col.clear();

    if (closest != (Object *) 0) {
    	lt = light_list;

    	Colour ocol;

    	Colour ka = closest->obj_mat->ka;
    	Colour kd = closest->obj_mat->kd;
    	Colour ks = closest->obj_mat->ks;
    	Colour kr = closest->obj_mat->kr;
    	Colour kt = closest->obj_mat->kt;
    	double phong = closest->obj_mat->n;
    	double refIndex = closest->obj_mat->refractionIndex;
    	Ray tolight;

    	col.red += ka.red;
    	col.green += ka.green;
    	col.blue += ka.blue;

    	while (lt != (Light *) 0) {
    		Vector ldir;
    		Vector xldir;
    		Vector reflectDir;
    		Colour lcol;

    		lt->getLightProperties(position, &xldir, &lcol);
    		xldir.normalise();

		    // shadow test

    		float ldist = lt->distanceToSource(position);
    		tolight.D.set(
    			xldir.x,
    			xldir.y,
    			xldir.z
    			);
    		tolight.D.normalise();
    		tolight.P.set(
    			position.x + normal.x * EPSILON_FACTOR,
    			position.y + normal.y * EPSILON_FACTOR,
    			position.z + normal.z * EPSILON_FACTOR,
    			position.w
    			);

    		if (this->shadowtrace(tolight, ldist)) {
				lt = lt->next(); // next light
				continue; //the effect of this light is discarded
			}

		    // calculation of diffuse component

			float dlc = xldir.dot(normal);


		    // calculation of  specular component

			reflectDir.set(
				-xldir.x + 2 * (dlc) * normal.x,
				-xldir.y + 2 * (dlc) * normal.y,
				-xldir.z + 2 * (dlc) * normal.z
				);
			reflectDir.normalise();
		    float slc = -reflectDir.dot(ray.D);// there is a minus because the ray direction is inverted
		    if (slc < 0.0) {
		    	slc = 0.0;
		    }
		    slc = pow(slc, phong);
		    
		    
		    if (dlc < 0.0) {
		    	dlc = 0.0;
		    }

		    // combine components

		    col.red += lcol.red * (dlc * kd.red + slc * ks.red);
		    col.green += lcol.green * (dlc * kd.green + slc * ks.green);
		    col.blue += lcol.blue * (dlc * kd.blue + slc * ks.blue);

		    lt = lt->next(); // next light
		}

		// add reflected rays here

		if (kr.red != 0.0 || kr.green != 0.0 || kr.blue != 0.0) {
		    //we copy the intersection stack
			TransparentIntersection *intersec_stack_copy = intersec_stack->copy();

			float thetaR = -(normal.dot(ray.D));
			Ray reflected;
			reflected.D.set(
				ray.D.x + 2 * thetaR * normal.x,
				ray.D.y + 2 * thetaR * normal.y,
				ray.D.z + 2 * thetaR * normal.z
				);
			reflected.D.normalise();
			reflected.P.set(
				position.x + normal.x * EPSILON_FACTOR,
				position.y + normal.y * EPSILON_FACTOR,
				position.z + normal.z * EPSILON_FACTOR,
				position.w
				);
			Colour rlc = this->raytrace(reflected, level - 1, intersec_stack_copy);

			col.red += rlc.red * kr.red;
			col.green += rlc.green * kr.green;
			col.blue += rlc.blue * kr.green;
		}

		// add refracted rays here

		if (kt.red != 0.0 || kt.green != 0.0 || kt.blue != 0.0) {

		    // RULES I SET ABOUT TRANSPARENT ELEMENTS
		    //  - The current refraction index correspond to refraction index
		    //  of the last object we entered
		    //  - When we exit an object the refraction index become the refraction
		    //  index of the last object we entered and that we did not exit yet
		    //  - The amount of light of each colour component that passes through
		    //  the object depends of kt.[red/green/blue] and is independant of the
		    //  distance traveled in the transparent object.

			double prev_index = WORLD_REFRACTION_INDEX,
			next_index = WORLD_REFRACTION_INDEX;
			if (intersec_stack != (TransparentIntersection*) 0) {
				prev_index = intersec_stack->prev_index;
			}

			TransparentIntersection *prevIntersec = intersec_stack;
			TransparentIntersection *prevPrevIntersec = (TransparentIntersection *) 0;
			bool exit = false;
			while (prevIntersec != (TransparentIntersection*) 0) {
			//if we are going out of the object
				if (prevIntersec->curr_object == closest) {
					exit = true;
					if (prevPrevIntersec == (TransparentIntersection*) 0)
				//if element to delete is head of stack
					{
						TransparentIntersection *tempIntersec = intersec_stack;
						intersec_stack = intersec_stack->next();
						prevIntersec = intersec_stack;
						delete tempIntersec;
					}
					else
					{
						prevPrevIntersec->link(prevIntersec->next());
						delete prevIntersec;
						prevIntersec = prevPrevIntersec->next();
					}
			} else { //If we are going in the object
				prevPrevIntersec = prevIntersec;
				prevIntersec = prevIntersec->next();
			}
		}

		if (!exit) {
			TransparentIntersection *current_intersec = new TransparentIntersection();
			current_intersec->set(refIndex, closest);
			current_intersec->link(intersec_stack);
			intersec_stack = current_intersec;
		}

		if (intersec_stack != (TransparentIntersection*) 0) {
			next_index = intersec_stack->prev_index;
		}


		    // the formula can be found on page 565 of (ray tracing from the ground up)
		double 	eta = next_index / prev_index,
		cosi = -ray.D.dot(normal),
		sin2 = 1/(eta*eta) * (1- (cosi*cosi)),
		part2 = (1/eta) * cosi - sqrt(1-sin2),
		temp = 1 - (1 / (eta * eta) * (1 - cosi*cosi));
		Ray transmitted;
		transmitted.D.set(
			ray.D.x/eta + part2*normal.x,
			ray.D.y/eta + part2*normal.y,
			ray.D.z/eta + part2*normal.z
			);
		transmitted.D.normalise();
		transmitted.P.set(
			position.x - normal.x * EPSILON_FACTOR,
			position.y - normal.y * EPSILON_FACTOR,
			position.z - normal.z * EPSILON_FACTOR,
			position.w
			);

		Colour tlc;
		if (temp < 0){
			tlc.set(0,0,0,1);
		} else {
			tlc = this->raytrace(transmitted, level - 1, intersec_stack);
		}
		col.red += tlc.red * kt.red;
		col.green += tlc.green * kt.green;
		col.blue += tlc.blue * kt.green;
	}
}

return col;
}

bool Scene::shadowtrace(Ray &ray, double tlimit) {
	Object *obj;
	Hit hit;

    // check for shadow intersections

	obj = obj_list;

	while (obj != (Object *) 0) {
		if (obj->transformedintersect(ray, &hit, tlimit) == true) {
			if (hit.t < tlimit) {
				return true;
			}
		}
		obj = obj->next();
	}

	return false;
}
