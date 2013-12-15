#pragma once
class Math3D
{
public:
	const double myPi;

	Math3D(void);
	~Math3D(void);

	void buildPerspectiveMatrix(double fieldOfView, double aspectRatio, double zNear, double zFar, float m[16]);
	void buildLookAtMatrix(double eyex, double eyey, double eyez, double centerx, double centery, double centerz, double upx, double upy, double upz, float m[16]);
	void makeRotateMatrix(float angle, float ax, float ay, float az, float m[16]);
	void makeTranslateMatrix(float x, float y, float z, float m[16]);
	void makeScaleMatrix(float x, float y, float z, float m[16]);
	void multMatrix(float dst[16], const float src1[16], const float src2[16]);
};


