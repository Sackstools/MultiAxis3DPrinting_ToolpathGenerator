Eigen::MatrixXd m = Eigen::MatrixXd::Random(3, 3); // generate a 3x3 random matrix
Eigen::VectorXd v = Eigen::VectorXd::Random(5); // generate a random vector of size 5

Eigen::Matrix3d m;
m.setRandom(); // set all coefficients of m to random values

Eigen::VectorXd v(10);
v.setRandom(10); // set all coefficients of v to random values

Eigen::MatrixXd m2(4, 4);
m2.setRandom(4, 4); // set all coefficients of m2 to random values
