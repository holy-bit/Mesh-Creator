#pragma once

#ifndef SERIALIZER_HEADER
#define SERIALIZER_HEADER

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

namespace Serial
{
	class Serializer
	{
	public:

		//! Serializa en un archivo binario un vector de floats.
		/*! <b>Method:  </b>     Save */
		/*! <b>FullName:</b>     Serial::Serializer::Save */
		/*! <b>Access:  </b>     public static  */
		/**
		* @param   string path
		* @param   const vector<float > & Vector
		* @return  void
		*/
		static void Save(string path, const vector<float >& Vector);

		//! Deserializa un archivo binario devolviendolo en un vector de floats.
		/*! <b>Method:  </b>     Load */
		/*! <b>FullName:</b>     Serial::Serializer::Load */
		/*! <b>Access:  </b>     public static  */
		/**
		* @param   string path
		* @return  std::vector<float >
		*/
		static vector<float > Load(string path);

	};
}

#endif // !SERIALIZER_HEADER