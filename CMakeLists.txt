cmake_minimum_required(VERSION 3.2)

project(ShapeSharpening)

# Handle Qt stuff
#################
# CMAKE_PREFIX_PATH must be set to the Qt5 installation
set(CMAKE_PREFIX_PATH "C:/Qt5/5.5/msvc2013_64/" CACHE PATH "The path to the Qt5 installation directory")
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/ShapeSharpening)

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
 
# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt MOC file generation
########################
#set(QT_MOC_GENERATION_FILES
#	"${CMAKE_CURRENT_SOURCE_DIR}/app/scene.h"
#)
#QT5_WRAP_CPP(MOC_CPPS ${QT_MOC_GENERATION_FILES})

file(GLOB ALL_GUI "${CMAKE_CURRENT_SOURCE_DIR}/res/*.ui")
QT5_WRAP_UI(UI_CPPS ${ALL_GUI})

file(GLOB ALL_RES "${CMAKE_CURRENT_SOURCE_DIR}/res/*.qrc")
QT5_ADD_RESOURCES(RES_CPPS ${ALL_RES})

#set(ALL_QT_GENERATED_CODE ${MOC_CPPS} ${UI_CPPS} ${RES_CPPS})
set(ALL_QT_GENERATED_CODE ${UI_CPPS} ${RES_CPPS})

message(status "** Qt binary directory: ${_qt5Core_install_prefix}")

find_package(OpenGL)

#enable OpenMP
##############
find_package(OpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
##############
#end OpenMP

#Additional Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4267 /wd4804")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /bigobj")

set(BOOST_ROOT "C:/Program Files/boost_1_58_0" CACHE PATH "The path to the boost root directory")
find_package(Boost 1.58 REQUIRED)
message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
message(status "** Boost Libraries: ${Boost_LIBRARIES}")

# Putting it together
#####################
set(ALL_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIR})
include_directories(${ALL_INCLUDE_DIRECTORIES})

set(ALL_LIBDIRS ${Boost_LIBRARY_DIRS}
)
link_directories(${ALL_LIBDIRS})



# resource-files
file(GLOB ALL_HTMLS
	"${CMAKE_CURRENT_SOURCE_DIR}/res/*.vsh"
	"${CMAKE_CURRENT_SOURCE_DIR}/res/*.fsh"
	"${CMAKE_CURRENT_SOURCE_DIR}/res/*.jpg"
	"${CMAKE_CURRENT_SOURCE_DIR}/res/*.jpeg"
	"${CMAKE_CURRENT_SOURCE_DIR}/res/*.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/res/*.png"
)

# Intentionally left out *.cxx because those are moc generated.
file(GLOB_RECURSE ALL_SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.txx"
)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)
 


# Automatically create Filters (a.k.a Subdirectories) within Visual Studios Project View
# which reflect our projects folder structure (keeping it nice and clean)
# :: found on cmake mailinglist http://permalink.gmane.org/gmane.comp.programming.tools.cmake.user/10226 
IF( MSVC )
    FOREACH( pathSourceFile ${ALL_SRC} )
	
        GET_FILENAME_COMPONENT( pathSourceGroup ${pathSourceFile} PATH )
		
        IF( NOT ${pathSourceGroup} STREQUAL ${CMAKE_SOURCE_DIR} )
            # Make the path relative to the base source path
            STRING( REPLACE ${CMAKE_SOURCE_DIR} "" pathSourceGroup ${pathSourceGroup} )
   
            # Remove starting / and \
            STRING( SUBSTRING ${pathSourceGroup} 0 1 firstChar )
            IF( firstChar STREQUAL "/" OR
                firstChar STREQUAL "\\" )
                   
                STRING( LENGTH ${pathSourceGroup} strLen )
                MATH( EXPR strLen "${strLen} - 1" )
                STRING( SUBSTRING ${pathSourceGroup} 1 ${strLen}  pathSourceGroup )
            ENDIF()
           
            # Replace / with \ so the source groups work correctly in MSVC
            STRING( REPLACE "/" "\\" pathSourceGroup ${pathSourceGroup} )
           
            # Add file to the source group
            GET_FILENAME_COMPONENT( fileExtension ${pathSourceFile} EXT )
            IF( ${fileExtension} MATCHES ".c" OR
                ${fileExtension} MATCHES ".cpp" OR ${fileExtension} MATCHES ".txx")
                SOURCE_GROUP( "Source Files\\${pathSourceGroup}" FILES ${pathSourceFile} )
            ELSEIF( ${fileExtension} MATCHES ".h" OR
                    ${fileExtension} MATCHES ".hpp" )
                SOURCE_GROUP( "Header Files\\${pathSourceGroup}" FILES ${pathSourceFile} )
            ELSE()
                MESSAGE( SEND_ERROR "Source grouping failed on file ${pathSourceFile}" )
            ENDIF()
           
        ENDIF()
       
    ENDFOREACH()
ENDIF()



add_executable(ShapeSharpening ${ALL_SRC} ${ALL_QT_GENERATED_CODE})

qt5_use_modules(ShapeSharpening Widgets OpenGL)

set(ALL_LIBRARIES ${Boost_LIBRARIES} ${OPENGL_LIBRARIES})

target_link_libraries(ShapeSharpening ${ALL_LIBRARIES})

# Copying DLLs
##############
install(TARGETS ShapeSharpening DESTINATION bin)

install(FILES ${ALL_HTMLS} DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/d3dcompiler_47.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/libEGL.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/libEGLd.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/libGLESv2.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/libGLESv2d.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/opengl32sw.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/Qt5Core.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/Qt5Cored.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/Qt5Gui.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/Qt5Guid.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/Qt5OpenGL.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/Qt5OpenGLd.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/Qt5Widgets.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/Qt5Widgetsd.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/Qt53DCore.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/Qt53DCored.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/Qt53DRenderer.dll" DESTINATION bin)
install(FILES "${_qt5Core_install_prefix}/bin/Qt53DRendererd.dll" DESTINATION bin)

ADD_CUSTOM_TARGET(run)
ADD_CUSTOM_COMMAND(TARGET run POST_BUILD COMMAND ShapeSharpening.exe WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../install/bin/)
ADD_DEPENDENCIES(run ALL_BUILD INSTALL ShapeSharpening)

