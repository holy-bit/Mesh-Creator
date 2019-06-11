

#include "Serializer.hpp"

namespace Serial
{

	void Serializer::Save(string path, const vector<float >& Vector)
	{
		ofstream file(path, std::ios::out | std::ofstream::binary);


		int size = (int)Vector.size();
		file.write(reinterpret_cast<const char *>(&size), sizeof(size));


		for (auto& f : Vector) {

			file.write(reinterpret_cast<const char *>(&f), sizeof(float));
		}
		file.close();
	}

	std::vector<float > Serializer::Load(string path)
	{
		vector<float> Vector;
		ifstream file(path, std::ios::in | std::ifstream::binary);

		int size = 0;
		file.read(reinterpret_cast<char *>(&size), sizeof(size));
		Vector.resize(size);
		for (int n = 0; n < size; ++n)
		{

			float f;
			file.read(reinterpret_cast<char *>(&f), sizeof(float));
			Vector.push_back(f);

		}
		return Vector;
	}

}