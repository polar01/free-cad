/***************************************************************************
 *   Copyright (c) J�rgen Riegel          (juergen.riegel@web.de) 2009     *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#ifndef _ProjectionAlgos_h_
#define _ProjectionAlgos_h_

#include <TopoDS_Shape.hxx>
#include <Base/Vector3D.h>
#include <string>

class BRepAdaptor_Curve;

namespace Drawing
{

/** Algo class for projecting shapes and creating SVG output of it
 */
class DrawingExport ProjectionAlgos
{
public:
    /// Constructor
    ProjectionAlgos(const TopoDS_Shape &Input,const Base::Vector3f &Dir);
    virtual ~ProjectionAlgos();

    void execute(void);
    static TopoDS_Shape invertY(const TopoDS_Shape&);

    std::string Edges2SVG(const TopoDS_Shape &);
    std::string Edges2DXF(const TopoDS_Shape &);//add by Dan Falck 2011/09/25 

    enum SvgExtractionType { 
        Plain = 0,
        WithHidden = 1,
        WithSmooth = 2
    };

    std::string getSVG(SvgExtractionType type, float scale);
    std::string getDXF(SvgExtractionType type, float scale);//add by Dan Falck 2011/09/25 


    const TopoDS_Shape &Input;
    const Base::Vector3f &Direction;

    TopoDS_Shape V ;// hard edge visibly
    TopoDS_Shape V1;// Smoth edges visibly
    TopoDS_Shape VN;// contour edges visibly
    TopoDS_Shape VO;// contours apparents visibly
    TopoDS_Shape VI;// isoparamtriques   visibly
    TopoDS_Shape H ;// hard edge       invisibly
    TopoDS_Shape H1;// Smoth edges  invisibly
    TopoDS_Shape HN;// contour edges invisibly
    TopoDS_Shape HO;// contours apparents invisibly
    TopoDS_Shape HI;// isoparamtriques   invisibly

private:
    void printCircle(const BRepAdaptor_Curve&, std::ostream&);
    void printEllipse(const BRepAdaptor_Curve&, int id, std::ostream&);
    void printBSpline(const BRepAdaptor_Curve&, int id, std::ostream&);
    void printGeneric(const BRepAdaptor_Curve&, int id, std::ostream&);
    // dxf output section - Dan Falck 2011/09/25  
    void printDxfHeader(std::ostream&);
    void printDxfCircle(const BRepAdaptor_Curve&, std::ostream&);
    void printDxfEllipse(const BRepAdaptor_Curve&, int id, std::ostream&);
    void printDxfBSpline(const BRepAdaptor_Curve&, int id, std::ostream&);
    void printDxfGeneric(const BRepAdaptor_Curve&, int id, std::ostream&);

};

} //namespace Drawing


#endif