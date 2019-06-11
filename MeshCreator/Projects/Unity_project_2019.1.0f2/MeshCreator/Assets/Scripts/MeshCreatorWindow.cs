using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class MeshCreatorWindow : EditorWindow
{
    static public MeshCreator meshCreator;
    static public string savePath = "../../../Assets/Saves";
    static public string loadPath = "../../../Assets/Saves";
    [MenuItem("Window/MeshCreatorSettings")]

    //Mostrar ventana
    public static void ShowWindow()
    {
        GetWindow<MeshCreatorWindow>("Mesh Creator");
    }

    private void OnGUI()
    {
        if (meshCreator != null)
        {
            Object target = meshCreator;
            SerializedObject so = new SerializedObject(meshCreator);
            so.Update();
            SerializedProperty isClosed = so.FindProperty("isClosed");

            EditorGUILayout.PropertyField(isClosed, true); // True means show children
            SerializedProperty roadWidth = so.FindProperty("roadWidth");

            EditorGUILayout.PropertyField(roadWidth, true); // True means show children
            SerializedProperty stringsProperty = so.FindProperty("points");

            EditorGUILayout.PropertyField(stringsProperty, true); // True means show children
            so.ApplyModifiedProperties();

            EditorGUI.BeginChangeCheck();
            if (GUILayout.Button("UpdateMesh"))
            {
                meshCreator.UpdateMesh();
            }
            if (GUILayout.Button("Reset"))
            {
                meshCreator.Reset();
            }
            EditorGUI.EndChangeCheck();
        }

        GUILayout.Label("Save/Load", EditorStyles.boldLabel);

        EditorGUILayout.BeginHorizontal();
        {
            if (GUILayout.Button("Save", GUILayout.Width(150)))
            {
                string path = EditorUtility.SaveFilePanel("Save Path as .mc", savePath, "Path" + MeshCreatorWrapper.GetPathId(meshCreator.path) + ".mc", "mc");
                MeshCreatorWrapper.Save(meshCreator.path, path);
            }
            EditorGUILayout.DelayedTextField("Save Path:", savePath, GUILayout.Width(300));
            if (GUILayout.Button("...", GUILayout.Width(32)))
            {
                savePath = EditorUtility.OpenFolderPanel("Save Path", savePath, "");
            }
        }
        EditorGUILayout.EndHorizontal();


        EditorGUILayout.BeginHorizontal();
        {
            if (GUILayout.Button("Load", GUILayout.Width(150)))
            {
                string path = EditorUtility.OpenFilePanel("Load Path as .mc", loadPath, "mc");
                meshCreator.path = MeshCreatorWrapper.CreatePath();
                MeshCreatorWrapper.Load(meshCreator.path, path);
                meshCreator.UpdatePoints();
                meshCreator.UpdateMesh();
            }
            EditorGUILayout.DelayedTextField("Load Path:", loadPath, GUILayout.Width(300));
            if (GUILayout.Button("...", GUILayout.Width(32)))
            {
                loadPath = EditorUtility.OpenFolderPanel("Load Path", loadPath, "");
            }
        }
        EditorGUILayout.EndHorizontal();
    }

}
