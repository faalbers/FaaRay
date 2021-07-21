#ifndef __FAARAY_RENDERJOB_H__
#define __FAARAY_RENDERJOB_H__

#include "Base/Base.hpp"
#include "Scene/Scene.hpp"
#include "Scene/ViewPlane.hpp"
#include "Render/TraceThread.hpp"

namespace FaaRay {

class RenderJob : public FaaRay::Base
{
public:
    RenderJob();
    ~RenderJob();

    FaaRay::SceneSPtr      getSceneSPtr() const;
    FaaRay::ViewPlaneSPtr  getViewPlaneSPtr() const;

    void setViewPlaneSPtr(FaaRay::ViewPlaneSPtr viewPlaneSPtr);

    void setMultiThread();
    
    void render() const;

private:
    // NeedFix: create typedefs for these
    FaaRay::ViewPlaneSPtr   viewPlaneSPtr_;
    FaaRay::SceneSPtr       sceneSPtr_;
    bool            multiThread_;
    

    
    void renderOneThread_() const;
    void renderMultiThread_() const;
    void setupTraceThread_(FaaRay::TraceThreadSPtr ttRef) const;
};

typedef std::shared_ptr<RenderJob> RenderJobSPtr;
typedef std::shared_ptr<const RenderJob> ConstRenderJobSPtr;

}

#endif

