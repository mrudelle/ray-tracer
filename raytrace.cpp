#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <math.h>
using namespace std;

#include "include/scene.h"
#include "include/sphere.h"
#include "include/triangle.h"
#include "include/plane.h"
#include "include/directional_light.h"
#include "include/camera.h"
#include "include/transformation.h"
#include "include/transformation_stack.h"
#include "include/quadratic.h"
#include "include/cube.h"
#include "include/pointLight.h"
#include "include/material.h"
#include "include/frame_buffer.h"



#define XSIZE 400
#define YSIZE 300

#define ANTI_ALIASING 1

#define DOF_SAMPLES 1
#define DOF_LENS_DIAMETER 0.030
#define DOF_FOCAL_DISTANCE 2

#define VIEW_PLANE_DISTANCE 0.5

#define PI 3.14159265359

#define CITY_SIZE_X 5
#define CITY_SIZE_Y 10

float frand()
{
	int x;
	float f;

	x = rand();
	f = (float)(x & 0xffff);
	f = f/65536.0;

	return f;
}

void printTransform(string name, Transformation tt) 
{
	fprintf(stderr, "Transform %s:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", 
		name.c_str(), tt.A, tt.B, tt.C, tt.D, tt.E, tt.F, tt.G, tt.H, tt.I, tt.J, tt.K, tt.L);
}
     
void makeTriangle(Vertex a, Vertex b, Vertex c, Material *m, Scene *scene, TransformationStack *ts) {
	Triangle *t;

	t = new Triangle(a, b, c);

	t->setMaterial(m);
        Transformation *tr = new Transformation();
        (*tr) = ts->CombineStack();
	t->setTransformation(tr);
	
	scene->addObject(*t);
}

// The main raytacing entry point.

