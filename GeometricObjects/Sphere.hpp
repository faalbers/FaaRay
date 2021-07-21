#ifndef __FAARAY_SPHERE_H__
#define __FAARAY_SPHERE_H__

#include "GeometricObject.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"
#include <memory>

namespace FaaRay {

class Sphere : public FaaRay::GeometricObject
{
public:
    Sphere();
    ~Sphere(void);     // destructor

    void setCenter(
        const GFA::Scalar &x,
        const GFA::Scalar &y,
        const GFA::Scalar &z);
    void setRadius(const GFA::Scalar &radius);

    virtual bool hit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin, GFA::Normal &srNormal) const;
    virtual bool shadowHit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin) const;

private:
    GFA::Point3D    center_;    // center point of the sphere
    GFA::Scalar     radius_;     // sphere radius
    GFA::Scalar     radiusQuad_; // quadratic sphere radius
};

typedef std::shared_ptr<Sphere> SphereSPtr;
SphereSPtr MakeSphereSPtr();

}

#endif


