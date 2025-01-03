#include <helpers/math_operations.h>

Eigen::MatrixXd vectorToMatrix(const std::vector<float>& vector, int rows, int cols)
{
	Eigen::MatrixXd matrix(rows, cols);
	for (size_t i = 0; i < vector.size(); i += cols) {
		for (int j = 0; j < cols; j++) {
			matrix.row(i / cols)(j) = vector[i + j];
		}
	}
	return matrix;
}