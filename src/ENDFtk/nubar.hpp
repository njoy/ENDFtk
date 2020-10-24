#ifndef NJOY_ENDFTK_NUBAR
#define NJOY_ENDFTK_NUBAR

// system includes
#include <variant>

// other includes
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/InterpolationRecord.hpp"
#include "range/v3/view/stride.hpp"
#include "range/v3/view/drop_exactly.hpp"

namespace njoy {
namespace ENDFtk {
namespace nubar {

#include "ENDFtk/nubar/Constant.hpp"
#include "ENDFtk/nubar/DecayConstant.hpp"
#include "ENDFtk/nubar/EnergyDependent.hpp"
#include "ENDFtk/nubar/Polynomial.hpp"
#include "ENDFtk/nubar/Tabulated.hpp"

using NubarData = std::variant< // LNU=1
                                Polynomial,
                                // LNU=2
                                Tabulated >;

using DecayConstantData = std::variant< // LDG=0
                                        Constant,
                                        // LDG=1
                                        EnergyDependent >;

#include "ENDFtk/nubar/src/readNubarData.hpp"
#include "ENDFtk/nubar/src/readDecayConstantData.hpp"

} // nubar namespace
} // ENDFtk namespace
} // njoy namespace

#endif
