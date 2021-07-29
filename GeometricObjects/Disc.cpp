#include "Disc.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"
#include <memory>

FaaRay::Disc::Disc(void)
    :   GeometricObject()
{
}

FaaRay::Disc::Disc(const GFA::Point3D& center, const GFA::Normal& normal)
    :   GeometricObject(),
        center_(center),
        normal_(normal)
{
}

FaaRay::Disc::~Disc()
{
}

void FaaRay::Disc::setCenter(const GFA::Scalar &x, const GFA::Scalar &y, const GFA::Scalar &z)
{
    center_.x = x;
    center_.y = y;
    center_.z = z;
}

void FaaRay::Disc::setNormal(const GFA::Scalar &x, const GFA::Scalar &y, const GFA::Scalar &z)
{
    normal_.x = x;
    normal_.y = y;
    normal_.z = z;
}

void FaaRay::Disc::setRadius(const GFA::Scalar &radius)
{
    radius_ = radius;
}

bool FaaRay::Disc::hit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin, GFA::Normal &srNormal) const
{
    GFA::Scalar t = (center_ - ttRef.rayOrigin) * normal_ / (ttRef.rayDirection * normal_);

	if (t <= GFA::EPSILON)
		return (false);

    GFA::Point3D localHitPoint = ttRef.rayOrigin + ttRef.rayDirection * t;
    if ( (localHitPoint - center_).length() > radius_ )
        return (false);

    tmin = t;
    srNormal      = normal_;

    return (true);
}

bool FaaRay::Disc::shadowHit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin) const
{
    GFA::Scalar t = (center_ - ttRef.sRayOrigin) * normal_ / (ttRef.sRayDirection * normal_);

	if (t <= GFA::EPSILON)
		return (false);

    GFA::Point3D localHitPoint = ttRef.sRayOrigin + ttRef.sRayDirection * t;
    if ( (localHitPoint - center_).length() > radius_ )
        return (false);

    tmin = t;

    return (true);
}

FaaRay::DiscSPtr FaaRay::MakeDiscSPtr()
{
    return std::make_shared<FaaRay::Disc>();
}

