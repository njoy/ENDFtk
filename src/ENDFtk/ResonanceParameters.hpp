namespace resonanceParameters {

#include "ENDFtk/resonanceParameters/Base.hpp"
#include "ENDFtk/resonanceParameters/SpecialCase.hpp"
#include "ENDFtk/resonanceParameters/resolved.hpp"

namespace unresolved {}

using EnergyRange = std::variant< SpecialCase,
                                  resolved::SLBW, 
                                  resolved::MLBW, 
                                  resolved::ReichMoore >;

#include "ENDFtk/resonanceParameters/Isotope.hpp"

}
