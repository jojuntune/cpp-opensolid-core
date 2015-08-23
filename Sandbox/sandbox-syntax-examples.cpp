#include <OpenSolid/Core/Zero.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Triangle.hpp>
#include <OpenSolid/Core/Tetrahedron.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>

#include <vector>

using namespace opensolid;

void zeroExamples() {
    assert(1e-14 == Zero());
    assert(1e-3 > Zero());
    assert(1e-3 == Zero(1e-2));
    assert(std::atan(1.0) - M_PI / 4 == Zero());
}

void intervalExamples() {
    Interval a(2, 4);
    Interval b(3, 5);

    assert(a.width() - 2 == Zero());
    assert(a.overlaps(b));
    assert(!a.contains(b));

    Interval c = a * b;
    assert(c.lowerBound() - 6 == Zero());
    assert(c.upperBound() - 20 == Zero());
}

void vectorExamples() {
    Vector3d v1(1, 2, 3);
    Vector3d v2(4, 5, 6);

    assert(v1.dot(v2) - 32 == Zero());

    Vector3d v3 = v1.cross(v2);
    assert((v3 - Vector3d(-3, 6, -3)).isZero());

    Matrix3d m = Matrix3d::IDENTITY();
    assert((m * v1.components() - v1.components()).isZero());
    assert((m.inverse() - m).isZero());
}

void pointExamples() {
    Point3d p1(1, 1, 1);
    Point3d p2(2, 2, 2);

    Vector3d displacement = p2 - p1;
    assert((p1 + displacement - p2).isZero());

    Point3d scaled = p2.scaledAbout(p1, 2.0);
    assert((scaled - Point3d(3, 3, 3)).isZero());

    Point3d translated = p1.translatedBy(UnitVector3d::Y());
    assert((translated - Point3d(1, 2, 1)).isZero());
}

void boxExamples() {
    Box2d box = Point2d(1, 0).hull(Point2d(2, 1)).hull(Point2d(1, 2));

    Point2d minVertex = box.minVertex();
    assert((minVertex - Point2d(1, 0)).isZero());

    Point2d maxVertex = box.maxVertex();
    assert((maxVertex - Point2d(2, 2)).isZero());

    assert(box.contains(Point2d(2, 0)));
    assert(!box.contains(Point2d::ORIGIN()));

    for (int i = 0; i < 1000; ++i) {
        assert(box.contains(box.randomPoint()));
    }
}

void axisExamples() {
    Axis3d zAxis = Axis3d::Z();
    Point3d point(1, 2, 3);

    Point3d rotated = point.rotatedAbout(zAxis, M_PI / 2);
    assert((rotated - Point3d(-2, 1, 3)).isZero());

    Point3d translated = point.translatedAlong(zAxis, 5.0);
    assert((translated - Point3d(1, 2, 8)).isZero());
}

void planeExamples() {
    Plane3d plane(Point3d(1, 1, 1), UnitVector3d::X());

    Point3d mirrored = Point3d(2, 3, 4).mirroredAbout(plane);
    assert((mirrored - Point3d(0, 3, 4)).isZero());

    Point3d projected = Point3d(4, 5, 6).projectedOnto(plane);
    assert((projected - Point3d(1, 5, 6)).isZero());
}

void lineSegmentExamples() {
    LineSegment2d segment(Point2d(1, 1), Point2d(3, 4));
    
    double length = segment.length();
    assert(length - sqrt(13.0) == Zero());
    
    UnitVector2d normalVector = segment.normalVector();
    assert(normalVector.equals(Vector2d(-3, 2).normalized()));
    
    Axis2d axis = segment.axis();
    Point2d axisOrigin = axis.originPoint();
    UnitVector2d axisDirection = axis.directionVector();
    assert((axisOrigin - segment.startVertex()).isZero());
    assert(axisDirection.equals(segment.vector().normalized()));
}

