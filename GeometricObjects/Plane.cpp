#include "Plane.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"
#include <memory>

FaaRay::Plane::Plane(void)
    :   GeometricObject()
{
}

FaaRay::Plane::Plane(const GFA::Point3D& center, const GFA::Normal& normal)
    :   GeometricObject(),
        center_(center),
        normal_(normal)
{
}

FaaRay::Plane::~Plane()
{
}

void FaaRay::Plane::setCenter(const GFA::Scalar &x, const GFA::Scalar &y, const GFA::Scalar &z)
{
    center_.x = x;
    center_.y = y;
    center_.z = z;
}

void FaaRay::Plane::setNormal(const GFA::Scalar &x, const GFA::Scalar &y, const GFA::Scalar &z)
{
    normal_.x = x;
    normal_.y = y;
    normal_.z = z;
}

bool FaaRay::Plane::hit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin, GFA::Normal &srNormal) const
{
    GFA::Scalar t = (center_ - ttRef.rayOrigin) * normal_ / (ttRef.rayDirection * normal_);

    if (t > GFA::EPSILON) {
        tmin = t;
        srNormal = normal_;
        return true;
    }

    return false;
    /*
    // page 54
    GFA::Scalar t = (point - ray.origin) * normal / (ray.direction * normal);

    if (t > kEpsilon) {
        tmin = t;
        sr.normal           = normal;
        sr.localHitPoint    = ray.origin + ray.direction * t;
        sr.color            = color;
        return (true);
    }
    
    return (false);
    */

}

bool FaaRay::Plane::shadowHit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin) const
{
    GFA::Scalar t = (center_ - ttRef.sRayOrigin) * normal_ / (ttRef.sRayDirection * normal_);

    if (t > GFA::EPSILON) {
        tmin = t;
        return true;
    }

    return false;
    /*
    // page 54
    GFA::Scalar t = (point - ray.origin) * normal / (ray.direction * normal);

    if (t > kEpsilon) {
        tmin = t;
        return (true);
    }
    
    return (false);
    */
}

FaaRay::PlaneSPtr FaaRay::MakePlaneSPtr()
{
    return std::make_shared<FaaRay::Plane>();
}

