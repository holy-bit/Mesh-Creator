
#include "Mesh_Creator_Controller.hpp"

namespace MC
{

	MC::Mesh_Creator_Controller& Mesh_Creator_Controller::getInstance()
	{
		static Mesh_Creator_Controller instance;
		return instance;
	}

	MC::Path* Mesh_Creator_Controller::CreatePath(float* array_Pointer, int number_of_points)
	{
		return  new Path(id++, array_Pointer, number_of_points);
	}

	MC::Path* Mesh_Creator_Controller::CreatePath()
	{
		return  new Path(id++);
	}

}