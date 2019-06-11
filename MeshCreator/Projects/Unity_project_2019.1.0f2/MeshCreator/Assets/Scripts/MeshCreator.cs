using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;


[RequireComponent(typeof(MeshFilter))]
[RequireComponent(typeof(MeshRenderer))]
public class MeshCreator : MonoBehaviour
{
   


    //Mesh Values
    public List<Vector2> points = new List<Vector2>(); //Puntos del trazado
    public bool isClosed; //Boleano que marca si tiene que cerrar el trazado.
    public float roadWidth = 1; //Ancho del trazado a generar
    public float tiling = 1; //tileado de los uvs
    public float spacing = 1;

    

    public IntPtr path;//Puntero al Path de la dll

    public List<Vector2> GetPointsList() { return points; } //Devuelve la lista de puntos

    //Resetea la malla y puntos del objeto
    public void Reset()
    {
    points = new List<Vector2>();
    GetComponent<MeshFilter>().mesh = null;
    }


    //Actualiza la malla del objeto
    public void UpdateMesh()
    {
        transform.position = Vector3.zero;
        path = CreatePathWithPointsParse();
        GetComponent<MeshFilter>().mesh = LoadMesh();
        int textureRepeat = Mathf.RoundToInt(tiling * points.ToArray().Length * spacing * .05f);
        GetComponent<MeshRenderer>().sharedMaterial.mainTextureScale = new Vector2(1, textureRepeat);
    }


    //Crea un Path en la dll pasandole un array de puntos.
    public unsafe IntPtr CreatePathWithPointsParse()
    {
        Vector2[] pointst = points.ToArray();
        float[] pointsf = new float[pointst.Length*2];

        for (int i = 0; i < pointst.Length; i++)
        {

            pointsf[i * 2] = pointst[i].x;
            pointsf[i * 2 + 1] = pointst[i].y;
        }
        //Pin Memory
        fixed (float* p = pointsf)
        {
            return MeshCreatorWrapper.CreatePathWithPoints((IntPtr)p, pointst.Length);
        }
    }

    

    //Actualiza los puntos guardados en la dll a la lista de unity
    public void UpdatePoints()
    {
        points.Clear();
        float[] pointst = new float[MeshCreatorWrapper.GetNumberOfPoints(path) * 2];
        MeshCreatorWrapper.GetPointsData(path, pointst);
        for (int i = 0; i < MeshCreatorWrapper.GetNumberOfPoints(path); i++)
        {
            points.Add(new Vector2(pointst[i * 2], pointst[i * 2 + 1]));
        }
    }

    //Actualiza los datos desde la dll a unity y actualiza la composicion de la malla
    public Mesh LoadMesh()
    {
        MeshCreatorWrapper.CreateMesh(path, roadWidth, isClosed);

        Vector3[] vertscpp = new Vector3[MeshCreatorWrapper.GetVertexsSize(path)];
        Vector2[] uvscpp = new Vector2[MeshCreatorWrapper.GetUvsSize(path)];
        
        int[] index;
        UpdatePoints();

        
        float[] vertst = new float[MeshCreatorWrapper.GetVertexsSize(path)*2];
        float[] uvst = new float[MeshCreatorWrapper.GetUvsSize(path)*2];
        index = new int[MeshCreatorWrapper.GetTrisSize(path)];
        MeshCreatorWrapper.GetVertexsData(path,vertst);
        MeshCreatorWrapper.GetUVsData(path, uvst);
        MeshCreatorWrapper.GetIndexsData(path, index);
        
        for (int i = 0; i < MeshCreatorWrapper.GetVertexsSize(path);i++)
        {
            
            vertscpp[i] = new Vector3(vertst[i * 2], vertst[i * 2 + 1], 0);
        }

        for (int i = 0; i < MeshCreatorWrapper.GetUvsSize(path); i++)
        {
            uvscpp[i] = new Vector2(uvst[i * 2], uvst[i * 2 + 1]);
        }
        
        Mesh mesh = new Mesh();
        mesh.vertices = vertscpp;
        mesh.triangles = index;
        mesh.uv = uvscpp;

        return mesh;
    }
}
