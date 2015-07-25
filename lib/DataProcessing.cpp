


//static void ReadSTLBinary(misc::BinInputStream& l_strm, Mesh& mesh)
//{
//	try
//	{
//		//skip header
//#if defined (_WIN32)
//		const unsigned __int64 header_length = 80;
//#elif defined(linux)
//		const uint64_t header_length = 80;
//#endif
//
//		char header[header_length];
//#if defined (_WIN32)
//		unsigned __int64 size;
//#elif defined(linux)
//		uint64_t size;
//#endif
//
//		size = header_length;
//		l_strm.Read((void*)header, size);
//		int nTotalTriangles;
//
//		size = sizeof(nTotalTriangles);
//		l_strm.Read(&nTotalTriangles, size);
//
//		if (!nTotalTriangles)
//		{
//			throw STLParserException(STLParserException::INVALID_NUMBER_OF_TRIANGLES);
//		}
//
//		TriangleVector triangleVector;
//		triangleVector.Reserve(nTotalTriangles);
//		const size_t pointsBufferSize = 12;
//		float* points3dBuffer = new float[pointsBufferSize];
//		point3d normal;
//		point3d point1;
//		point3d point2;
//		point3d point3;
//		short dummyint = 0;
//		size = sizeof(dummyint);
//		for (int i = 0; i < nTotalTriangles; i++)
//		{
//			BufferedReadTriangle(l_strm, normal, point1, point2, point3, points3dBuffer);
//
//			l_strm.Read(&dummyint, size);
//
//			if (~(point1 - point2) < mathdef::_MATH_TOL &&
//				~(point3 - point2) < mathdef::_MATH_TOL)
//				continue;
//
//			triangleVector.AddTriangle(point1, point2, point3, normal);
//		}
//		delete[] points3dBuffer;
//		mesh.SetTriangles(triangleVector);
//	}
//	catch (misc::Exception& ex)
//	{
//		throw STLParserException(STLParserException::INVALID_FILE_FORMAT, &ex);
//	}
//}
//
////!BufferedReadTriangle
///*!Reads a triangle from an input binary .stl file
//\param strm reference to the input stream
//\param normal reference for the normal
//\param point1 reference to the triangle's first 3DPoint
//\param point2 reference to the triangle's second 3DPoint
//\param point3 reference to the triangle's third 3DPoint
//\param buffer the buffer that will be used for file reading
//*/
//static bool BufferedReadTriangle(misc::BinInputStream& strm,
//	point3d& normal, point3d& point1, point3d& point2, point3d& point3, float* buffer)
//{
//	const size_t nrOfPointsToBeReadInOneShot = 12;
//#if defined (_WIN32)
//	unsigned __int64 size = sizeof(float)* nrOfPointsToBeReadInOneShot;
//#elif defined(linux)
//	uint64_t size = sizeof(float)* nrOfPointsToBeReadInOneShot;
//#endif
//	strm.Read(buffer, size);
//	ReadPointFromBuffer(normal, buffer, 0);
//	ReadPointFromBuffer(point1, buffer, 3);
//	ReadPointFromBuffer(point2, buffer, 6);
//	ReadPointFromBuffer(point3, buffer, 9);
//	return true;
//}
//
////!ReadPointFromBuffer
///*!Utility method, reads a point from a given buffer, using data starting at
//extractionStartPosition
//\param point reference to the input stream
//\param buffer the input buffer
//\param extractionStartPosition the position at which extraction will commence
//*/
//static bool ReadPointFromBuffer(
//	point3d& point, float* buffer, const size_t& extractionStartPosition)
//{
//	point.x(buffer[extractionStartPosition]);
//	point.y(buffer[extractionStartPosition + 1]);
//	point.z(buffer[extractionStartPosition + 2]);
//	return true;
//}



//#include <sstream>
//#include <string>
//
//std::string line;
//while (std::getline(infile, line))
//{
//	std::istringstream iss(line);
//	int a, b;
//	if (!(iss >> a >> b)) { break; } // error
//
//	// process pair (a,b)
//}

