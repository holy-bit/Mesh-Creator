using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;

public class MeshCreatorWrapper : MonoBehaviour
{
    // The imported function
    [DllImport("MeshCreator_vs-2017")]
    public static extern int GetPathId(IntPtr path);

    [DllImport("MeshCreator_vs-2017")]
    public static extern IntPtr CreatePath();

    [DllImport("MeshCreator_vs-2017")]
    public static extern IntPtr CreatePathWithPoints(IntPtr arrayPointer, int numberOfPoints);

    [DllImport("MeshCreator_vs-2017")]
    public static extern void AddPoint(IntPtr path, float x, float y);

    [DllImport("MeshCreator_vs-2017")]
    public static extern int GetNumberOfPoints(IntPtr path);

    [DllImport("MeshCreator_vs-2017")]
    public static extern void GetPoints(IntPtr path, IntPtr data);
    [DllImport("MeshCreator_vs-2017")]
    public static extern void GetVertexs(IntPtr path, IntPtr data);
    [DllImport("MeshCreator_vs-2017")]
    public static extern void GetIndexs(IntPtr path, IntPtr data);
    [DllImport("MeshCreator_vs-2017")]
    public static extern void GetUvs(IntPtr path, IntPtr data);
    [DllImport("MeshCreator_vs-2017")]
    public static extern void CreateMesh(IntPtr path, float roadWidth = 1, bool isClosed = false);
    [DllImport("MeshCreator_vs-2017")]
    public static extern int GetVertexsSize(IntPtr path);
    [DllImport("MeshCreator_vs-2017")]
    public static extern int GetUvsSize(IntPtr path);
    [DllImport("MeshCreator_vs-2017")]
    public static extern int GetTrisSize(IntPtr path);

    [DllImport("MeshCreator_vs-2017")]
    public static extern void Save(IntPtr path, string savePath);

    [DllImport("MeshCreator_vs-2017")]
    public static extern void Load(IntPtr path, string loadPath);

    //Pasa un puntero de un array para que lo rellene la dll con los vertices que tiene guardados
    public static unsafe void GetVertexsData(IntPtr path, float[] outArray)
    {
        //Pin Memory
        fixed (float* p = outArray)
        {
            GetVertexs(path, (IntPtr)p);
        }
    }

    //Pasa un puntero de un array para que lo rellene la dll con los Uvs que tiene guardados
    public static unsafe void GetUVsData(IntPtr path, float[] outArray)
    {
        //Pin Memory
        fixed (float* p = outArray)
        {
            GetUvs(path, (IntPtr)p);
        }
    }


    //Pasa un puntero de un array para que lo rellene la dll con los puntos que tiene guardados
    public static unsafe void GetPointsData(IntPtr path, float[] outArray)
    {
        //Pin Memory
        fixed (float* p = outArray)
        {
            GetPoints(path, (IntPtr)p);
        }
    }

    //Pasa un puntero de un array  para que lo rellene la dll con los indices que tiene guardados
    public static unsafe void GetIndexsData(IntPtr path, int[] outArray)
    {
        //Pin Memory
        fixed (int* p = outArray)
        {
            GetIndexs(path, (IntPtr)p);
        }
    }
}
