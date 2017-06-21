#include "ENDFtk.hpp"

namespace njoy{
namespace ENDFtk{
namespace ResonanceParameters {

SpecialCase::SpecialCase(double EL, double EH, double SPI, double AP, int NLS ):
    lowerEnergyLimit( EL ),
    upperEnergyLimit( EH ),
    spin( SPI ),
    scatteringRadius( AP ),
    nlValues( NLS )
{ }

} // namspace ResonanceParameters
} // namespace ENDFtk
} // namespace njoy
