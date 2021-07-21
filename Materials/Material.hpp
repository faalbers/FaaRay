#ifndef __FAARAY_MATERIAL_H__
#define __FAARAY_MATERIAL_H__

#include "Base/Base.hpp"
#include "GFA.hpp"

namespace FaaRay{

// forward decleration because TraceThread also Material
class TraceThread;

class Material : public FaaRay::Base
{
    public:
        Material();
        virtual ~Material();

        //virtual const GFA::RGBColor & getDiffuseCd() const { return color_; }
        virtual void shade(FaaRay::TraceThread &ttRef) const = 0;
        virtual void diffuse(FaaRay::TraceThread &ttRef) const = 0;

        //void setColor() { color_.r = 0.0;}
    
    protected:
        GFA::RGBColor color_;
};

typedef std::shared_ptr<Material>  MaterialSPtr;
typedef std::shared_ptr<const Material>  ConstMaterialSPtr;

}

#endif

