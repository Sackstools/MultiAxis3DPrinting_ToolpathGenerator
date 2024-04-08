using namespace Eigen;
using Eigen::placeholders::last;
VectorXd v(n);
v(seq(2, last - 2)).setOnes();
