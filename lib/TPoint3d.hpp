#ifndef __TPoint3d_hpp__
#define __TPoint3d_hpp__

#include <exception> 
#include <limits>

#define _min(a, b) ((a) < (b) ? (a) : (b))
#define _max(a, b) ((a) > (b) ? (a) : (b)) 


//#############################################################################

#if defined (_WIN32)
	#define INLINE	__forceinline
#elif defined(linux)
	#define INLINE
#endif

	//!This struct represents a 3d point.
	/*!The 3d point is an array with 3 dimension components (x,y,z).
	*/
	template< class T > struct TPoint3d
	{
		// DEFAULT PUBLIC NON-VIRTUAL DESTRUCTOR IS USED IN THIS CLASS
	public:

//#############################################################################
		
		//!Sets 3d point to origin.
		INLINE TPoint3d()
		{
			elems[0] = elems[1] = elems[2] = (T)0.; 
			// cast is needed otherwise causes a warning when used with integer types MST
		}
		
//#############################################################################

		//!Set 3d point
		/*!Sets the 3d point to the new position.
			\param first constant x-coordinate of the 3d point
			\param second constant y-coordinate of the 3d point
			\param third constant z-coordinate of the 3d point
		*/
		INLINE TPoint3d( const T first, const T second, const T third )
		{
			elems[0] = first;
			elems[1] = second;
			elems[2] = third;
		}

//#############################################################################

		//!Copy 3d point
		/*!Creates a exact copy of a given 3d point 
		   \param tc tool to create a copy of
		*/
		INLINE TPoint3d( const TPoint3d &tc )
		{
			elems[0] = tc.elems[0];
			elems[1] = tc.elems[1];
			elems[2] = tc.elems[2];
		}

//#############################################################################

		//!Set 3d point
		/*!Sets the 3d point to the new position.
			\param ar const array of the 3d point elements
		*/
		INLINE TPoint3d( const T ar[] )
		{
			elems[0] = ar[0];
			elems[1] = ar[1];
			elems[2] = ar[2];
		}

//#############################################################################

		//!Assigment operator
		/*!Assigns one 3d point object to another
		  \param tc tool to copy the information from
		  \returns current 3d point with copied information
		*/
#ifdef  _WIN64
		//VC8 bug, if inline the assignment operator sometimes works wrong
		//because of a bug in the x64 VC8 optimizer
		const TPoint3d& operator=( const TPoint3d &tc )
#else
		INLINE	const TPoint3d& operator=( const TPoint3d &tc )
#endif
		{
			if( this != &tc )
			{
				elems[0] = tc.elems[0];
				elems[1] = tc.elems[1];
				elems[2] = tc.elems[2];
			}

			return *this;
		}

//#############################################################################

		//!Assigment operator
		/*!Assigns one 3d point an array
		  \param ar tool to copy the information from an array with 3d point information
		  \returns current 3d point with copied information
		*/
		const TPoint3d& operator=( const T ar[] )
		{
			elems[0] = ar[0];
			elems[1] = ar[1];
			elems[2] = ar[2];
			return *this;
		}
//#############################################################################

		//!Equality operator
		/*!Are given tools equal?
		  \param tc tool to compare the current tool with
		  \returns <b>true</b> if both tools contain the same parameters,
		  <b>false</b> otherwise
		*/
		INLINE const bool operator==( const TPoint3d &tc ) const
		{
			// !!! DO NOT USE memcpy or it will fail when comparing -0.0 and 0.0 floating point values.
			return x() == tc.x() && y() == tc.y() && z() == tc.z();
		}

//#############################################################################

		//!Inequality operator
		/*!Are given tools equal?
		  \param tc tool to compare the current tool with
		  \returns <b>false</b> if both tools contain the same parameters,
		  <b>true</b> otherwise
		*/
		INLINE const bool operator!=( const TPoint3d &tc ) const
		{
			return !((*this) == tc);
		}

//#############################################################################

		//!Set 3d point
		/*!Sets new x-coordinate of the 3d point.
			\param newx const x-coordinate of the 3d point
		*/
		INLINE void x( const T & newx )
		{
			elems[0] = newx;
		}

//#############################################################################

		//!Set 3d point
		/*!Sets new y-coordinate of the 3d point.
			\param newy const y-coordinate of the 3d point
		*/
		INLINE void y( const T & newy )
		{
			elems[1] = newy;
		}

//#############################################################################

		//!Set 3d point
		/*!Sets new z-coordinate of the 3d point.
			\param newz const z-coordinate of the 3d point
		*/
		INLINE void z( const T & newz )
		{
			elems[2] = newz;
		}

//#############################################################################

		//!Get x-coordinate
		/*!Gets the x-coordinate of the 3d point as a reference.
			\returns constant reference to the x-coordinate
		*/
		INLINE const T & x() const
		{
			return elems[0];
		}

//#############################################################################

		//!Get y-coordinate
		/*!Gets the y-coordinate of the 3d point as a reference.
			\returns constant reference to the y-coordinate
		*/
		INLINE const T & y() const
		{
			return elems[1];
		}

//#############################################################################

		//!Get z-coordinate
		/*!Gets the z-coordinate of the 3d point as a reference.
			\returns constant reference to the z-coordinate
		*/
		INLINE const T & z() const
		{
			return elems[2];
		}
		
//#############################################################################

		//!Get 3d point
		/*!Gets a pointer to the 3d point array.
			\returns constant pointer to the 3d point array
		*/
		INLINE operator const T*() const
		{
			return elems;
		}

//#############################################################################

		//!Get 3d point
		/*!Gets a pointer to the 3d point array.
			\returns pointer to the 3d point array
		*/
		INLINE operator T*()
		{
			return elems;
		}

//#############################################################################

		//!+= operator
		/*!Add each component of a 3d point to another
			\param ta const reference of a 3d point
		*/
		INLINE void operator+=( const TPoint3d &ta )
		{
			elems[0] += ta.elems[0];
			elems[1] += ta.elems[1];
			elems[2] += ta.elems[2];
		}

//#############################################################################

		//!-= operator
		/*!Subtract each component of a 3d point with another
			\param ta const reference of a 3d point
		*/ 
		INLINE void operator-=( const TPoint3d &ta )
		{
			elems[0] -= ta.elems[0];
			elems[1] -= ta.elems[1];
			elems[2] -= ta.elems[2];
		}

//#############################################################################

		//!Squared length
		/*!Returns squared length of the vector represented by the 3d point
			\returns constant length of the vector represented by the 3d point.
		*/
		INLINE const T Length2() const
		{
			return (elems[0] * elems[0] + elems[1] * elems[1] + 
											elems[2] * elems[2] );
		}

//#############################################################################

		//!~ operator
		/*!Returns length of the vector represented by the 3d point
			\returns constant length of the vector represented by the 3d point.
		*/
		INLINE const T operator~() const
		{
			#ifdef  _WIN64
				return (T)sqrt( static_cast<double>(elems[0] * elems[0] + 
				         elems[1] * elems[1] + 
						 elems[2] * elems[2]) );
			#else
					return sqrt( elems[0] * elems[0] + 
						elems[1] * elems[1] + 
						elems[2] * elems[2] );
			#endif
		}

//#############################################################################

		//!*= operator
		/*!Multiply each 3d component with a factor
			\param scFactor const reference to a factor 
		*/
		INLINE void operator*=( const T& scFactor )
		{
			elems[0] = elems[0] * scFactor;
			elems[1] = elems[1] * scFactor;
			elems[2] = elems[2] * scFactor;
		}

//#############################################################################

		//!/= operator
		/*!Divide each 3d component with a factor
			\param scFactor const reference to a factor 
		*/
		INLINE void operator/=( const T scFactor )
		{
			elems[0] = elems[0] / scFactor;
			elems[1] = elems[1] / scFactor;
			elems[2] = elems[2] / scFactor;
		}

//#############################################################################

		//!Normalize function
		/*!Normalize this vector (3d point)
		*/
		INLINE const TPoint3d<T>& Normalize()
		{
			if(*this == TPoint3d(0, 0, 0))
				throw std::exception("Exception::CANNOT_NORMALIZE_NULL_VEC");
			(*this) /= ~(*this);
			return *this;
		}

		//! Equality method
		/*
			\param toCompare const reference to a 3d point
			\returns bool if this vector si equal with toComapre vector
		*/
		INLINE bool is_eq(const TPoint3d& toComapre, const T & tolerance = std::numeric_limits<T>::epsilon()) const
		{
			const TPoint3d diff(toComapre - *this);
			const T diffSquare = diff * diff;

			if(diffSquare < tolerance)
				return true;
			else
				return false;
		}

//#############################################################################

	private:
		T elems[3];
	};

	template < class T > INLINE TPoint3d<T> operator-(
		const TPoint3d<T> &p )
	{
		return TPoint3d<T>( -p.x(), -p.y(), -p.z() );
	}