void triangleExamples() {
    Point3d firstVertex(1, 1, 1);
    Point3d secondVertex(3, 1, 1);
    Point3d thirdVertex(1, 3, 1);
    Triangle3d triangle(firstVertex, secondVertex, thirdVertex);

    Point3d centroid = triangle.centroid();
    assert((centroid - Point3d(5.0 / 3.0, 5.0 / 3.0, 1)).isZero());

    UnitVector3d normalVector = triangle.normalVector();
    assert(normalVector.equals(UnitVector3d::Z()));

    double area = triangle.area();
    assert(area - 2.0 == Zero());

    double hypotenuseLength = triangle.edge(0).length();
    assert(hypotenuseLength - 2 * sqrt(2.0) == Zero());

    Point3d projectedOrigin = Point3d::ORIGIN().projectedOnto(triangle.plane());
    assert((projectedOrigin - Point3d(0, 0, 1)).isZero());
}

void tetrahedronExamples() {
    Tetrahedron3d unitTetrahedron = Tetrahedron3d::UNIT();

    Point3d firstVertex = unitTetrahedron.vertex(0);
    assert((firstVertex - Point3d::ORIGIN()).isZero());

    Point3d secondVertex = unitTetrahedron.vertex(1);
    assert((secondVertex - Point3d(1, 0, 0)).isZero());

    double volume = unitTetrahedron.volume();
    assert(volume - 1.0 / 6.0 == Zero());

    Point3d largeFaceCentroid = unitTetrahedron.face(0).centroid();
    Point3d expectedCentroid(1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0);
    assert((largeFaceCentroid - expectedCentroid).isZero());
}

void spatialSetExamples() {
    std::vector<Point2d> pointList(5);
    pointList[0] = Point2d::ORIGIN();
    pointList[1] = Point2d(1, 0);
    pointList[2] = Point2d(0, 1);
    pointList[3] = Point2d(2, 2);
    pointList[4] = Point2d(3, 0);

    SpatialSet<Point2d> set(pointList);
    Box2d queryBox(Interval(0, 2), Interval(1, 2));

    assert(set.overlapping(queryBox).size() == 2);
    assert(
        set.overlapping(queryBox).all(
            [&] (const Point2d& point) {
                return queryBox.contains(point);
            }
        )
    );
}

void parametricExpressionExamples() {
    Parameter1d t;

    ParametricExpression<Point3d, double> lineExpression =
        Point3d(1.0, 1.0, 1.0) + t * Vector3d(1.0, 1.0, 1.0);
    Point3d start = lineExpression.evaluate(0.0);
    Point3d mid = lineExpression.evaluate(0.5);
    Point3d end = lineExpression.evaluate(1.0);

    assert((start - Point3d(1.0, 1.0, 1.0)).isZero());
    assert((mid - Point3d(1.5, 1.5, 1.5)).isZero());
    assert((end - Point3d(2.0, 2.0, 2.0)).isZero());

    ParametricExpression<double, double> sineDerivative = sin(t).derivative();
    ParametricExpression<double, double> cosineExpression = cos(t);
    std::vector<double> parameterValues(10);
    for (unsigned i = 0; i < parameterValues.size(); ++i) {
        parameterValues[i] = i * 2 * M_PI / (parameterValues.size() - 1);
    }
    std::vector<double> sineDerivativeValues = sineDerivative.evaluate(parameterValues);
    std::vector<double> cosineValues = cosineExpression.evaluate(parameterValues);
    for (unsigned i = 0; i < parameterValues.size(); ++i) {
        assert(sineDerivativeValues[i] - cosineValues[i] == Zero());
    }

    ParametricExpression<double, double> shouldBeZero = sin(2.0 * t) - 2.0 * sin(t) * cos(t);
    std::vector<double> zeroValues = shouldBeZero.evaluate(parameterValues);
    for (unsigned i = 0; i < parameterValues.size(); ++i) {
        assert(zeroValues[i] == Zero());
    }
}

int main() {
    zeroExamples();
    intervalExamples();
    vectorExamples();
    pointExamples();
    boxExamples();
    axisExamples();
    planeExamples();
    lineSegmentExamples();
    triangleExamples();
    tetrahedronExamples();
    spatialSetExamples();
    parametricExpressionExamples();
    return 0;
}
