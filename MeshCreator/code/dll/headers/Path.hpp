
#ifndef PATH_HEADER
#define PATH_HEADER

#include <vector>
#include <cmath>
using namespace std;
namespace MC
{
	struct Vector2f
	{
	public:
		float x;
		float y;
		Vector2f(float x = 0, float y = 0) : x(x), y(y) {}
		Vector2f(const Vector2f &p) { x = p.x; y = p.y; }

		Vector2f operator - (Vector2f const &vec2) {
			return Vector2f(this->x - vec2.x, this->y - vec2.y);
		}
		Vector2f operator + (Vector2f const &vec2) {
			return Vector2f(this->x + vec2.x, this->y + vec2.y);
		}
		Vector2f operator += (Vector2f const &vec2) {
			return *this = *this + vec2;
		}

		Vector2f operator * (float const &num) {
			return Vector2f(this->x *num, this->y * num);
		}

		Vector2f operator / (float const &num) {
			return Vector2f(this->x / num, this->y / num);
		}
	};
	typedef Vector2f point;

	class Path
	{

	public:
		int id; /**< Identificador del Path */
		vector<point>points; /**< Puntos del Path */
		vector<point>verts; /**< Vertices que conforman la malla */
		vector<point>uvs; /**< UVs que conforman la malla */
		vector<int>tris; /**< Indices de triangulos que conforman la malla */


		//! Crea un Path vacio.
		/*! <b>Method:  </b>     Path */
		/*! <b>FullName:</b>     MC::Path::Path */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   int ID
		* @return  
		*/
		Path(int ID);

		//! Crea un Path a partir de un array de puntos.
		/*! <b>Method:  </b>     Path */
		/*! <b>FullName:</b>     MC::Path::Path */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   int ID
		* @param   float * array_Pointer
		* @param   int number_of_points
		* @return  
		*/
		Path(int ID, float* array_Pointer, int number_of_points);

		//! Carga los datos del Path a partir de un archivo binario.
		/*! <b>Method:  </b>     Load */
		/*! <b>FullName:</b>     MC::Path::Load */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   string path
		* @return  void
		*/
		void Load(string path);

		//! Guarda los datos del Path en un archivo binario.
		/*! <b>Method:  </b>     Save */
		/*! <b>FullName:</b>     MC::Path::Save */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   string path
		* @return  void
		*/
		void Save(string path);

		//! Añade un punto al Path.
		/*! <b>Method:  </b>     AddPoint */
		/*! <b>FullName:</b>     MC::Path::AddPoint */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   float x
		* @param   float y
		* @return  void
		*/
		void AddPoint(float x, float y);
		
		//! Rellena un array de float a partir de un puntero con los datos de un vector de puntos.
		/*! <b>Method:  </b>     fillNativePointsArray */
		/*! <b>FullName:</b>     MC::Path::fillNativePointsArray */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   float * array_Pointer
		* @param   vector<point> & data
		* @return  void
		*/
		void fillNativePointsArray(float* array_Pointer, vector<point>& data);

		//! Rellena un array de float a partir de un puntero con los datos de un vector de int.
		/*! <b>Method:  </b>     fillNativeArray */
		/*! <b>FullName:</b>     MC::Path::fillNativeArray */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   int * array_Pointer
		* @param   vector<int> & data
		* @return  void
		*/
		void fillNativeArray(int* array_Pointer, vector<int>& data);

		//! Devuelve el numero de puntos que contiene el Path.
		/*! <b>Method:  </b>     GetNumberOfPoints */
		/*! <b>FullName:</b>     MC::Path::GetNumberOfPoints */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  int
		*/
		int GetNumberOfPoints();

		//! Devuelve el tamaño del vector de vertices.
		/*! <b>Method:  </b>     GetVertSize */
		/*! <b>FullName:</b>     MC::Path::GetVertSize */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  int
		*/
		int GetVertSize();

		//! Devuelve el tamaño del vector de Uvs.
		/*! <b>Method:  </b>     GetUvsSize */
		/*! <b>FullName:</b>     MC::Path::GetUvsSize */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  int
		*/
		int GetUvsSize();

		//! Devuelve el tamaño del vector de triangulos.
		/*! <b>Method:  </b>     GetTrisSize */
		/*! <b>FullName:</b>     MC::Path::GetTrisSize */
		/*! <b>Access:  </b>     public  */
		/**
		* @return  int
		*/
		int GetTrisSize();


		//! Crea la malla a partir de los puntos que contiene el Path, puediendole decir el grosor y si es un circuito cerrado.
		/*! <b>Method:  </b>     CreateMesh */
		/*! <b>FullName:</b>     MC::Path::CreateMesh */
		/*! <b>Access:  </b>     public  */
		/**
		* @param   float roadWidth
		* @param   bool isClosed
		* @return  void
		*/
		void CreateMesh(float roadWidth = 1, bool isClosed = false);


	};
}

#endif