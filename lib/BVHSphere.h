#pragma once

#include <algorithm>
#include <vector>
#include "ShapeSphere.h"
#include "CompareLineSegmentWithSphere.h"
#include "MovementSphere.h"

#include <conio.h>

class BVHSphere : public ShapeSphere
{
public:
	BVHSphere(void);
	~BVHSphere(void)
	{
		//_cprintf("bvh destroy \n");
	};

	BVHSphere(std::vector<ShapeSphere*> & moveList); 

	ShapeSphere* buildBranch(std::vector<ShapeSphere*> & shapes, size_t begin, size_t shape_size);

	BVHSphere(ShapeSphere* priml, ShapeSphere* prim2); 
	BVHSphere(ShapeSphere* priml, ShapeSphere* prim2, const BoundingSphere & _bbox); 

	void draw();

	void freeNode();

	void buildKnnExactMap(KnnMapType & knnMap, const size_t & k, ShapeSphere *startNode);

	void allNNExact(std::vector<ShapeSphere*> &neighborList, size_t numberOfNeighbors, ShapeSphere *startNode);

	static const int BVH_TEX_SIZE = 800;

private:

	void bvh_knn(NeighborListType &neighborList, CheckListType & checkList, 
				const size_t & numberOfNeighbors, ComparePointWithSphere & pointSphereComparer,
				CompareLineWithPoint & pointLineComparer, const size_t & queryingMoveId);

	ShapeSphere* left; 
	ShapeSphere* right;

};



class CmpSphere
{
private:
	int axis;
public:

	CmpSphere(const int & iAxis) {axis = iAxis;}

	bool operator()(ShapeSphere* bvh1, ShapeSphere* bvh2) const
	{
		return bvh1->getBoundingSphere().getCenter()[axis] < bvh2->getBoundingSphere().getCenter()[axis];
	}

};



