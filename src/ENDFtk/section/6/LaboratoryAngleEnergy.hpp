class LaboratoryAngleEnergy :
  protected InterpolationSequenceRecord< EnergyOutgoingCosineDistribution > {

public:
  /* constructor */
  using InterpolationSequenceRecord::InterpolationSequenceRecord;

  /* get methods */
  long NR() const { return InterpolationSequenceRecord::tab2().NR(); }
  long NE() const { return InterpolationSequenceRecord::tab2().NZ(); }
  double energy() const { return InterpolationSequenceRecord::tab2().C2(); }

  auto energies() const { return InterpolationSequenceRecord::records(); }

  auto interpolants() const { return InterpolationSequenceRecord::tab2().interpolants(); }
  auto boundaries() const { return InterpolationSequenceRecord::tab2().boundaries(); }

  using InterpolationSequenceRecord::NC;
  using InterpolationSequenceRecord::print;
};
