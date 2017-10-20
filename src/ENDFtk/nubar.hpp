namespace nubar {

#include "ENDFtk/nubar/Polynomial.hpp"
#include "ENDFtk/nubar/Tabulated.hpp"

using Data = std::variant< // LNU=1
                           Polynomial,
                           // LNU=2
                           Tabulated >;
}
