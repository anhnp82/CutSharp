#include "MovementSphere.h"
//#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <queue>



MovementSphere::MovementSphere(void)
{
}



void MovementSphere::freeNode()
{
	//_cprintf("free leaf %d \n", m_OriginalId);
}



MovementSphere::MovementSphere(ShapeSphere::Vector3 _begin, ShapeSphere::Vector3 _end, 
							   Vector3 begin_axis, Vector3 end_axis, float radius, size_t moveId) 
{
	begin = _begin;
	end = _end;
	m_OriginalId = moveId;
	m_ToolRadius = radius;
	m_begin_axis = begin_axis;
	m_end_axis = end_axis;

	m_BoundingSphere.init(begin, end);
}



void MovementSphere::draw()
{
	//glBegin(GL_LINES);
	//
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(begin.x(), begin.y(), begin.z());
	//glVertex3f(end.x(), end.y(), end.z());
	//
	//glEnd();

	//_cprintf("move id: %d \n", m_OriginalId );
}



void MovementSphere::bvh_knn(NeighborListType &neighborList, CheckListType & checkList, 
							const size_t & numberOfNeighbors, ComparePointWithSphere & pointSphereComparer,
							CompareLineWithPoint & pointLineComparer, const size_t & queryingMoveId)
{

	if ( queryingMoveId == this->m_OriginalId )
	{
		return;
	}

	float distance = pointLineComparer.getDistance(this);
	this->setRanking(distance);

	//_cprintf("distance line - sphere %f \n", distance);

	if (neighborList.empty())
	{
		neighborList.push(this);
		return;
	}
	else
	{
		ShapeSphere* kth_neighbor = neighborList.top();

		if (distance < kth_neighbor->getRanking() || neighborList.size() < numberOfNeighbors)
		{

			//to do
			//remove the co-linear continuous neighbors of the top 4
			//if (neighborList.size() < 5)
			{
				neighborList.push(this);
			}
			
		}
	}
	//only keep numberOfNeighbors
	while (neighborList.size() > numberOfNeighbors)
	{
		//_cprintf("neighborList size %d \n", neighborList.size());
		neighborList.pop();
	}

	//dummy by pass warning
	checkList.size();
	pointSphereComparer.idle();
	
}

