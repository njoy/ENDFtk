class RMatrixLimited : public Base {
public:
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/SpinGroup.hpp"

  int IFG;
  int KRM;
  int KRL;

  std::optional<LIST> gammaPlusCompoundNucleus;

  std::vector< SpinGroup > spinGroups;

  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/src/ctor.hpp"
};
