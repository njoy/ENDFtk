namespace resonanceParameters {

#include "ENDFtk/resonanceParameters/Base.hpp"
#include "ENDFtk/resonanceParameters/SpecialCase.hpp"
#include "ENDFtk/resonanceParameters/resolved.hpp"
#include "ENDFtk/resonanceParameters/unresolved.hpp"

using EnergyRange = std::variant< SpecialCase,
                                  resolved::SLBW, 
                                  resolved::MLBW, 
                                  resolved::ReichMoore,
                                  unresolved::EnergyDependent>;

#include "ENDFtk/resonanceParameters/Isotope.hpp"

}
