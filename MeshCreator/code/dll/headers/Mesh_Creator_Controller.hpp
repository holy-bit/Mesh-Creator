
#ifndef MESH_CREATOR_CONTROLLER_HEADER
#define MESH_CREATOR_CONTROLLER_HEADER

#define MC_API __declspec(dllexport)


#include "Path.hpp"

namespace MC
{

	class Mesh_Creator_Controller
	{

	public:
		int id; /**< identificador de los objetos. */


		//! Devuelve la instancia del singleton, si se llama por primera vez crea el objeto.
		/*! <b>Method:  </b>     getInstance */
		/*! <b>FullName:</b>     MC::Mesh_Creator_Controller::getInstance */
		/*! <b>Access:  </b>     public static  */
		/**
		* @return  MC::Mesh_Creator_Controller&
		*/
		static Mesh_Creator_Controller& getInstance();

		//! Crea un Path vacio.
		/*! <b>Method:  </b>     CreatePath */
		/*! <b>FullName:</b>     MC::Mesh_Creator_Controller::CreatePath */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  MC::Path*
		*/
		Path* CreatePath();

		//! Crea un Path a partir de un array de puntos.
		/*! <b>Method:  </b>     CreatePath */
		/*! <b>FullName:</b>     MC::Mesh_Creator_Controller::CreatePath */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   float * array_Pointer
		* @param   int number_of_points
		* @return  MC::Path*
		*/
		Path* CreatePath(float* array_Pointer, int number_of_points);

	};


	extern "C"
	{
		MC_API void AddPoint(Path* path, float x, float y) { path->AddPoint(x, y); };

		MC_API Path*  CreatePath() { return Mesh_Creator_Controller::getInstance().CreatePath(); }

		MC_API Path*  CreatePathWithPoints(float* array_Pointer, int number_of_points) { return Mesh_Creator_Controller::getInstance().CreatePath(array_Pointer, number_of_points); }

		MC_API int  GetPathId(Path* path) { return path->id; }

		MC_API void GetPoints(Path* path, float* data) { path->fillNativePointsArray(data, path->points); }

		MC_API void GetVertexs(Path* path, float* data) { path->fillNativePointsArray(data,path->verts); }

		MC_API void GetUvs(Path* path, float* data){ path->fillNativePointsArray(data,path->uvs); }

		MC_API void GetIndexs(Path* path, int* data) { path->fillNativeArray(data,path->tris); }

		MC_API void CreateMesh(Path* path, float roadWidth = 1, bool isClosed = false){ path->CreateMesh(roadWidth,isClosed); }

		MC_API void Save(Path* path, char* savepath){ path->Save(savepath); }

		MC_API void Load(Path* path, char* loadpath){ path->Load(loadpath); }

		MC_API int GetNumberOfPoints(Path* path) { return path->GetNumberOfPoints(); };

		MC_API int GetVertexsSize(Path* path) { return path->GetVertSize(); };

		MC_API int GetUvsSize(Path* path) { return path->GetUvsSize(); };

		MC_API int GetTrisSize(Path* path) { return path->GetTrisSize(); };
	}
}

#endif