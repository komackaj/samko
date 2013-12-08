#ifndef HEADER_E3B2F809C396CE9F
#define HEADER_E3B2F809C396CE9F

#pragma once
#include <vector>
#include <opencv2/core/core.hpp>

namespace samko {

/** Computing scale factor for homogenization from vector using std::accumulate
 *  @todo replace with c++11 lambda */
class SumDist {
	cv::Point2f From;

public:
	SumDist(cv::Point2f from);

	float operator() (float soFar, cv::Point2f pt);
};


/// Coordinates homogenization - after transform will have mean point value (0,0) and dist from mean will be sqrt(2)
class CoordHomogenization {

public:
	CoordHomogenization(void);

	/** computes homogenization parameters from set of points
	 *	@throws std::runtime error on failure */
	void compute(std::vector<cv::Point2f> points);

	float getScale() const;

	/**	Makes point homogenized
	 *	@param [in]     pt	unhomogenized point
	 *	@returns homogenized point */
	cv::Point2f homogenize(const cv::Point2f& pt) const;

	///	Homogenization of whole vector
	std::vector<cv::Point2f> homogenize(const std::vector<cv::Point2f>& pts) const;

	/**	Transforms homogenized point to unhomogenized
	 *	@param [in]     pt	homogenized point
	 *	@returns unhomogenized point */
	cv::Point2f unhomogenize(const cv::Point2f& pt) const;

	///	Unhomogenization of whole vector
	std::vector<cv::Point2f> unhomogenize(const std::vector<cv::Point2f>& pts) const;

private:

    cv::Point2f		Mean;		///< center of homogenization set
	float			Scale;		///< average distance for homogenization set

	float distToMean(cv::Point2f pt);
};

} //namespace samko

#endif // header guard