int main(int argc, const char *argv[])
{
	Scene *scene;
	Vector v;
	int x,y,ai;
	int n;
	DirectionalLight *dl;
	Colour cl;
	Vertex pp;
	double ca, cr, cg,cb;
	Transformation transfo;
	TransformationStack* ts = new TransformationStack();

	srand(4250085);

	// create the frame buffer holding the image
	FrameBuffer frameBuffer(XSIZE, YSIZE);
	frameBuffer.clear();

  // SETUP SCENES
	
	// ========== SETUP SCENE -> FISHBOWL ==========
	Scene *fishbowl = new Scene();
	Vector lightdir;
	lightdir.set(1,-1,1);
	Colour lightcolour;
	lightcolour.set(1,1,1,1);
	DirectionalLight *fbdl = new DirectionalLight(lightdir, lightcolour);
	fishbowl->addLight(*fbdl);
	Vertex origin1, origin2;
	Material glass, vacuum, red;
	glass.setPhong(1,1,1, 0.02, 0.1, 0.5, 0.2, 0.9, 1.56, 400);
	vacuum.setPhong(1,1,1, 0.02, 0.1, 0.5, 0.2, 0.9, 1, 400);
	red.setPhong(1,0,0, 0.1, 0.9, 0.0, 0.0, 0.0, 1, 400);
	origin1.set(0,0,0,1);
	Sphere *sext = new Sphere(origin1, 1.0);
	sext->setMaterial(&glass);
	Sphere *sint = new Sphere(origin1, 0.9);
	sint->setMaterial(&vacuum);
	Cube *inside = new Cube(-0.2,-0.2,3.8,0.4,0.4,0.4);
	inside->setMaterial(&red);
	fishbowl->addObject(*inside);
	fishbowl->addObject(*sext);
	// ========== END SCENE -> FISHBOWL ==========



	// ========== SETUP SCENE -> CITY ==========
	Scene *city = new Scene();
	Vector city_ld, city_pl_d;
	Vertex city_pl_p;
	city_ld.set(1,-1,1.5);
	city_ld.normalise();
	Colour city_lc;
	city_lc.set(1,1,1,1);
	DirectionalLight *city_dl = new DirectionalLight(city_ld, city_lc);
	city->addLight(*city_dl);
	city_pl_p.set(1.5,0.7,2,1);
	city_pl_d.set(-0.5, -0.5, -1);
	city_pl_d.normalise();
	PointLight *city_pl = new PointLight(city_pl_p, city_pl_d, city_lc, 4, 4);
	city->addLight(*city_pl);
	Cube citycube[CITY_SIZE_X][CITY_SIZE_Y];
	for (int i = 0; i < CITY_SIZE_X; i++) {
	    for (int j = 0; j < CITY_SIZE_Y; j++) {
		citycube[i][j].set(-(CITY_SIZE_X*0.3/2) + i*0.3 , -0.5, -(CITY_SIZE_Y*0.3/2) + j*0.3, 0.2, frand(), 0.2);
		Material *m = new Material();
		m->setPhong(frand(), frand(), frand(), 0.1, 0.9, 0.2, 0.0, 0.0, 0.0, 200.0);
		citycube[i][j].setMaterial(m);
		city->addObject(citycube[i][j]);
	    }
	}
	Plane *city_floor;
	Material *city_floor_mat;
	Vector city_floor_p;
	city_floor_p.set(0,1,0);
	city_floor = new Plane(city_floor_p, 0.5001);
	city_floor_mat = new Material();
        city_floor_mat->setPhong(0.35588, 0.85098, 0.423529, 0.1, 0.9, 0.1, 0, 0.0, 1.5, 10);
	city_floor->setMaterial(city_floor_mat);
	city->addObject(*city_floor);
	// ========== END SCENE -> CITY ==========



	// ========== SETUP SCENE -> FRACTAL ==========
	Scene *fractal = new Scene();
	Vector fractal_ld;
	fractal_ld.set(1,-1,1);
	Vertex fractal_lpos;
	fractal_lpos.set(-1,1,-1,1);
	Colour fractal_lc;
	fractal_lc.set(1,1,1,1);
	PointLight *fractal_dl = new PointLight( fractal_lpos, fractal_ld, fractal_lc, 4, 1);
	fractal->addLight(*fractal_dl);
	Material *fractal_mat = new Material();
	fractal_mat->setPhong(1,1,1, 0.01, 0.05, 0.9, 0.95, 0.0, 1.5, 800);
	Sphere fractal_s1, fractal_s2, fractal_s3, fractal_s4;
	Vertex fractal_v1, fractal_v2, fractal_v3, fractal_v4;
	fractal_v1.set(-1, 0, 0, 1);
	fractal_v2.set(0.5, 0.866025, 0, 1);
	fractal_v3.set(0.5, -0.866025,0, 1);
	fractal_v4.set(0, 0, 0, 1);
	fractal_s1.set(fractal_v1, 0.866025);
	fractal_s2.set(fractal_v2, 0.866025);
	fractal_s3.set(fractal_v3, 0.866025);
	fractal_s4.set(fractal_v4, 1-0.866025);
	fractal->addObject(fractal_s1);
	fractal->addObject(fractal_s2);
	fractal->addObject(fractal_s3);
	fractal->addObject(fractal_s4);
	fractal_s1.setMaterial(fractal_mat);
	fractal_s2.setMaterial(fractal_mat);
	fractal_s3.setMaterial(fractal_mat);
	fractal_s4.setMaterial(fractal_mat);
	Plane *fractal_floor, *fractal_ceil;
	Material *fractal_floor_mat, *fractal_ceil_mat;
	Vector fractal_floor_p;
	fractal_floor_p.set(0,0,-1);
	fractal_floor = new Plane(fractal_floor_p, 0.5001);
	fractal_floor_mat = new Material();
        fractal_floor_mat->setPhong(0.278, 0.447, 0.917, 0.1, 0.90, 0.1, 0, 0.0, 1.5, 10);
	fractal_floor->setMaterial(fractal_floor_mat);
	fractal->addObject(*fractal_floor);
	// ========== END SCENE -> FRACTAL ==========
	


	// ========== SETUP SCENE -> HOURGLASS ==========
	Scene *hourglass = new Scene();
	Vector hourglass_ld;
	hourglass_ld.set(1.2,-1,1.2);
	Colour hourglass_lc;
	hourglass_lc.set(1,1,1,1);
	DirectionalLight *hourglass_dl = new DirectionalLight(hourglass_ld, hourglass_lc);
	hourglass->addLight(*hourglass_dl);
	
	Quadratic hourglass_sandext, hourglass_sandint, hourglass_glass;
	hourglass_sandext.set(1,-1,1,0,0,0,0,0,0,0.40);
	Material hourglass_sand_mat;
	hourglass_sand_mat.setPhong(239.0/255.0, 210.0/255.0, 121.0/255.0, 0.2, 0.8, 0.1, 0.0, 0.0, 1.5, 20);
	hourglass_sandext.setMaterial(&hourglass_sand_mat);
	hourglass->addObject(hourglass_sandext);
	
	hourglass_sandint.set(1,1,1,0,0,0,0,0,0,-0.25);
	hourglass_sandint.setMaterial(&hourglass_sand_mat);
	hourglass->addObject(hourglass_sandint);
	
	TransformationStack hourglass_ts;
	Transformation hourglass_trans;
	hourglass_trans.translation(0,0,-3);
	hourglass_ts.Push(&hourglass_trans);
	hourglass_glass.set(1,1,1,0,0,0,0,0,0,-0.4);
	Material hourglass_glass_mat;
	hourglass_glass_mat.setPhong(1, 1, 1, 0.05, 0.1, 0.8, 0.4, 0.9, 1.5, 800);
	hourglass_glass.setMaterial(&hourglass_glass_mat);
	Transformation final_transfo = hourglass_ts.CombineStack();
	hourglass_glass.setTransformation(&final_transfo);
	hourglass->addObject(hourglass_glass);
	
	Vector hourglass_floor_p;
	hourglass_floor_p.set(0,1,0);
	Plane *hourglass_floor = new Plane(hourglass_floor_p, 0.3);
	Material *hourglass_floor_mat = new Material();
        hourglass_floor_mat->setPhong(0.278, 0.447, 0.917, 0.1, 0.90, 0.1, 0, 0.0, 1.5, 10);
	hourglass_floor->setMaterial(hourglass_floor_mat);
	hourglass->addObject(*hourglass_floor);
	// ========== END SCENE -> HOURGLASS ==========



	// ========== BEGIN SCENE -> FIRSTSTEPS ==========
  	// Create a new scene to render
	Scene *first_steps = new Scene();
  	// Create and add a directional light to the scene
	v.set(-1.0,-1.0,1.0);
	cl.set(1.0,1.0,1.0,1.0);
	pp.set(-50.0, 50.0, -48.25, 1.0);
	dl = new DirectionalLight(v, cl);
	first_steps->addLight(*dl);
	// Create and add a point light to the scene
	Vertex lpos;
	lpos.set(-0.5, 1, 0.75, 1);
	Vector ldir;
	ldir.set(0.5, -1, 0.25);
	Colour lcol;
	lcol.set(1,1,1,1);
	PointLight *pl = new PointLight(lpos, ldir, lcol, 3, 1);
	first_steps->addLight(*pl);
	// Create a transformation stack
	Transformation move0, move1,move2,scale,rotation;
	move1.translation(0, 0, -1.5);
	ts->Push(&move1);
	scale.scale(0.8,0.8,0.5);
	ts->Push(&scale);
	rotation.rotationz(PI/4);
	ts->Push(&rotation);
	move2.translation(0, 0, 1.5);
	ts->Push(&move2);
	// Add 10 random spheres to the scene
	for (n = 0; n < 10; n += 1)
	{
		Sphere *s;
		Material *m;
		Vertex p;
    	// position
		p.set(frand()-0.5,frand()-0.5,frand()+1.0,1.0);
    	// create with random radius
		s = new Sphere(p, frand()/2.0);
    	// create new material with shared random Ka and Kd
		m = new Material();
		cr = frand(); cg = frand(); cb = frand(); ca = frand();
        m->setPhong(cr, cg, cb, 0.1, 0.5, 0.5, 0.0, 0.0, 1.5, 30.0);
        // set spheres material
		s->setMaterial(m);
		// apply the transformation stack
		transfo = ts->CombineStack();
		s->setTransformation(&transfo);
		first_steps->addObject(*s);
	}
	// remove transformations from the stack
	ts->Pop();
	ts->Pop();
	ts->Pop();
	ts->Pop();
	// Add 10 random triangle to the first_steps
	for (n = 0; n < 20; n += 1)
	{
		Triangle *t;
		Material *m;
		Vertex p1, p2, p3;
    	// position
		p1.set(frand()-0.5,frand()-0.5,frand()+1.0,1.0);
		p2.set(frand()-0.5,frand()-0.5,frand()+1.0,1.0);
		p3.set(frand()-0.5,frand()-0.5,frand()+1.0,1.0);
    	// create new material with shared random Ka and Kd
		m = new Material();
		cr = frand(); cg = frand(); cb = frand(); ca = frand();
        m->setPhong(cr, cg, cb, 0.1, 0.5, 0.5, 0.0, 0.0, 1.5, 100.0);
        // create the triangles
		makeTriangle(p1, p2, p3, m, first_steps, ts);
	}
	// ADD a Plane as floor
	Plane *floor;
	Material *mfloor;
	Vertex p1;
	Vector v1;
	v1.set(0,1,0);
	floor = new Plane(v1, 0.5);
	// create new material with shared random Ka and Kd
	mfloor = new Material();
	cr = frand(); cg = frand(); cb = frand(); ca = frand();
	mfloor->setPhong(cr, cg, cb, 0.1, 0.5, 0.1, 0.5, 0.0, 1.5, 10);
	floor->setMaterial(mfloor);
	transfo = ts->CombineStack();
	floor->setTransformation(&transfo);
	first_steps->addObject(*floor);
	//Create a transparent cube
	Cube *cube = new Cube(-1, -0.5, 0.5, 2, 1, 0.2);
	Material *m = new Material();
	cr = frand(); cg = frand(); cb = frand(); ca = frand();
	m->setPhong(1, 1, 1, 0.05, 0.0, 0.3, 0.1, 0.9, 1.5, 200.0);
	cube->setMaterial(m);
	//first_steps->addObject(*cube);
	Transformation *teli = new Transformation();
	teli->translation(0.5, 0.0, -1);
	ts->Push(teli);
	//Create a quadratic elipse
	Quadratic elipse;
	elipse.set(1,1,1,0,0,0,0,0,0,-0.25);
	Material melipse;
	melipse.setPhong(0, 1.0, 0.0, 0.1, 0.1, 0.1, 0.1, 0.9, 1.5, 100);
	elipse.setMaterial(&melipse);
	Transformation tfeli = ts->CombineStack();
	elipse.setTransformation(&tfeli);
	//first_steps->addObject(elipse);
	//create a sphere
	Vertex sv;
	sv.set(0.5,0,-0.5,1);
	Sphere *boule = new Sphere(sv, 0.5);
	boule->setMaterial(&melipse);
	first_steps->addObject(*boule);  
	// ========== END SCENE -> FIRSTSTEPS ==========   



	// ========== SCENE CHOICE ==========
	scene = first_steps;
	


	// ========== SETUP CAMERA ==========
	Camera view;
	Vector up;
	
	fprintf(stderr, "argc %d : ", argc);
	for (int i = 0; i<argc; i++) {
		fprintf(stderr, "arg %d=%s, ", i, argv[i]);
	}
	
	if (argc == 9){
		Vertex dest;
		dest.set((float)atof(argv[1]),(float)atof(argv[2]),(float)atof(argv[3]),1.0);
		float dist = (float)atof(argv[4]);
		float ang = (float)(atof(argv[5])*3.1415/180);
		Vertex eye;
		eye.set((float)(atof(argv[1])+sin(ang)*dist),(float)atof(argv[2]),(float)(atof(argv[3])-cos(ang)*dist),1.0);
		Vector look = Vector(eye, dest);
		look.normalise();
		up.set((float)atof(argv[6]),(float)atof(argv[7]),(float)atof(argv[8]));
		up.normalise();
		view = Camera(VIEW_PLANE_DISTANCE, eye, up, look);
		fprintf(stderr, "eye: {%f,%f,%f} - look: {%f,%f,%f}\n", view.eye.x, view.eye.y, view.eye.z, view.look.x, view.look.y, view.look.z);
		fprintf(stderr, "u: {%f,%f,%f} - v: {%f,%f,%f} - w: {%f,%f,%f}\n", view.u.x, view.u.y, view.u.z, view.v.x, view.v.y, view.v.z, view.w.x, view.w.y, view.w.z);
	} else {
		Vertex eye;
		eye.set(0.0,0.0,0.0,1.0);
		Vector look;
		look.set(0.0,0.0,1.0);
		up.set(0.0,1.0,0.0);
		up.normalise();
		view = Camera(VIEW_PLANE_DISTANCE, eye, up, look);
	}
	


  	// ========== RAYTRACE SCENE ==========
	
	fprintf(stderr, "|-----------loading------------|\n|");

	// p is the intersection of the primaryRay on the focal distance
	Vertex dof_p;
	Ray primaryRay, dof_ray;
	float dist_to_focal, sample_d, sample_alpha;
	Colour cumulativeColour;
	
	for(y=0;y<YSIZE;y+=1)
	{
	    for(x=0;x<XSIZE;x+=1)
		{
			cumulativeColour.clear();

			float yoffset = ((float)YSIZE/2)/(float)XSIZE;
			for (ai=0;ai<ANTI_ALIASING;ai+=1){
			    
				//Compute antialiasing sample
			    
				if (ANTI_ALIASING == 1)
					primaryRay = view.getPerspectiveRay((((float)x)/XSIZE)-0.5, (((float)y)/XSIZE)-yoffset);
					//the last term allows to center non 1-ratio images
				else
					primaryRay = view.getPerspectiveRay((((float)x+frand()-0.5)/XSIZE)-0.5, (((float)y+frand())/XSIZE)-yoffset);
				
				for (int dofi = 0; dofi < DOF_SAMPLES; dofi++) {
				    
				    //Compute depth of field sample
				    
				    dist_to_focal = (float)DOF_FOCAL_DISTANCE/(float)VIEW_PLANE_DISTANCE;
				    dof_p.set(
						primaryRay.P.x + primaryRay.D.x * dist_to_focal,
						primaryRay.P.y + primaryRay.D.y * dist_to_focal,
						primaryRay.P.z + primaryRay.D.z * dist_to_focal,
						1);
				    if (DOF_SAMPLES != 1)
				    {
					sample_alpha = frand()*3.14159265*2.0;
					sample_d = frand();
					dof_ray.P.set(
						primaryRay.P.x + sample_d * (float)DOF_LENS_DIAMETER * (cos(sample_alpha)*view.v.x + sin(sample_alpha)*view.u.x),
						primaryRay.P.y + sample_d * (float)DOF_LENS_DIAMETER * (cos(sample_alpha)*view.v.y + sin(sample_alpha)*view.u.y),
						primaryRay.P.z + sample_d * (float)DOF_LENS_DIAMETER * (cos(sample_alpha)*view.v.z + sin(sample_alpha)*view.u.z),
						1);
					dof_ray.D.set(
						dof_p.x - dof_ray.P.x,
						dof_p.y - dof_ray.P.y,
						dof_p.z - dof_ray.P.z
						);
				    }
				    else
				    {
					dof_ray.P.set(
						primaryRay.P.x,
						primaryRay.P.y,
						primaryRay.P.z,
						primaryRay.P.w
					    );
					dof_ray.D.set(
					    primaryRay.D.x,
						primaryRay.D.y,
						primaryRay.D.z
					    );
				    }
				    dof_ray.D.normalise();
					
				    // Trace primary ray
				    Colour col = scene->raytrace(dof_ray, 6, (TransparentIntersection*)0);

				     // Save result in frame buffer
				    cumulativeColour.red += col.red/(ANTI_ALIASING*DOF_SAMPLES);
				    cumulativeColour.green += col.green/(ANTI_ALIASING*DOF_SAMPLES);
				    cumulativeColour.blue += col.blue/(ANTI_ALIASING*DOF_SAMPLES);
				    cumulativeColour.alpha += col.alpha/(ANTI_ALIASING*DOF_SAMPLES);
				    
				} 
			}

			frameBuffer.setValue(x, y, cumulativeColour);
		}
	    if (y%(YSIZE/30) < 1){
		fprintf(stderr, "=");
	    }
	    
	}

	fprintf(stderr, "|\n");

  	// OUTPUT IMAGE	
    frameBuffer.writePAM();
}
