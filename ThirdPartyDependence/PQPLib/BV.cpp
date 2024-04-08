// Constructor for the BV class
BV::BV() : first_child(0) {}

// Destructor for the BV class
BV::~BV() {}

// Function for fitting a BV to a set of triangles in world coordinates
void BV::FitToTris(PQP_REAL O[3][3], PolygonalMesh *mesh, Tri* tris, int num_tris)

// Function for fitting a BV to a set of triangles in local coordinates
void BV::FitToTris(PQP_REAL O[3][3], Tri *tris, int num_tris)

// Function for testing overlap between two BVs
int BV_Overlap(PQP_REAL R[3][3], PQP_REAL T[3], BV *b1, BV *b2)

// Function for computing the distance between two BVs
#if PQP_BV_TYPE & RSS_TYPE
PQP_REAL BV_Distance(PQP_REAL R[3][3], PQP_REAL T[3], BV *b1, BV *b2)
#endif

// Function for computing the distance between a point and a BV
#if PQP_BV_TYPE & RSS_TYPE
PQP_REAL Point_BV_Distance(PQP_REAL R[3][3], PQP_REAL T[3], BV *b, PQP_REAL p[3])
#endif