//#############################################################################

	//!+ operator
	/*!Add each component of a 3d point to another
		\param first const reference of a 3d point
		\param second const reference of a 3d point
		\returns added 3d point
	*/
	template < class T > INLINE TPoint3d<T> operator+( 
		const TPoint3d<T> &first, const TPoint3d<T> &second )
	{
		return TPoint3d<T>( first.x() + second.x(),
				first.y() + second.y(),
				first.z() + second.z() );
	}

//#############################################################################

	//!- operator
	/*!Subtract each 3d point component from another
		\param first const reference of a 3d point
		\param second const reference of a 3d point
		\returns subtracted 3d point
	*/
	template < class T > INLINE TPoint3d<T> operator-( 
		const TPoint3d<T> &first, const TPoint3d<T> &second )
	{
		return TPoint3d<T>( first.x() - second.x(),
			first.y() - second.y(),
			first.z() - second.z() );
	}
	
//#############################################################################

	//!* operator
	/*!Multiply each 3d component with a factor.
		\param pt const reference to a 3d point
		\param factor const reference to a factor to multiply with
		\returns new 3d point object
	*/
	template < class T >INLINE const TPoint3d<T> operator*( 
		const TPoint3d<T> &pt, const T factor )
	{
		return TPoint3d<T>( pt.x()*factor, pt.y()*factor,
												pt.z()*factor);
	}

