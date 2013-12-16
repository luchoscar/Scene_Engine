/************************************************************
 * Holds matrix multiplication functions and matrix data	*
 ************************************************************/

#pragma once

class Matrix3D
{
private:
	float matrix[16];

public:
	Matrix3D(void) { memset(matrix, 0, sizeof(matrix)); }

	//Overload [] so it can be used like an array
	float& operator [] (int index) { return matrix[index]; }

	//Use Matrix like a function, but returns the actual matrix underneath
	float* operator () ()	{ return matrix; }

	static void MakeTranslateMatrix(float x, float y, float z, Matrix3D& m);
	static void MakeRotateMatrix(float angle, float ax, float ay, float az, Matrix3D& m);
	static void MakeScaleMatrix(float scaleX, float scaleY, float scaleZ, Matrix3D& m);
	
	static void Transform(float dst[4], Matrix3D& mat, const float vec[4]);
	static void MultMatrix(Matrix3D& dst, Matrix3D& src1, Matrix3D& src2);
	static void InvertMatrix(Matrix3D* out, Matrix3D* m);
	
	static void BuildPerspectiveMatrix(double fieldOfView, double aspectRatio, double zNear, double zFar, Matrix3D& m);
	static void BuildLookAtMatrix(double eyex, double eyey, double eyez, 
								  double centerx, double centery, double centerz,
								  double upx, double upy, double upz,
								  Matrix3D& m);

};