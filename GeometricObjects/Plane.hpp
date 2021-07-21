#ifndef __FAARAY_PLANE_H__
#define __FAARAY_PLANE_H__

#include "GeometricObject.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"
#include <memory>

namespace FaaRay {

class Plane : public GeometricObject
{
public:
    Plane(void);
    Plane(const GFA::Point3D& center, const GFA::Normal& normal);
    ~Plane();

    void setCenter(const GFA::Scalar &x, const GFA::Scalar &y, const GFA::Scalar &z);
    void setNormal(const GFA::Scalar &x, const GFA::Scalar &y, const GFA::Scalar &z);

    virtual bool hit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin, GFA::Normal &srNormal) const;
    virtual bool shadowHit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin) const;

private:
    GFA::Point3D    center_;    // point through which plane passes
    GFA::Normal     normal_;    // plane normal
};

typedef std::shared_ptr<Plane> PlaneSPtr;
PlaneSPtr MakePlaneSPtr();

}

#endif

