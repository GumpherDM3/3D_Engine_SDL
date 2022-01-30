#include <SDL2/SDL.h>
#include "Renderer.h"
#include "Triangle.h"
#include "Mesh_Pipeline.h"
#include "Multiply_Matrix_Service.h"

Renderer::Renderer(void){
    // SDL and Screen initializing
	SCREEN_W = 640;
    SCREEN_H = 360;
	window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, screen_mode);
	renderer = SDL_CreateRenderer(window, -1, 0);
    

	// Projection Matrix
    fNear = 0.1f;
	fFar = 1000.0f;
	fFOV=90.0f;
	fAspectRatio = (float)SCREEN_H/(float)SCREEN_W;
	fFOV_rad = 1.0/(SDL_tanf((fFOV/2)*(3.14159265f/180.0f)));

	matProj.m[0][0] = fAspectRatio*fFOV_rad;
	matProj.m[1][0] = 0.0;
	matProj.m[2][0] = 0.0;
	matProj.m[3][0] = 0.0;
	matProj.m[0][1] = 0.0;
	matProj.m[1][1] = fFOV_rad;
	matProj.m[2][1] = 0.0;
	matProj.m[3][1] = 0.0;
	matProj.m[0][2] = 0.0;
	matProj.m[1][2] = 0.0;
	matProj.m[2][2] = fFar/(fFar-fNear);
	matProj.m[3][2] = (-fFar*fNear)/(fFar-fNear);
	matProj.m[0][3] = 0.0;
	matProj.m[1][3] = 0.0;
	matProj.m[2][3] = 1.0;
	matProj.m[3][3] = 0.0;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

}

void Renderer::Draw_Triangle_2d(Vec2d vert1, Vec2d vert2, Vec2d vert3, SDL_Color col)
{
	
	SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);

	vert1 = Cartesian_to_Screen(vert1);
	vert2 = Cartesian_to_Screen(vert2);
	vert3 = Cartesian_to_Screen(vert3);
	SDL_RenderDrawLineF(renderer, vert1.x, vert1.y, vert2.x, vert2.y);
	SDL_RenderDrawLineF(renderer, vert2.x, vert2.y, vert3.x, vert3.y);
	SDL_RenderDrawLineF(renderer, vert3.x, vert3.y, vert1.x, vert1.y);
}

void Renderer::Project_Triangle_3d(Triangle &tri){
	// Apply Perspective Projection Matrix
	Triangle triProjected;
	
	Multiply_Matrix_Service::MultiplyMatrixVector(tri.p[0], triProjected.p[0], matProj);
	Multiply_Matrix_Service::MultiplyMatrixVector(tri.p[1], triProjected.p[1], matProj);
	Multiply_Matrix_Service::MultiplyMatrixVector(tri.p[2], triProjected.p[2], matProj);

	// Drop 3D to 2D
	Vec2d point1, point2, point3;

	point1.x = triProjected.p[0].x;
	point1.y = triProjected.p[0].y;

	point2.x = triProjected.p[1].x;
	point2.y = triProjected.p[1].y;

	point3.x = triProjected.p[2].x;
	point3.y = triProjected.p[2].y;			

	SDL_Color col;
	col.r=255; col.g=0; col.b=0; col.a = 255;

	Draw_Triangle_2d(point1, point2, point3, col);
}

void Renderer::Refresh_Screen(Mesh_Pipeline &this_mesh_pipeline){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);	
	for (auto this_mesh: this_mesh_pipeline.Get_Meshes()){
		std::vector<Triangle> tris = this_mesh.get_tris();
		for (auto tri: tris)
		{
			Project_Triangle_3d(tri);
		
		}
	}
	Draw_Reticle();
	SDL_RenderPresent(renderer);
} 

void Renderer::Draw_Reticle(){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Draw Reticle
	Vec2d single_point;
	single_point.x=0;
	single_point.y=0;
	single_point = Cartesian_to_Screen(single_point);

	SDL_RenderDrawPointF(renderer, single_point.x, single_point.y);
}

//Private Methods
Vec2d Renderer::Cartesian_to_Screen(Vec2d this_point)
{
	float HALF_SCREEN_W = (SCREEN_W)/2;
	float scaled_x = this_point.x*(HALF_SCREEN_W);
	this_point.x = scaled_x+(HALF_SCREEN_W);

	float HALF_SCREEN_H = (SCREEN_H)/2;
	float scaled_y = this_point.y*(HALF_SCREEN_H);
	this_point.y = SCREEN_H-(scaled_y+(HALF_SCREEN_H));
	return this_point;
} 

void Renderer::shutdown(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	

}