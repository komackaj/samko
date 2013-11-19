#include <libsamko/calib2d/coordhomog.h>
#include <numeric>
#include <stdexcept>
#include <algorithm>
#include <libsamko/cvutils.h>

#include <iostream>

using namespace std;
using namespace cv;

namespace samko {

/* ScaleComp */
SumDist::SumDist(Point2f from) : From(from) {
}

float SumDist::operator()(float soFar, Point2f pt) {
	return soFar + CvUtils::PointDist(From, pt);
}

/* CoordHomogenization */
CoordHomogenization::CoordHomogenization(void) : Mean(-1.0f, -1.0f), Scale(0.0) {
}

void CoordHomogenization::compute(vector<Point2f> points) {
	if (points.empty())
		throw std::runtime_error("CoordHomogenization::compute - empty dataset");

	Mean = std::accumulate(points.begin(), points.end(), Point2f(0.0f, 0.0f) );
	Mean *= 1.0 / points.size();

	SumDist sumDist(Mean);
	Scale = std::accumulate(points.begin(), points.end(), 0.0f, sumDist ) / points.size();
}

float CoordHomogenization::getScale() const {
	return Scale;
}

Point2f CoordHomogenization::homogenize(const Point2f& pt) const {
	if (Scale == 0)
		throw std::logic_error("CoordHomogenization::homogenize - not initialized");

	return (pt - Mean) * (1/Scale);
}

Point2f CoordHomogenization::unhomogenize(const Point2f& pt) const {
	if (Scale == 0)
		throw std::logic_error("CoordHomogenization::homogenize - not initialized");

	return pt*Scale + Mean;
}

vector<Point2f> CoordHomogenization::homogenize(const vector<Point2f>& pts) const {
    vector<Point2f> retval(pts.size());
    std::transform(begin(pts), end(pts), begin(retval), [this](const Point2f& _){return homogenize(_);} );
    return retval;
}

vector<Point2f> CoordHomogenization::unhomogenize(const vector<Point2f>& pts) const {
	vector<Point2f> retval(pts.size());
    std::transform(begin(pts), end(pts), begin(retval), [this](const Point2f& _){return unhomogenize(_);} );
    return retval;
}

float CoordHomogenization::distToMean(Point2f pt) {
	return CvUtils::PointDist(pt, Mean);
}

void CoordHomogenization::readFrom(Reader *reader) {
    Mean.x = reader->readFloat("meanX");
    Mean.y = reader->readFloat("meanY");
    Scale = reader->readFloat("scale");
}

void CoordHomogenization::writeTo(Writer *writer) const {
    writer->writeFloat("meanX", Mean.x);
    writer->writeFloat("meanY", Mean.y);
    writer->writeFloat("scale", Scale);
}

} //namespace samko