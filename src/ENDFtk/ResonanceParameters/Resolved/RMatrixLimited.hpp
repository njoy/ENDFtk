class RMatrixLimited : public Base {
public:
  #include "ENDFtk/ResonanceParameters/Resolved/RMatrixLimited/SpinGroup.hpp"

  int IFG;
  int KRM;
  int KRL;

  std::optional<LIST> gammaPlusCompoundNucleus;

  std::vector< SpinGroup > spinGroups;

  #include "ENDFtk/ResonanceParameters/Resolved/RMatrixLimited/src/ctor.hpp"
};
