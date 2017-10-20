namespace nubar {

#include "ENDFtk/nubar/Polynomial.hpp"
#include "ENDFtk/nubar/Tabulated.hpp"

using NubarData = std::variant< // LNU=1
                                Polynomial,
                                // LNU=2
                                Tabulated >;
}
