class EnergyOutgoingCosineDistribution :
  protected InterpolationSequenceRecord< CosineOutgoingEnergyDistribution > {

public:
  /* constructor */
  #include "ENDFtk/section/6/LaboratoryAngleEnergy/EnergyOutgoingCosineDistribution/src/ctor.hpp"

  /* get methods */
  long NRM() const { return InterpolationSequenceRecord::tab2().NR(); }
  long NMU() const { return InterpolationSequenceRecord::tab2().NZ(); }
  double energy() const { return InterpolationSequenceRecord::tab2().C2(); }

  auto cosines() const { return InterpolationSequenceRecord::records(); }

  auto interpolants() const { return InterpolationSequenceRecord::tab2().interpolants(); }
  auto boundaries() const { return InterpolationSequenceRecord::tab2().boundaries(); }
  
  using InterpolationSequenceRecord::NC;
  using InterpolationSequenceRecord::print;
};
