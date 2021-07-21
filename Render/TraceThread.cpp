#include "TraceThread.hpp"

#include <algorithm>

FaaRay::TraceThread::TraceThread()
    : srHitAnObject(false)
    , sRayInShadow(false)
    , testBit(false)
{
    constructDebug("TraceThread");
}

FaaRay::TraceThread::~TraceThread()
{
    deconstructDebug("TraceThread");
}

void FaaRay::TraceThread::render()
{
    sceneSPtr->getCameraSPtr()->render(*this);
    viewPlaneSPtr->setPixel(x, y, color);
}

void FaaRay::TraceThread::renderBlock()
{
    for ( GFA::Index i = blockStart; i <= blockEnd; i++ ) {
        initRandom(0);
        x = i % width;
        y = i / width;
        render();
    }
}

void FaaRay::TraceThread::initRandom(const uint32_t &s)
{
    seedValue_ = s;
    rng_.seed(seedValue_);
}

GFA::Scalar FaaRay::TraceThread::rand()
{
    return distribution(rng_);
}


