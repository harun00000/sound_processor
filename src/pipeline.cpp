#include "pipeline.hpp"

void Pipeline::addFilter(std::unique_ptr<IFilter> filter){
    filters_.push_back(std::move(filter));
}

void Pipeline::apply(Waveform& sound) const{
    for (const auto& filter : filters_)
    {
        filter->apply(sound);
    }
}