OpenSolid is a free, open source (LGPL) C++ library for the representation and manipulation of geometric objects such as points, bounding boxes, triangles, axes, planes, curves, surfaces, and volumes. Key features include:

- Modern object-oriented design
- Clean, readable syntax using value semantics
- Axes, planes, coordinate systems
- Line segments, triangles, tetrahedra
- Robust [transformation](https://bitbucket.org/ianmackenzie/opensolid/wiki/Transformation) system for translating, rotating, mirroring and projecting objects
- Full support for arbitrary parametric functions (not just NURBS) for definining curves, surfaces and volumes
- Pervasive use of [bounding boxes](https://bitbucket.org/ianmackenzie/opensolid/wiki/Bounding%20boxes) for robust and efficient algorithms
- `SpatialSet` class for efficient spatial searching

Many more features are planned; for more details, see the [roadmap](https://bitbucket.org/ianmackenzie/opensolid/wiki/Roadmap).

# Building

OpenSolid can be built on Linux, Windows and Mac OS X using CMake; see the [Building OpenSolid](https://bitbucket.org/ianmackenzie/opensolid/wiki/Building%20OpenSolid) page for details.

# Development

Interested in helping with OpenSolid development? Great! Once you have successfully [built](https://bitbucket.org/ianmackenzie/opensolid/wiki/Building%20OpenSolid) OpenSolid, check out the [OpenSolid Style Guide](https://bitbucket.org/ianmackenzie/opensolid/wiki/OpenSolid%20Style%20Guide) for examples of indentation, naming, file/directory layout etc.

# Examples

    ::::c++
    // Intervals and floating-point values
    Interval a = Interval(2, 4);
    Interval b = Interval(3, 5);
    Interval c = a.intersection(b); // [3,4]
    assert(c.lowerBound() - 3 == Zero()); // Tolerant comparison
    assert(c.width() - 1 == Zero());
    Interval d = a.hull(b); // [2,5]
    assert(d.width() - 3 == Zero());
    assert(d.contains(a));
    assert(!d.strictlyContains(a));

    // Points and boxes
    Point3d p1(1, 5, 3);
    Box3d box = p1.hull(Point3d(4, 2, 6));
    Point3d p2 = p1 + Vector3d(10, 0, 0);

    // Axes, planes, coordinate systems
    Frame3d global;
    Axis3d zAxis = global.zAxis();
    Plane3d plane = global.xyPlane().offsetBy(5);

    // Transformations
    Point3d originalPoint(1.0, 2.0, 3.0);
    Point3d newPoint = point.rotatedAbout(zAxis, M_PI / 4).translatedBy(Vector3d(20, 0, 0));

    // Line segments, triangles
    LineSegment3d lineSegment(Point3d(1, 2, 3), Point3d(4, 5, 6));
    assert((lineSegment.vector() - Vector3d(3, 3, 3)).isZero());
    assert(lineSegment.length() - 3 * sqrt(3) == Zero());
    Triangle3d triangle(Point3d::origin(), Point3d(1, 0, 0), Point3d(0, 1, 0));
    assert((triangle.centroid() - Point3d(1.0 / 3.0, 1.0 / 3.0, 0.0)).isZero());