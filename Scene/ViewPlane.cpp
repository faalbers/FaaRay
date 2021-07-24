
#include "ViewPlane.hpp"
#include "GFA.hpp"
#include "Samplers/Sampler.hpp"
#include "Samplers/RegularSampler.hpp"
#include "Samplers/MultiJitteredSampler.hpp"

FaaRay::ViewPlane::ViewPlane()
    : samplerSPtr_(new FaaRay::RegularSampler)
    , frameBufferPtr_(new GFA::RGBColorBuffer)
    , pixelSize_(1.0)
{
    constructDebug("FaaRay::ViewPlane");
}

// NeedFix: Is this called at all ?S
FaaRay::ViewPlane::ViewPlane(const GFA::Size width, const GFA::Size height)
    : samplerSPtr_(new FaaRay::RegularSampler(1))
    , frameBufferPtr_(new GFA::RGBColorBuffer(width, height))
    , pixelSize_(10.0/256.0)
{
    constructDebug("FaaRay::ViewPlane");
}

FaaRay::ViewPlane::~ViewPlane(void)
{
    delete frameBufferPtr_;
    sPtrDebug("FaaRay::ViewPlane:samplerSPtr_", samplerSPtr_);
    deconstructDebug("FaaRay::ViewPlane");
}

const GFA::Size & FaaRay::ViewPlane::width() const
{
    return frameBufferPtr_->width();
}

const GFA::Size & FaaRay::ViewPlane::height() const
{
    return frameBufferPtr_->height();
}

const GFA::Scalar & FaaRay::ViewPlane::pixelSize() const
{
    return pixelSize_;
}

const GFA::Size & FaaRay::ViewPlane::numSamples() const
{
    return samplerSPtr_->numSamples();
}

// NeedFix: are we setting 2 buffers ??
void FaaRay::ViewPlane::setPixel(
    const GFA::Index &x, const GFA::Index &y,
    const GFA::RGBColor &col) const
{
    // NeedFix: frameBufferPtr does not do anything right now
    frameBufferPtr_->setPixel(x, y, col);
    setGUIPixel_(x, y, col);
}

GFA::RGBColor FaaRay::ViewPlane::getPixel(GFA::Index x, GFA::Index y)
{
    return frameBufferPtr_->getPixel(x, y);
}

void FaaRay::ViewPlane::setNumSamples(const GFA::Size &numSamples)
{
    if (samplerSPtr_->numSamples() == numSamples) return;

    if (numSamples > 1) samplerSPtr_ = FaaRay::MakeMultiJitteredSamplerSPtr(numSamples);
    else samplerSPtr_ = FaaRay::MakeRegularSamplerSPtr(numSamples);
}

const FaaRay::Sampler * FaaRay::ViewPlane::getSamplerPtr() const
{
    return samplerSPtr_.get();
}

// NeedFix: why to procs doing the same thing
FaaRay::SamplerSPtr FaaRay::ViewPlane::getSamplerSPtr() const
{
    return samplerSPtr_;
}

FaaRay::ConstSamplerSPtr FaaRay::ViewPlane::getConstSamplerSPtr() const
{
    return samplerSPtr_;
}

void FaaRay::ViewPlane::setGUIPixel_(const GFA::Index &, const GFA::Index &,
        const GFA::RGBColor &) const
{
}