//#############################################################################

	//!* operator
	/*!Multiply each 3d component with a factor.
		\param factor const reference to a factor to multiply with
		\param pt const reference to a 3d point	
		\returns new 3d point object
	*/
	template < class T > INLINE const TPoint3d<T> operator*( 
		const T factor, const TPoint3d<T> &pt )
	{
		return TPoint3d<T>( pt.x()*factor, pt.y()*factor,
												pt.z()*factor);
	}

//#############################################################################

	//!/ operator
	/*!Divide each 3d component with a factor.
		\param pt const reference to a 3d point
		\param factor const reference to a factor to divide with
		\returns new 3d point object
	*/
	template < class T > INLINE const TPoint3d<T> operator/( 
		const TPoint3d<T> &pt, const T factor )
	{
		return TPoint3d<T>( pt.x()/factor, pt.y()/factor,
									pt.z()/factor );
	}


//#############################################################################

	//!* operator
	/*!Scalar product of to 3d points.
		\param first const reference to a 3d point
		\param second const reference to a 3d point
		\returns scalar	
	*/
	template < class T > INLINE T operator*( 
		const TPoint3d<T> &first, const TPoint3d<T> &second )
	{
		return first.x()*second.x() + first.y()*second.y() +
												first.z()*second.z();
	}

//#############################################################################
	
	//!% operator
	/*!Cross (vector) product of to 3d points
		\param first const reference to a 3d point
		\param second const reference to a 3d point
		\returns 3d point
	*/
	template < class T > INLINE TPoint3d<T> operator%( 
		const TPoint3d<T> &first, const TPoint3d<T>  &second )
	{
		return TPoint3d<T> ( first.y()*second.z() - first.z()*second.y(),
						first.z()*second.x() - first.x()*second.z(),
					first.x()*second.y() - first.y()*second.x() );
	}



//#############################################################################

#endif //__TPoint3d_hpp__
