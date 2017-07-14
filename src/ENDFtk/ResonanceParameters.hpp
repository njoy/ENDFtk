namespace ResonanceParameters {

#include "ENDFtk/ResonanceParameters/Base.hpp"
#include "ENDFtk/ResonanceParameters/SpecialCase.hpp"

namespace Resolved {
  #include "ENDFtk/ResonanceParameters/Resolved.hpp"
}

namespace Unresolved {}

using EnergyRange = std::variant< SpecialCase,
                                  Resolved::SLBW, 
                                  Resolved::MLBW, 
                                  Resolved::ReichMoore >;

#include "ENDFtk/ResonanceParameters/Isotope.hpp"

}
