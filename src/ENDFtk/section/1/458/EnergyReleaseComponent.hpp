class EnergyReleaseComponent : protected TabulationRecord {

public:
  /* constructor */
  using TabulationRecord::TabulationRecord;

  /* get methods */
  using TabulationRecord::NP;
  using TabulationRecord::NR;
  int LDRV() const { return TabulationRecord::L1(); }
  int IFC() const { return TabulationRecord::L2(); }
  auto energy() const { return TabulationRecord::x(); }
  auto release() const { return TabulationRecord::y(); }
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};

