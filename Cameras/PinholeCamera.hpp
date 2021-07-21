#ifndef __FAARAY_PINHOLECAMERA_H__
#define __FAARAY_PINHOLECAMERA_H__

#include "Camera.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"
#include <memory>

namespace FaaRay {

class PinholeCamera : public Camera
{
public:
    PinholeCamera();
    virtual ~PinholeCamera();

    void setViewPlaneDistance(const GFA::Scalar &viewPlaneDistance);
    void setZoom(const GFA::Scalar &zoom);
    
    void setRayDirection(FaaRay::TraceThread &ttRef) const;

    virtual void render(FaaRay::TraceThread &ttRef) const;
 
private:
    GFA::Scalar viewPlaneDistance_;
    GFA::Scalar zoom_;
};

typedef std::shared_ptr<PinholeCamera> PinholeCameraSPtr;
PinholeCameraSPtr MakePinholeCameraSPtr();

}

#endif

