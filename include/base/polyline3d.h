#ifndef _WGEO_CORE_POLYLINE3D_
#define _WGEO_CORE_POLYLINE3D_

class Polyline3d {
public:
    Polyline3d(Vector3* vertices, int vertex_count, bool closed);
    virtual ~Polyline3d();
    int VertexCount() const;
    Vector3 GetVertex(int i) const;
    void SetVertex(int i, const Vector3& vertex);
private:
    int m_vertex_count;
    Vector3* m_vertices;
    bool m_closed;
};

inline Polyline3d::Polyline3d(Vector3* vertices, int vertex_count, bool closed) {
    m_vertices = vertices;
    m_vertex_count = vertex_count;
    m_closed = closed;
}

inline Polyline3d::~Polyline3d() {
    delete [] m_vertices;
}

inline int Polyline3d::VertexCount() const {
    return m_vertex_count;
}

inline Vector3 Polyline3d::GetVertex(int i) const {
    return m_vertices[i];
}

inline void Polyline3d::SetVertex(int i, const Vector3& vertex) {
    m_vertices[i] = vertex;
}

#endif