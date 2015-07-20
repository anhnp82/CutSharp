#ifndef __BoundingBox_hpp__
#define __BoundingBox_hpp__


//! implements a 3d bounding box
/*! The class members are 2 bboxCorners
	You can do union, intersection, comparisons
*/
template < class T > class BoundingBox  
{
public:
	typedef TPoint3d<T> bboxCorner;

	//! Constructor
	/*!
		This constructor initialize corners at (-max_value)-(max_value)
	*/
	BoundingBox()
	:UpperRightFarCorner( -mathdef::_maxvalue(T()),
		-mathdef::_maxvalue(T()), -mathdef::_maxvalue(T()) ), 
	 BottomLeftNearCorner( mathdef::_maxvalue(T()),
		mathdef::_maxvalue(T()), mathdef::_maxvalue(T()) )
	{
	}

	//! Constructor
	/*!
		This constructor takes two corners as parameters
		\param corner1 - first corner
		\param corner2 - second corner
	*/
	BoundingBox(const TPoint3d< T > &corner1, const TPoint3d< T > &corner2)
	{
		SetCorners(corner1, corner2);
	}


	//! GetBottomLeftNearCorner
	/*!
		\returns the BottomLeftNearCorner
	*/
	const bboxCorner &GetBottomLeftNearCorner() const
	{
		return BottomLeftNearCorner;
	}

	//! Set Bounding Box Corners
	/*!
		\param corner1 - first corner
		\param corner2 - second corner
	*/
	void SetCorners( const TPoint3d< T > &corner1,const TPoint3d< T > &corner2 )
	{
		UpperRightFarCorner.x(
			corner1.x() > corner2.x() ? corner1.x() : corner2.x());
		UpperRightFarCorner.y(
			corner1.y() > corner2.y() ? corner1.y() : corner2.y());
		UpperRightFarCorner.z(
			corner1.z() > corner2.z() ? corner1.z() : corner2.z());
		BottomLeftNearCorner.x(
			corner1.x() > corner2.x() ? corner2.x() : corner1.x());
		BottomLeftNearCorner.y(
			corner1.y() > corner2.y() ? corner2.y() : corner1.y());
		BottomLeftNearCorner.z(
			corner1.z() > corner2.z() ? corner2.z() : corner1.z());
	}

	//! GetUpperRightFarCorner
	/*!
		\returns the UpperRightFarCorner
	*/
	const bboxCorner &GetUpperRightFarCorner() const
	{
		return UpperRightFarCorner;
	}

	//! Equality operator
	bool operator==( const BoundingBox &toCompare )
	{
		return (BottomLeftNearCorner == toCompare.BottomLeftNearCorner &&
			UpperRightFarCorner == toCompare.UpperRightFarCorner);
	}

	//! GetWidth
	/*!
		\returns the width of the bounding box (x2-x1)
	*/
	T GetWidth() const
	{
		return UpperRightFarCorner.x() - BottomLeftNearCorner.x();
	}

	//! GetHeight
	/*!
		\returns the height of the bounding box (y2-y1)
	*/
	T GetHeight() const
	{
		return UpperRightFarCorner.y() - BottomLeftNearCorner.y();
	}

	//! GetDepth
	/*!
		\returns the depth of the bounding box (z2-z1)
	*/
	T GetDepth() const
	{
		return UpperRightFarCorner.z() - BottomLeftNearCorner.z();
	}

	//! GetVolume
	/*!
		\returns the volume of the bounding box
	*/
	T GetVolume() const
	{
		return GetWidth() * GetHeight() * GetDepth();
	}

	//! GetDiagonalLength
	/*!
		\returns the length of the main diagonal of the bounding box
	*/
	T GetDiagonalLength() const
	{
		return sqrt(GetWidth() * GetWidth() + GetHeight() * GetHeight() +
			GetDepth() * GetDepth());
	}

	//! += Operator
	/*!
		Makes the union of the two bounding boxes
	*/
	void operator+=( const BoundingBox &ta )
	{
		if (!this->IsInitialized() || this->IsEmpty())
		{
			*this = ta;
			return;
		}
		UpperRightFarCorner.x(mathdef::_max(UpperRightFarCorner.x(),
			ta.UpperRightFarCorner.x()));
		UpperRightFarCorner.y(mathdef::_max(UpperRightFarCorner.y(),
			ta.UpperRightFarCorner.y()));
		UpperRightFarCorner.z(mathdef::_max(UpperRightFarCorner.z(),
			ta.UpperRightFarCorner.z()));
		BottomLeftNearCorner.x(mathdef::_min(BottomLeftNearCorner.x(),
			ta.BottomLeftNearCorner.x()));
		BottomLeftNearCorner.y(mathdef::_min(BottomLeftNearCorner.y(),
			ta.BottomLeftNearCorner.y()));
		BottomLeftNearCorner.z(mathdef::_min(BottomLeftNearCorner.z(),
			ta.BottomLeftNearCorner.z()));
	}

	//! -= Operator
	/*!
		Makes the intersection of the two bounding boxes
	*/
	void operator-=( const BoundingBox &ta )
	{
		if (UpperRightFarCorner.x() < ta.BottomLeftNearCorner.x() ||
			UpperRightFarCorner.y() < ta.BottomLeftNearCorner.y() ||
			UpperRightFarCorner.z() < ta.BottomLeftNearCorner.z() ||
			BottomLeftNearCorner.x() > ta.UpperRightFarCorner.x() ||
			BottomLeftNearCorner.y() > ta.UpperRightFarCorner.y() ||
			BottomLeftNearCorner.z() > ta.UpperRightFarCorner.z())
		{
			//no intersection
			UpperRightFarCorner = TPoint3d<T>();
			BottomLeftNearCorner = TPoint3d<T>();
			return;
		}

		UpperRightFarCorner.x(_min(UpperRightFarCorner.x(),
			ta.UpperRightFarCorner.x()));
		UpperRightFarCorner.y(_min(UpperRightFarCorner.y(),
			ta.UpperRightFarCorner.y()));
		UpperRightFarCorner.z(_min(UpperRightFarCorner.z(),
			ta.UpperRightFarCorner.z()));
		BottomLeftNearCorner.x(_max(BottomLeftNearCorner.x(),
			ta.BottomLeftNearCorner.x()));
		BottomLeftNearCorner.y(_max(BottomLeftNearCorner.y(),
			ta.BottomLeftNearCorner.y()));
		BottomLeftNearCorner.z(_max(BottomLeftNearCorner.z(),
			ta.BottomLeftNearCorner.z()));
	}

	//! IsEmpty
	/*!
		\returns true if the corners are pointing to the same point
	*/
	bool IsEmpty() const
	{
		return (GetWidth() == 0.0 && GetHeight() == 0.0 && GetDepth() == 0.0);
	}

	//! IsPlane
	/*!
		\returns true if one of the dimensions is 0.0
	*/
	bool IsPlane() const
	{
		return (GetWidth() == 0.0 ||
			GetHeight() == 0.0 || GetDepth() == 0.0);
	}

	//! GetCenter
	/*!
		\returns the center of the bounding box
	*/
	TPoint3d< T > GetCenter()const
	{
		return TPoint3d< T >( static_cast<T>(BottomLeftNearCorner.x() + 0.5 * GetWidth() ),
			static_cast<T>( BottomLeftNearCorner.y() + 0.5 * GetHeight() ),
			static_cast<T>( BottomLeftNearCorner.z() + 0.5 * GetDepth()) );
	}


	//! IsOverlap
	/*!
		\returns true if bounding boxes overlap
	*/
	bool IsOverlap( const BoundingBox &ta ) const
	{
		if (UpperRightFarCorner.x() < ta.BottomLeftNearCorner.x() ||
			UpperRightFarCorner.y() < ta.BottomLeftNearCorner.y() ||
			UpperRightFarCorner.z() < ta.BottomLeftNearCorner.z() ||
			BottomLeftNearCorner.x() > ta.UpperRightFarCorner.x() ||
			BottomLeftNearCorner.y() > ta.UpperRightFarCorner.y() ||
			BottomLeftNearCorner.z() > ta.UpperRightFarCorner.z()
			)
				return false;
		return true;
	}

	//! Enlarge bbox so that bbox contains specified point.
	void EnlargeForPoint( TPoint3d< T > point )
	{
		// Adjust bounding box
		if ( point.x() < BottomLeftNearCorner.x() ) BottomLeftNearCorner.x( point.x() );
		if ( point.y() < BottomLeftNearCorner.y() ) BottomLeftNearCorner.y( point.y() );
		if ( point.z() < BottomLeftNearCorner.z() ) BottomLeftNearCorner.z( point.z() );
		if ( point.x() > UpperRightFarCorner.x() ) UpperRightFarCorner.x( point.x() );
		if ( point.y() > UpperRightFarCorner.y() ) UpperRightFarCorner.y( point.y() );
		if ( point.z() > UpperRightFarCorner.z() ) UpperRightFarCorner.z( point.z() );
	}

	bool IsInitialized() const
	{
		return !( UpperRightFarCorner.x() == -mathdef::_maxvalue(T()) &&
				UpperRightFarCorner.y() == -mathdef::_maxvalue(T()) &&
				UpperRightFarCorner.z() == -mathdef::_maxvalue(T()) &&
				BottomLeftNearCorner.x() == mathdef::_maxvalue(T()) &&
				BottomLeftNearCorner.y() == mathdef::_maxvalue(T()) &&
				BottomLeftNearCorner.z() == mathdef::_maxvalue(T()) );
	}

	//!  Uninitialize
	void Uninitialize()
	{
		UpperRightFarCorner = bboxCorner( -mathdef::_maxvalue(T()),
										  -mathdef::_maxvalue(T()), 
										  -mathdef::_maxvalue(T()) );

		BottomLeftNearCorner = bboxCorner( mathdef::_maxvalue(T()),
										   mathdef::_maxvalue(T()), 
										   mathdef::_maxvalue(T()) );
	}

	//! Check if point is in bounding box
	bool Contains( const bboxCorner& p ) const
	{
		return
			p.x() <= GetUpperRightFarCorner().x() &&
			p.y() <= GetUpperRightFarCorner().y() &&
			p.z() <= GetUpperRightFarCorner().z() &&
			p.x() >= GetBottomLeftNearCorner().x() &&
			p.y() >= GetBottomLeftNearCorner().y() &&
			p.z() >= GetBottomLeftNearCorner().z();
	}

	//! Check if bounding box is in bounding box
	bool Contains( const BoundingBox< T >& src ) const
	{
		return
			Contains(src.BottomLeftNearCorner) && 
			Contains(src.UpperRightFarCorner);
	}

	
	//! Check if point is in bounding box
	bool Contains( const bboxCorner& p, T offset ) const
	{
		return
			p.x() <= GetUpperRightFarCorner().x() + offset &&
			p.y() <= GetUpperRightFarCorner().y() + offset &&
			p.z() <= GetUpperRightFarCorner().z() + offset &&
			p.x() >= GetBottomLeftNearCorner().x() - offset &&
			p.y() >= GetBottomLeftNearCorner().y() - offset &&
			p.z() >= GetBottomLeftNearCorner().z() - offset;
	}
	inline bool IsOverlapAppPlane(const BoundingBox< T > &src) const
	{
		if (UpperRightFarCorner.x() < src.BottomLeftNearCorner.x() ||
			UpperRightFarCorner.y() < src.BottomLeftNearCorner.y() ||
			BottomLeftNearCorner.x() > src.UpperRightFarCorner.x() ||
			BottomLeftNearCorner.y() > src.UpperRightFarCorner.y())
				return false;
		return true;
	}
	//! Inflate bounding box
	/*! 
		\param const T dx delta to add to both edges in x direction
		\param const T dy delta to add to both edges in y direction
		\param const T dz delta to add to both edges in z direction
	*/
	void Inflate(const T dx, const T dy, const T dz)
	{
		const TPoint3d<T> offs(dx,dy,dz);
		BottomLeftNearCorner-=offs;
		UpperRightFarCorner+=offs;
	}

	class Iterator
	{
	public:
		Iterator( const BoundingBox<T> *bb, int idx ) : m_bb( bb ), m_idx( idx ) {}
		Iterator() : m_bb( NULL ), m_idx( 0 ) {}

		Iterator &operator++() { ++m_idx; return *this; }
		bool operator!=( const Iterator &i ) const { return m_idx != i.m_idx; }

		bboxCorner operator*() const
		{
			const bboxCorner &c1 = m_bb->UpperRightFarCorner;
			const bboxCorner &c2 = m_bb->BottomLeftNearCorner;
			return bboxCorner(
				( m_idx & 1 ) ? c1.x() : c2.x(),
				( m_idx & 2 ) ? c1.y() : c2.y(),
				( m_idx & 4 ) ? c1.z() : c2.z()
			);
		};

	private:
		const BoundingBox<T> *m_bb;
		int m_idx;
	};

	Iterator Begin() const { return Iterator( this, 0 ); }
	Iterator End() const { return Iterator( this, 8 ); }

protected:
	bboxCorner BottomLeftNearCorner, UpperRightFarCorner;
}; //end of BoundingBox class

//! + Operator
/*!
	\returns the union of the two bounding boxes
*/
template < class T > const BoundingBox< T > operator+(
	const BoundingBox< T > &first, const BoundingBox< T > &second )
{
	typename BoundingBox<T>::bboxCorner corner1, corner2;
	corner2.x(mathdef::_max(first.GetUpperRightFarCorner().x(), second.GetUpperRightFarCorner().x()));
	corner2.y(mathdef::_max(first.GetUpperRightFarCorner().y(), second.GetUpperRightFarCorner().y()));
	corner2.z(mathdef::_max(first.GetUpperRightFarCorner().z(), second.GetUpperRightFarCorner().z()));
	corner1.x(mathdef::_min(first.GetBottomLeftNearCorner().x(), second.GetBottomLeftNearCorner().x()));
	corner1.y(mathdef::_min(first.GetBottomLeftNearCorner().y(), second.GetBottomLeftNearCorner().y()));
	corner1.z(mathdef::_min(first.GetBottomLeftNearCorner().z(), second.GetBottomLeftNearCorner().z()));
	return BoundingBox<T>( corner1, corner2 );
}


#endif //__BoundingBox_hpp__
