namespace resonanceParameters {

#include "ENDFtk/resonanceParameters/Base.hpp"

#include "ENDFtk/resonanceParameters/src/readAPE.hpp"
#include "ENDFtk/resonanceParameters/src/read.hpp"
#include "ENDFtk/resonanceParameters/src/readLISTs.hpp"

#include "ENDFtk/resonanceParameters/SpecialCase.hpp"
#include "ENDFtk/resonanceParameters/resolved.hpp"
#include "ENDFtk/resonanceParameters/unresolved.hpp"

using EnergyRange = std::variant< // LRU=0
                                  SpecialCase,
                                  // LRU=1
                                  resolved::SLBW, 
                                  resolved::MLBW, 
                                  resolved::ReichMoore,
                                  // LRU=2
                                  unresolved::EnergyIndependent,
                                  unresolved::EnergyDependentFissionWidths,
                                  unresolved::EnergyDependent>;

#include "ENDFtk/resonanceParameters/Isotope.hpp"

}
