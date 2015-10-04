#pragma once
#include "ShapeSphere.h"
#include "CompareLineSegmentWithSphere.h"
#include "CompareLineSegmentWithBox.h"

#pragma warning (disable: 4201)
//#include "glm-0.9.3.4/glm/glm.hpp"
#pragma warning (default: 4201)

#include <conio.h>



class MovementSphere :
	public ShapeSphere
{
public:
	MovementSphere(void);
	~MovementSphere(void){};

	MovementSphere(Vector3 _begin, Vector3 _end, Vector3 _beginAxis, Vector3 _endAxis, float radius, size_t moveId);

	void draw();
	void freeNode();

	const Vector3 & getBegin()
	{
		return begin;
	}

	const Vector3 & getEnd()
	{
		return end;
	}

	size_t getMoveId()
	{
		return m_OriginalId;
	}

private:

	Vector3 begin;
	Vector3 end;
	Vector3 m_begin_axis;
	Vector3 m_end_axis;
	float m_ToolRadius;
	size_t m_OriginalId;


	void bvh_knn(NeighborListType &neighborList, CheckListType & checkList, 
				const size_t & numberOfNeighbors, ComparePointWithSphere & pointSphereComparer,
				CompareLineWithPoint & pointLineComparer, const size_t & queryingMoveId);
};



class CompareLineWithPoint
{

	typedef TPoint3d<float> Vector3;

private:

	Vector3 m_Point;

public:

	CompareLineWithPoint(const Vector3 & point)
	{
		m_Point = point;
	}

	void idle(){}

	float getDistance(MovementSphere * move)
	{
		Vector3 direction = move->getEnd() - move->getBegin();

		float length = ~direction;
		direction /= length;

		Vector3 beginToPoint = m_Point - move->getBegin();
		float projection = beginToPoint*direction;

		if (projection <= 0)
		{
			return ~(m_Point - move->getBegin());
		}
		if (projection >= length)
		{
			return ~(m_Point - move->getEnd());
		}

		Vector3 projectedPoint = (move->getBegin() + projection*direction);
		return ~(m_Point - projectedPoint);

	}


	bool operator()(ShapeSphere* _move1, ShapeSphere* _move2) const
	{
		return _move1->getRanking() > _move2->getRanking();
	}

};



class CompareLineSegment
{
	typedef TPoint3d<float> Vector3;

private:

	CompareLineSegmentWithBox m_CompareUtils;
	CompareLineSegmentWithBox::Segment m_currentSegment;

public:

	CompareLineSegment(const CompareLineSegmentWithBox::Segment & currentSegment) //: m_CompareUtils(currentSegment)
	{
		m_currentSegment = currentSegment;
	}

	void idle(){}

	float getDistance(MovementSphere * _aMove)
	{
		CompareLineSegmentWithBox::Segment seg;
		seg.P0 = _aMove->getBegin();
		seg.P1 = _aMove->getEnd();
		return m_CompareUtils.dist3D_Segment_to_Segment(seg, m_currentSegment);
	}

	bool operator()(ShapeSphere* _move1, ShapeSphere* _move2) const
	{
		return _move1->getRanking() < _move2->getRanking();
	}

};



