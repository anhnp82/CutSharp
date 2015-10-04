#pragma once

//#include <GL/glew.h>
#include "app/glextensions.h"
#include "boost/unordered_map.hpp"
#include <queue>
#include "BoundingSphere.h"

//#define MAX_FLOAT = 3.40282e+38

using namespace std;
class CompareLineSegment;
class CompareLineSegmentWithSphere;
class CompareLineWithPoint;
class ComparePointWithSphere;

#include <conio.h>

class ShapeSphere
{
public:
	ShapeSphere(void);
	virtual ~ShapeSphere(void) 
	{
		//_cprintf("base destroy \n");
	};

	struct NeighborItem 
	{
		size_t id;
		float ranking;
	};

	typedef TPoint3d<float> Vector3;
	typedef boost::unordered_map< size_t, std::vector<NeighborItem> > KnnMapType;
	typedef priority_queue<ShapeSphere*, std::vector<ShapeSphere*>, CompareLineWithPoint> NeighborListType;
	typedef priority_queue<ShapeSphere*, std::vector<ShapeSphere*>, ComparePointWithSphere> CheckListType;

	virtual void draw() = 0;

	const BoundingSphere & getBoundingSphere()
	{
		return m_BoundingSphere;
	}

	virtual void freeNode() = 0;

	float getRanking()
	{
		return ranking;
	}

	void setRanking(float aRank)
	{
		this->ranking = aRank;
	}

	virtual void bvh_knn(NeighborListType &neighborList, CheckListType & checkList, 
						const size_t & numberOfNeighbors, ComparePointWithSphere & pointSphereComparer, 
						CompareLineWithPoint & pointLineComparer, const size_t & queryingMoveId) = 0;

	virtual void buildKnnExactMap(KnnMapType & knnMap, const size_t & k, ShapeSphere *startNode) = 0;

protected:

	float ranking;
	BoundingSphere m_BoundingSphere; 

};







