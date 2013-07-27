/**
 * @file common.cpp
 * @author Can Erdogan
 * @date July 25, 2013
 * @brief The main header file for common utilities
 */

#pragma once

#include <somatic.h>
#include <somatic/daemon.h>
#include <somatic.pb-c.h>
#include <somatic/motor.h>
#include <imud.h>
#include <filter.h>
#include <ach.h>

#include <iomanip>

#include <dynamics/SkeletonDynamics.h>
#include <kinematics/BodyNode.h>
#include <kinematics/Dof.h>
#include <math/UtilsRotation.h>

#include <Eigen/Dense>

using namespace Eigen;

namespace Krang {

/* ******************************************************************************************** */
// Useful math operations

/// Converts a 4x4 homogeneous transform to a 6D euler with the given order for RPY.
Eigen::VectorXd transformToEuler(const Eigen::MatrixXd &T, math::RotationOrder _order);

/// Converts a 6D euler to a 4x4 homogeneous transform with the given order for RPY.
Eigen::MatrixXd eulerToTransform(const Eigen::VectorXd &V, math::RotationOrder _order);

/* ******************************************************************************************** */
/// The indicator for the left or right side	
enum Side {
	LEFT = 0,
	RIGHT
};

/* ******************************************************************************************** */
// IDs for the dart kinematic structure

extern std::vector <int> left_arm_ids;			///< Ids for left arm 
extern std::vector <int> right_arm_ids;			///< Ids for right arm
extern std::vector <int> imuWaist_ids;			///< Ids for waist/imu

extern std::vector <int> dart_root_dof_ids;        ///< Ids for the root position/orientation dofs in DART

/* ******************************************************************************************** */
typedef Matrix<double, 6, 1> Vector6d;			///< A typedef for convenience to contain f/t values
typedef Matrix<double, 7, 1> Vector7d;			///< A typedef for convenience to contain joint values
typedef Matrix<double, 6, 6> Matrix6d;			///< A typedef for convenience to contain wrenches

/* ******************************************************************************************** */
// Useful macros

#define VELOCITY SOMATIC__MOTOR_PARAM__MOTOR_VELOCITY
#define POSITION SOMATIC__MOTOR_PARAM__MOTOR_POSITION
#define pv(a) std::cout << #a << ": " << fix((a).transpose()) << "\n" << std::endl
#define pc(a) std::cout << #a << ": " << (a) << "\n" << std::endl
#define pm(a) std::cout << #a << ":\n " << fix((a).matrix()) << "\n" << std::endl
#define pmr(a) std::cout << #a << ":\n " << fix((a)) << "\n" << std::endl
#define parm (cout << llwa.pos[0] << ", " << llwa.pos[1] << ", " << llwa.pos[2] << ", " << \
	llwa.pos[3] << ", " << llwa.pos[4] << ", " << llwa.pos[5] << ", " << llwa.pos[6] << endl);
#define darm (cout << "dq: "<<llwa.vel[0] << ", " <<llwa.vel[1] << ", " << llwa.vel[2] << ", " << \
	llwa.vel[3] << ", " << llwa.vel[4] << ", " << llwa.vel[5] << ", " << llwa.vel[6] << endl);
#define eig7(x) (Vector7d() << (x)[0], (x)[1], (x)[2], (x)[3], (x)[4], (x)[5], (x)[6]).finished()

/* ********************************************************************************************* */
// as above, but nicely formatted. Prints fixed-point, fixed-width,
// and fixed-precision for perfectly aligned columns and no exponents.
#define DISPLAY_VECTOR(VEC) \
	{std::cout << std::setw(25) << std::left << #VEC; \
	for(int i = 0; i < VEC.size(); i++) std::cout << std::fixed << std::setw(12) << VEC[i]; \
	std::cout << std::endl;}

#define DISPLAY_MATRIX(MAT) \
	{std::cout << std::setw(25) << std::left << #MAT << std::endl; \
	for(int r = 0; r < MAT.rows(); r++) {	  \
	std::cout << "    "; \
	for(int c = 0; c < MAT.cols(); c++) { \
	std::cout << std::fixed << std::setw(12) << MAT(r, c); } \
std::cout << std::endl; \
}	\
std::cout << std::endl; }



};	// end of namespace

