// This is a really bad name for this class, but it is the name used in the ENDF
// manual.
class Isotope {
public:

  double ZAI;
  double abundance;
  std::vector< Range > ranges;

  #include "ENDFtk/ResonanceParameters/Isotope/src/ctor.hpp"
  #include "ENDFtk/ResonanceParameters/Isotope/src/resolvedRange.hpp"
};
