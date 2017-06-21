namespace ResonanceParameters {

namespace Resolved {
  #include "ENDFtk/ResonanceParameters/Resolved.hpp"
}

namespace Unresolved {
//#include "ENDFtk/ResonanceParameters/Unresolved.hpp"
}

using Range = std::variant< Resolved::SLBW, 
                               Resolved::MLBW, 
                               Resolved::ReichMoore >;
}
