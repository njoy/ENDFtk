namespace ResonanceParameters {

#include "ENDFtk/ResonanceParameters/SpecialCase.hpp"

namespace Resolved {
  #include "ENDFtk/ResonanceParameters/Resolved.hpp"
}

namespace Unresolved {
//#include "ENDFtk/ResonanceParameters/Unresolved.hpp"
}

using Range = std::variant< SpecialCase,
                            Resolved::SLBW, 
                            Resolved::MLBW, 
                            Resolved::ReichMoore >;

#include "ENDFtk/ResonanceParameters/Isotope.hpp"

}
