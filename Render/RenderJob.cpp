#include "RenderJob.hpp"
#include "GFA.hpp"
#include "Scene/Scene.hpp"
#include "Scene/ViewPlane.hpp"
#include "Render/TraceThread.hpp"
//#include <stdlib.h>
//#include <time.h>
#include <thread>

FaaRay::RenderJob::RenderJob()
    : viewPlaneSPtr_(nullptr)
    , sceneSPtr_(new FaaRay::Scene)
    , multiThread_(false)
{
    constructDebug("FaaRay::RenderJob");
}

FaaRay::RenderJob::~RenderJob()
{
    sPtrDebug("FaaRay::RenderJob:viewPlaneSPtr_", viewPlaneSPtr_);
    sPtrDebug("FaaRay::RenderJob:sceneSPtr_", sceneSPtr_);
    deconstructDebug("FaaRay::RenderJob");
}

FaaRay::SceneSPtr FaaRay::RenderJob::getSceneSPtr() const
{
    return sceneSPtr_;
}

FaaRay::ViewPlaneSPtr FaaRay::RenderJob::getViewPlaneSPtr() const
{
    return viewPlaneSPtr_;
}

void FaaRay::RenderJob::setViewPlaneSPtr(FaaRay::ViewPlaneSPtr viewPlaneSPtr)
{
    // NeedFix: make sure we need to reset first
    viewPlaneSPtr_.reset(); // delete managed object
    viewPlaneSPtr_ = viewPlaneSPtr;
}

void FaaRay::RenderJob::setMultiThread()
{
    multiThread_ = true;
}
  
void  FaaRay::RenderJob::render() const
{   
    if (multiThread_)
        renderMultiThread_();
    else
        renderOneThread_();
}

void FaaRay::RenderJob::setupTraceThread_(FaaRay::TraceThreadSPtr ttRef) const
{
    //NOTE: Should be shared pointers ?
    ttRef->viewPlaneSPtr = viewPlaneSPtr_;
    ttRef->sceneSPtr = sceneSPtr_;
    ttRef->samplerSPtr = ttRef->viewPlaneSPtr->getConstSamplerSPtr();
    ttRef->tracerSPtr = ttRef->sceneSPtr->getConstTracerSPtr();
    ttRef->ambientLightSPtr = ttRef->sceneSPtr->getConstAmbientLightSPtr();
    
    // NeedFix: All following could be added to a TraceThread init method
    
    // Optimization variables
    ttRef->width = ttRef->viewPlaneSPtr->width();
    ttRef->height = ttRef->viewPlaneSPtr->height();
    ttRef->halfWidth = ttRef->width * 0.5;
    ttRef->halfHeight = ttRef->height * 0.5;
    ttRef->pixelSize = ttRef->viewPlaneSPtr->pixelSize();
}

void FaaRay::RenderJob::renderOneThread_() const
{
    std::cout << "\n**** RenderJob:renderOneThread ****\n";
    //NOTE: Needs warning
    if (viewPlaneSPtr_.use_count() == 0 || sceneSPtr_.use_count() == 0) return;
    
    // setup render pixel that will be refferenced through the whole thread
    TraceThreadSPtr tt(new FaaRay::TraceThread);
    setupTraceThread_(tt);

    // Init random seed
    tt->initRandom(0);

    GFA::RGBColor pixcol;
    
    std::size_t max = tt->width * tt->height;
    for ( std::size_t i = 0; i < max; i++ ) {
        tt->x = i % tt->width;
        tt->y = i / tt->width;
        tt->render();
    }
}

void FaaRay::RenderJob::renderMultiThread_() const
{
    std::cout << "\n**** RenderJob:renderOneThread ****\n";
    
    //NOTE: Needs warning
    if (viewPlaneSPtr_.use_count() == 0 || sceneSPtr_.use_count() == 0) return;

    GFA::RGBColor pixcol;
    
    std::vector<std::thread*> tthreads;
    GFA::Index max = viewPlaneSPtr_->width() * viewPlaneSPtr_->height();
    GFA::Index coreBlockSize = max/std::thread::hardware_concurrency();
    for ( GFA::Index i = 0; i < max; i +=coreBlockSize ) {
        TraceThreadSPtr tt(new FaaRay::TraceThread);
        setupTraceThread_(tt);
        tt->blockStart = i;
        tt->blockEnd = i + coreBlockSize - 1;
        tthreads.push_back(new std::thread(&FaaRay::TraceThread::renderBlock, tt));
    }
    for (std::thread *tthread : tthreads ) tthread->join();
}
