#ifndef __FAARAY_GEOMETRICOBJECT_H__
#define __FAARAY_GEOMETRICOBJECT_H__

#include "Base/Base.hpp"
#include "GFA.hpp"
#include "Materials/Material.hpp"
#include <memory>

namespace FaaRay {

// forward decleration because TraceThread also includes GeometricObject through Scene
class TraceThread;

class GeometricObject : public FaaRay::Base
{
public:
    GeometricObject();      // default constructor
    virtual ~GeometricObject();     // destructor
    
    virtual bool hit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin, GFA::Normal &srNormal) const = 0;
    virtual bool shadowHit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin) const = 0;

    void setMaterialSPtr(FaaRay::ConstMaterialSPtr materialSPtr);
    FaaRay::ConstMaterialSPtr getMaterialSPtr() const;
    
protected:
    FaaRay::ConstMaterialSPtr  materialSPtr_;
};

typedef std::shared_ptr<GeometricObject> GeometricObjectSPtr;
typedef std::shared_ptr<const GeometricObject> ConstGeometricObjectSPtr;

}

#endif


