#ifndef HEADER_7703ED1279D5F2C1
#define HEADER_7703ED1279D5F2C1

#pragma once
#include <opencv2/imgproc/imgproc.hpp>
#include <libsamko/calib2d/coordhomog.h>

namespace samko {

class UIFactory;

/// Computing 2D projective transformation from image coordinates to calibration grid local coordinate system (LCS)
/// @todo implement user input of grid corners (@see detectGrid)
/// @todo implement target refining
/// @todo implement Jung's transformation
/// @todo additional out-of-sample control points on grid to evaluate precision
/// @todo camera distorsion parameters computation
class CalibrationProjective2D {
public:

	/** standard constructor
	 *	@param gridCentersDist	- @see GridCentersDist member
	 *	@param ransacReprojThreshold - @see RansacReprojThreshold member */
	CalibrationProjective2D(float gridCentersDist, double ransacReprojThreshold);

	/** computes 2D projective transformation from calibration grid image
	 *  throws std::runtime_error on failure
	 *	@returns true on success, false on failure */
	void compute(cv::Mat image, unsigned int colCount, unsigned int rowCount, const UIFactory *factory = nullptr);

	/** transforms image point to grid coordinate system
	 *	@pre compute method succeeded
	 *	@param [in]    pt  point image coordinates
	 *	@returns point coordinates in calib grid coord system */
	cv::Point2f imageToGrid(const cv::Point2f& imgPt) const;

	/// whole vector transformation
	std::vector<cv::Point2f> imageToGrid(const std::vector<cv::Point2f>& imgPts) const;

	/** transforms point in grid coordinate system to image coordinates
	 *	@pre compute method succeeded
	 *	@param [in]	    pt  point coordinates in calib grid coord system
	 *	@returns point image coordinates */
	cv::Point2f gridToImage(const cv::Point2f& gridPt) const;

	/// whole vector transformation
	std::vector<cv::Point2f> gridToImage(const std::vector<cv::Point2f>& gridPts) const;

/// additional informations

	/**	Calibration grid image coordinates
	 * @pre compute method succeeded
	 * @returns image coordinates */
	std::vector<cv::Point2f> getGridImageCoords() const;

	/** Calibration grid reprojection errors (in same unit as gridCentersDist in constructor )
     * @pre compute method succeeded
     * @returns vector of errors */
	std::vector<cv::Point2f> getGridImageErrors() const;

	/** @returns stdev error
	 *  @pre compute method succeeded
	 *	@note non-const due to lazy initialization */
	cv::Point2f getMeanReprojectionError();

    /// @returns image with drawn error ellipses for every point of grid
    /// @throws std::logic_error on failure (object not initialized via successful call to compute)
	cv::Mat	getResidualsImage() const;

private:

	cv::Size					GridSize;		///< num of target per row/col
	float						GridCentersDist;///< distance between neighbourh targets in length units in grid LCS
	/// maximum reprojection error (in pixels) for inlier when computing homography using RANSAC
	double						RansacReprojThreshold;

	std::vector<cv::Point2f>	ImageCoords;	///< image coordinates of grid centers
	std::vector<cv::Point2f>	GridCoords;		///< coordinates of grid centers in grid LCS

	CoordHomogenization	        HomogImage,		///< homogenization for image coordinates
                                HomogGrid;		///< homogenization for grid LCS

	cv::Mat						H;				///< projective homography from image to grid LCS
	cv::Mat						HInv;			///< projective homography from grid LCS to image

	std::vector<cv::Point2f>	Residuals;		///< grid center reprojection errors in grid LCS
	cv::Point2f					MeanReprojError;///< stdev of Errors
	cv::Mat						ResidualsImage;	///< image of calibration grid with reprojection errors drawn

	/** Computes LCS coordinates for given size of calibration field grid with same span between points
	 * @note LCS origin is at [0.0, 0.0]
	 * @param[in]   gridSize        number of cols and rows of calibration field
	 * @param[in]   gridCentersDist distance between neighbourh field points
	 * @returns     calibration field  points LCS coordinates */
	static std::vector<cv::Point2f> generateGridCoords(cv::Size gridSize, float gridCentersDist);

	/// initializes GridCoords and ImageCoords members
	///	@returns false on failure
	/// @todo  implement user input if automated detection fails
	void detectGrid(cv::Mat image, unsigned intcolCount, unsigned int rowCount, const UIFactory* factory = nullptr);

    /// Generates residuals image
    /// @returns residual image
	cv::Mat buildResidualsImage(cv::Mat srcImage, std::vector<uchar> inliers);
};

} // namespace samko

#endif // header guard
