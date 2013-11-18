#include <libsamko/calib2d/calibprojective.h>

#include <limits>
#include <stdexcept>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <libsamko/ui/uifactory.h>
#include <libsamko/ui/uigriddetector.h>

#include <libsamko/cvutils.h>

using namespace std;
using namespace cv;

namespace samko {

CalibrationProjective2D::CalibrationProjective2D(float gridCentersDist, double ransacReprojThreshold)
	: GridCentersDist(gridCentersDist)
	, RansacReprojThreshold(ransacReprojThreshold)
	, MeanReprojError(-1.0f, -1.0f)
{}

void CalibrationProjective2D::detectGrid(Mat image, unsigned int colCount, unsigned int rowCount, const UIFactory *factory) {
	GridSize = Size(colCount, rowCount);

	GridCoords = generateGridCoords(GridSize, GridCentersDist);
	const size_t expectedSize = colCount*rowCount;

	if ( !findCirclesGrid( image, GridSize, ImageCoords, CALIB_CB_SYMMETRIC_GRID + CALIB_CB_CLUSTERING) ||
		  ImageCoords.size() != expectedSize )	{

        if (factory){
            auto gridDetector = factory->getGridDetector();
            if(gridDetector)
                ImageCoords = gridDetector->getGrid(colCount, rowCount);
            else
                throw std::runtime_error("CalibrationProjective2D::detectGrid - given factory does not support GridDetector");
        }else{
            throw std::runtime_error("CalibrationProjective2D::detectGrid failed");
        }
	}

	/// may be returned from bottomright to topleft, so check and reverse
	Point2f front = ImageCoords.front(),
			back = ImageCoords.back();
	if ((front.x > back.x) && (front.y > back.y))
		std::reverse(ImageCoords.begin(), ImageCoords.end());
}

void CalibrationProjective2D::compute(Mat image, unsigned int colCount, unsigned int rowCount, const UIFactory *factory) {
	/// init grid / image coordinates of calibration grid
	detectGrid(image, colCount, rowCount, factory);

	/// homogenize
	HomogImage.compute(ImageCoords);
	HomogGrid.compute(GridCoords);
	vector<Point2f> img = HomogImage.homogenize(ImageCoords);
	vector<Point2f> grid = HomogGrid.homogenize(GridCoords);

	/// compute homography from homogenized coordinates
	vector<uchar> inliers;
	H = findHomography(img, grid, CV_RANSAC, RansacReprojThreshold / HomogImage.getScale(), inliers );
	if ( H.empty() )
		throw std::runtime_error("CalibrationProjective2D::compute - cannot find homography using RANSAC");

    HInv =  H.inv();

	/// compute reprojection errors
	vector<Point2f> reprojectedCenters(ImageCoords.size());
	Residuals.resize(ImageCoords.size());

	perspectiveTransform(img, reprojectedCenters, H);
	reprojectedCenters = HomogGrid.unhomogenize(reprojectedCenters);
	subtract(reprojectedCenters, GridCoords, Residuals);
	ResidualsImage = buildResidualsImage(image, inliers);
}

Point2f CalibrationProjective2D::imageToGrid(const Point2f& imgPt) const {
    vector<Point2f> in(1), out(1);
    in[0] = HomogImage.homogenize(imgPt);
	perspectiveTransform(in, out, H);
	return HomogGrid.unhomogenize(out[0]);
}

vector<Point2f> CalibrationProjective2D::imageToGrid(const std::vector<cv::Point2f>& gridPts) const {
    vector<Point2f> out(gridPts.size());
    perspectiveTransform(HomogImage.homogenize(gridPts), out, H);
	return HomogGrid.unhomogenize(out);
}

Point2f CalibrationProjective2D::gridToImage(const Point2f& gridPt) const {
    vector<Point2f> in(1), out(1);
    in[0] = HomogGrid.homogenize(gridPt);
	perspectiveTransform(in, out, HInv);
	return HomogImage.unhomogenize(out[0]);
}

vector<Point2f> CalibrationProjective2D::gridToImage(const std::vector<cv::Point2f>& gridPts) const {
    vector<Point2f> out(gridPts.size());
    perspectiveTransform(HomogGrid.homogenize(gridPts), out, HInv);
	return HomogImage.unhomogenize(out);
}

vector<Point2f> CalibrationProjective2D::getGridImageCoords() const {
	return ImageCoords;
}

vector<Point2f> CalibrationProjective2D::getGridImageErrors() const {
    return Residuals;
}

Point2f CalibrationProjective2D::getMeanReprojectionError() {
	if (MeanReprojError.x < 0 && !Residuals.empty() )
	{
	    if (Residuals.empty())
            throw std::logic_error("CalibrationProjective2D - not initialized in getMeanReprojectionError");

		Point2f stdev = std::accumulate(
                            begin(Residuals), end(Residuals), Point2f(0.0, 0.0),
                            [](const Point2f& soFar, const Point2f& added) {
                                return soFar + Point2f(added.x * added.x, added.y * added.y);
                        } );
        stdev *= 1.f / Residuals.size();
		MeanReprojError = Point2f(sqrt(stdev.x), sqrt(stdev.y));
	}

	return MeanReprojError;
}

Mat	CalibrationProjective2D::getResidualsImage() const {
	return ResidualsImage;
}

vector<Point2f> CalibrationProjective2D::generateGridCoords(Size gridSize, float gridCentersDist) {
	vector<Point2f> grid(gridSize.area());
	vector<Point2f>::iterator akt = grid.begin();
    for (int row = 0; row < gridSize.height; ++row)
        for (int col = 0; col < gridSize.width; ++col, ++akt)
			*akt = Point2f(gridCentersDist*col, gridCentersDist*row);
    return grid;
}

cv::Mat CalibrationProjective2D::buildResidualsImage(Mat srcImage, vector<uchar> inliers) {
	const int   SCALE = 300;
	const float MIN_ERR = 1.f / SCALE;

    Mat ret(srcImage.size(), CV_8UC3);
    if (srcImage.channels() == 1)
        cvtColor(srcImage, ret, CV_GRAY2RGB);
    else
        ret = srcImage.clone();

    size_t id = 0;
	for (const Point2f &pt : ImageCoords)
	{
		Point2f errors = Residuals[id];
		int thickness = 3;
		Scalar color = Scalar(0,255,0);	//green

		if ( inliers[id++] )
            errors = SCALE * Point2d(std::max<float>(errors.x, MIN_ERR), std::max<float>(errors.y, MIN_ERR));
		else
			color = Scalar(0,0,255);	//red

		ellipse(ret, pt, Size((int)abs(errors.x), (int)abs(errors.y)), 0., 0., 360., color, thickness );
	}
	return ret;
}

} // namespace samko