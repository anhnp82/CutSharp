//http://doc.qt.io/qt-4.8/qglbuffer.html
//http://doc.qt.io/qt-5/qopenglvertexarrayobject.html

// to do: attach move id for each vertex using NN search see also TestRenderder
// for each vertex, query knn moves => load move list first

#include <qvector3d.h>
#include "Shape.h"
#include "ShapeSphere.h"
#include "BVH.h"
#include "BVHSphere.h"

using namespace std;

class CDataProcessing
{
public:
	// A structure for our triangle vertex type.
	struct TriangleVertex
	{
		QVector3D position;
		QVector3D normal;
		QVector3D nearestMoveId; // store the nearest id of a linear cut
	};

	typedef vector<TriangleVertex> VertexList;

	CDataProcessing();
	~CDataProcessing();

private:
	VertexList m_VertexList;
};

CDataProcessing::CDataProcessing()
{
}

CDataProcessing::~CDataProcessing()
{
}


