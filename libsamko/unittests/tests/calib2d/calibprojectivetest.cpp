#include <gtest/gtest.h>

#include <libsamko/calib2d/calibprojective.h>

#include <libsamko/serialization/memstorage.h>
#include <libsamko/serialization/jsonreader.h>
#include <libsamko/serialization/jsonwriter.h>

#include <opencv2/highgui/highgui.hpp>

#include <mocks/ui/mockuifactory.h>
#include <mocks/ui/mockuigriddetector.h>
#include "../common.h"

// Grid calibration - may be allowed after InputParameters test succeedes

#undef GENERATE_GRIDS

constexpr int IMAGE_WIDTH = 640;
constexpr int IMAGE_HEIGHT = 480;
constexpr int GRID_COLS = 10;
constexpr int GRID_ROWS = 6;
constexpr int SPACING_MM = 10;
constexpr int SPACING_PIXELS = 60;	///< important for generating only
constexpr int RADIUS = 15;			///< important for generating only

using namespace samko;
using namespace cv;

using ::testing::Return;
using ::testing::StrictMock;

/* HELPER METHODS */

Mat generatePreciseField() {
	Size imSize(IMAGE_WIDTH, IMAGE_HEIGHT);
	Mat image(imSize, CV_8U, Scalar(255) );
	Size targetSize(RADIUS, RADIUS);
	Scalar targetColor(0);

	for (int iRow = 1; iRow < GRID_ROWS+1; iRow++)
		for (int iCol = 1; iCol < GRID_COLS+1; iCol++) {
			Point pt(iCol * SPACING_PIXELS, iRow * SPACING_PIXELS);
			ellipse(image, pt, targetSize , 0., 360., 0., targetColor);
			floodFill(image, pt, targetColor );
		}
    return image;
}

void testPreciseGrid(CalibrationProjective2D calib) {
    const size_t PT_COUNT = 4;
    vector<Point2f> img(PT_COUNT), grid(PT_COUNT);
    img[0] = Point2f(SPACING_PIXELS, SPACING_PIXELS);
    img[1] = Point2f(SPACING_PIXELS * GRID_COLS, SPACING_PIXELS);
    img[2] = Point2f(SPACING_PIXELS, SPACING_PIXELS * GRID_ROWS);
    img[3] = Point2f(SPACING_PIXELS * GRID_COLS, SPACING_PIXELS * GRID_ROWS);

    grid[0] = Point2f(0.f, 0.f);
    grid[1] = Point2f(SPACING_MM * (GRID_COLS-1), 0.f);
    grid[2] = Point2f(0.f, SPACING_MM * (GRID_ROWS-1));
    grid[3] = Point2f(SPACING_MM * (GRID_COLS-1), SPACING_MM * (GRID_ROWS-1));

    auto tmp = calib.imageToGrid(img);
    for (size_t i = 0; i < PT_COUNT; ++i)
        ExpectPoints2fNear(tmp[i], grid[i], 9e-3);  // grid LCS starts at 0,0

    tmp = calib.gridToImage(tmp);
    for (size_t i = 0; i < PT_COUNT; ++i)
        ExpectPoints2fNear(tmp[i], img[i], 2e-5);
}

CalibrationProjective2D initPrecise() {
    CalibrationProjective2D calib(SPACING_MM, 2);
	Mat image = generatePreciseField();
	calib.compute(image, GRID_COLS, GRID_ROWS);
	return calib;
}

void testSerializers(Reader& reader, Writer& writer) {
    auto calib = initPrecise();
    // serialize it
    writer.write("Calib2d", calib);
    std::string data = writer.data();
    //printf("Data: %s", data.c_str());
    // deserialize it
    CalibrationProjective2D deserialized(0, 0);
    reader.parse(data);
    reader.readObject("Calib2d", deserialized);
    // test
    testPreciseGrid(deserialized);
}

/* TEST CASES */

TEST(CalibProjective2DTest, InputParameters) {
	ASSERT_LE(RADIUS, SPACING_PIXELS);
	ASSERT_GE(IMAGE_WIDTH, GRID_COLS*SPACING_PIXELS + RADIUS );
	ASSERT_GE(IMAGE_HEIGHT, GRID_ROWS*SPACING_PIXELS + RADIUS );
}

TEST(CalibProjective2DTest, PreciseGridCompute) {
	auto calib = initPrecise();
	vector<Point2f> imgcrds = calib.getGridImageCoords();
	EXPECT_EQ(GRID_COLS*GRID_ROWS, imgcrds.size());
	EXPECT_LT(imgcrds.front().x, imgcrds.back().x);
	EXPECT_LT(imgcrds.front().y, imgcrds.back().y);

	Point2f meanError = calib.getMeanReprojectionError();
	ExpectPoints2fNear(meanError, Point2f(0.f, 0.f), 2e-6);
    //imshow("Residuals", calib.getResidualsImage());
	//waitKey();
}

TEST(CalibProjective2DTest, PreciseGridTransform) {
    auto calib = initPrecise();
    Point2f ptStart (SPACING_PIXELS, SPACING_PIXELS);
    Point2f pt = calib.imageToGrid(ptStart);
    ExpectPoints2fNear(pt, Point2f(0.f, 0.f), 6e-3);  // grid LCS starts at 0,0

    pt = calib.gridToImage(pt);
    ExpectPoints2fNear(pt, ptStart, 2e-5);
}

TEST(CalibProjective2DTest, PreciseGridTransformCorners) {
    auto calib = initPrecise();
    testPreciseGrid(calib);
}

TEST(CalibProjective2DTest, UserInputRequired) {
    CalibrationProjective2D calib(SPACING_MM, 2);

    vector<Point2f> mockData{{ Point2f(50.f, 64.f), Point2f(596.f, 50.f), Point2f(62.f, 360.f) }};

    StrictMock<MockUIFactory> strictFactory;
    EXPECT_CALL(strictFactory, getGridDetectorProxy())
        .WillOnce(Return(strictFactory.mockDetector(GRID_COLS, GRID_ROWS, mockData)));

    Mat image = imread("data/calibFields/calib010.png");
	calib.compute(image, GRID_COLS, GRID_ROWS, &strictFactory);

    Point2f imgPt(177.f, 242.f),
            expectedGridPt(2*SPACING_MM, 3*SPACING_MM),
            gridPt = calib.imageToGrid(imgPt);

    ExpectPoints2fNear(gridPt, expectedGridPt, 0.6f);
    ExpectPoints2fNear(calib.gridToImage(gridPt), imgPt, 0.6f);
}

TEST(CalibProjective2DTest, Serialization) {
    samko::MemStorage storage;
    testSerializers(storage, storage);
}

TEST(CalibProjective2DTest, SerializationJson) {
    JsonReader reader;
    JsonWriter writer;
    testSerializers(reader, writer);
}
