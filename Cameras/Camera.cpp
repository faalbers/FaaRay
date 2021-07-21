#include "Camera.hpp"
#include "GFA.hpp"

FaaRay::Camera::Camera()
{
    up_.y = 1.0; // set up vector
}

FaaRay::Camera::~Camera()
{
}

void FaaRay::Camera::setEye(const GFA::Point3D &eye)
{
    eye_ = eye;
}

const GFA::Point3D & FaaRay::Camera::getEye() const
{
    return eye_;
}

void FaaRay::Camera::setLookAt(const GFA::Point3D &lookAt)
{
    lookAt_ = lookAt;
}

void FaaRay::Camera::computeUVW()
{
    // take care of up and down singularities
    if ( eye_.x == lookAt_.x && eye_.z == lookAt_.z ) {
        if ( eye_.y > lookAt_.y ) {
            u_.x = 0.0; u_.y = 0.0; u_.z = 1.0; 
            v_.x = 1.0; v_.y = 0.0; v_.z = 0.0; 
            w_.x = 0.0; w_.y = 1.0; w_.z = 0.0; 
            return;
        } else if ( eye_.y < lookAt_.y ) {
            u_.x = 1.0; u_.y = 0.0; u_.z = 0.0; 
            v_.x = 0.0; v_.y = 0.0; v_.z = 1.0; 
            w_.x = 0.0; w_.y = -1.0; w_.z = 0.0; 
            return;
        }
    }

    w_ = eye_ - lookAt_;
    w_.normalize();
    u_ = up_ ^ w_;
    u_.normalize();
    v_ = w_ ^ u_;
}

