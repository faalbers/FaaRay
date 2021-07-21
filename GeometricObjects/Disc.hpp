#ifndef __FAARAY_DISC_H__
#define __FAARAY_DISC_H__

#include "GeometricObject.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"
#include <memory>

namespace FaaRay {

class Disc : public GeometricObject
{
public:
    Disc(void);
    Disc(const GFA::Point3D& center, const GFA::Normal& normal);
    ~Disc();

    void setCenter(const GFA::Scalar &x, const GFA::Scalar &y, const GFA::Scalar &z);
    void setNormal(const GFA::Scalar &x, const GFA::Scalar &y, const GFA::Scalar &z);
    void setRadius(const GFA::Scalar &radius);

    virtual bool hit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin, GFA::Normal &srNormal) const;
    virtual bool shadowHit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin) const;

private:
    GFA::Point3D    center_;    // point through which plane passes
    GFA::Normal     normal_;    // plane normal
    GFA::Scalar     radius_;     // sphere radius
};

typedef std::shared_ptr<Disc> DiscSPtr;
DiscSPtr MakeDiscSPtr();

}

#endif

