class DiscretePhoton : protected TabulationRecord {

public:
  /* constructor */
  using TabulationRecord::TabulationRecord;

  /* get methods */
  using TabulationRecord::NP;
  using TabulationRecord::NR;
  double E() const { return TabulationRecord::C1(); }
  double index() const { return TabulationRecord::L1(); }
  auto time() const { return TabulationRecord::x(); }
  auto multiplicity() const { return TabulationRecord::y(); }
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};

