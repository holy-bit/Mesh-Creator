using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(MeshCreator))]
public class MeshEditor : Editor
{
    MeshCreator meshCreator;

    public override void OnInspectorGUI()
    {
        base.OnInspectorGUI();

        if (GUILayout.Button("Mesh Creator Window", GUILayout.Width(500),GUILayout.Height(30)))
        {
            MeshCreatorWindow.ShowWindow();
        }
    }

    private void OnSceneGUI()
    {
        Event guiEvent = Event.current;
        Vector2 mousePos = HandleUtility.GUIPointToWorldRay(guiEvent.mousePosition).origin;
        List<Vector2> points = meshCreator.GetPointsList();
        if (guiEvent.type == EventType.MouseDown && guiEvent.button == 0 && guiEvent.shift)
        {
            points.Add(mousePos);

        }
        for (int i = 0; i < points.Count; i++)
        {
            Handles.FreeMoveHandle(points[i], Quaternion.identity, 0.3f, Vector2.zero, Handles.CylinderHandleCap);
            if (i != 0)
            Handles.DrawLine(points[i-1],points[i]);
        }
    }

    void OnEnable()
    {
        meshCreator = (MeshCreator)target;
        MeshCreatorWindow.meshCreator = meshCreator;
    }
}
