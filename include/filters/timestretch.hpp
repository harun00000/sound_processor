#include "ifilter.hpp"

/**
 * @brief Changes waveform duration.
 */
class TimeStretch : public IFilter{
private:
    double factor_;

public:
    /**
     * @brief Creates time stretch filter.
     * @param factor Duration factor.
     */
    explicit TimeStretch(double factor);

    /**
     * @brief Applies time stretch filter.
     * @param sound Waveform.
     */
    void apply(Waveform& sound) const override;
};