

#include "Path.hpp"
#include <Serializer.hpp>
using namespace Serial;
namespace MC
{
	MC::Path::Path(int ID, float* array_Pointer, int number_of_points) : id(ID)
	{
		for (int i = 0; i < number_of_points; i++)
		{
			points.push_back(point(array_Pointer[i * 2], array_Pointer[i * 2 + 1]));
		}
	}

	MC::Path::Path(int ID) : id(ID)
	{

	}

	void MC::Path::Load(string path)
	{
		vector<float> data = Serializer::Load(path);
		points.clear();
		for (size_t i = data.size() / 4 + 1; i < data.size() / 2; i++)
		{
			points.push_back(point(data[i * 2], data[i * 2 + 1]));
		}
	}

	void MC::Path::Save(string path)
	{
		vector<float> data;
		for (size_t i = 0; i < points.size(); i++)
		{
			data.push_back(points[i].x);
			data.push_back(points[i].y);
		}
		Serializer::Save(path, data);
	}

	void MC::Path::AddPoint(float x, float y)
	{
		points.push_back(point(x, y));
	}

	void MC::Path::fillNativePointsArray(float* array_Pointer, std::vector<point>& data)
	{
		for (int i = 0; i < data.size(); i++)
		{
			array_Pointer[i * 2] = data[i].x;
			array_Pointer[i * 2 + 1] = data[i].y;
		}
	}

	void MC::Path::fillNativeArray(int* array_Pointer, std::vector<int>& data)
	{
		for (int i = 0; i < data.size(); i++)
		{
			array_Pointer[i] = data[i];
		}
	}

	int MC::Path::GetNumberOfPoints()
	{
		return (int)points.size();
	}

	int MC::Path::GetVertSize()
	{
		return (int)verts.size();
	}

	int MC::Path::GetUvsSize()
	{
		return (int)uvs.size();
	}

	int MC::Path::GetTrisSize()
	{
		return (int)tris.size();
	}

	void MC::Path::CreateMesh(float roadWidth, bool isClosed )
	{
		verts.clear();
		uvs.clear();
		tris.clear();
		int numTris = 2 * ((int)points.size() - 1) + ((isClosed) ? 2 : 0);

		int vertIndex = 0;
		int triIndex = 0;

		for (int i = 0; i < points.size(); i++)
		{
			Vector2f forward;
			if (i < points.size() - 1 || isClosed)
			{
				forward += points[(i + 1) % points.size()] - points[i];
			}
			if (i > 0 || isClosed)
			{
				forward += points[i] - points[(i - 1 + points.size()) % points.size()];
			}
			float length = std::sqrt(forward.x *forward.x + forward.y*forward.y);
			forward = forward / length;
			Vector2f left = Vector2f(-forward.y, forward.x);

			verts.push_back(points[i] + left * roadWidth * 0.5f);
			verts.push_back(points[i] - left * roadWidth * 0.5f);

			float completionPercent = i / (float)(points.size() - 1);
			float v = 1 - std::abs(2 * completionPercent - 1);
			uvs.push_back(Vector2f(0, v));
			uvs.push_back(Vector2f(1, v));

			if (i < points.size() - 1 || isClosed)
			{
				tris.push_back(vertIndex);
				tris.push_back((vertIndex + 2) % (points.size() * 2));
				tris.push_back(vertIndex + 1);

				tris.push_back(vertIndex + 1);
				tris.push_back((vertIndex + 2) % (points.size() * 2));
				tris.push_back((vertIndex + 3) % (points.size() * 2));
			}
			vertIndex += 2;
			triIndex += 6;
		}
	}


}
