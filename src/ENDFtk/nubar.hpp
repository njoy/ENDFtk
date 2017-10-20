namespace nubar {

#include "ENDFtk/nubar/Constant.hpp"
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

}
