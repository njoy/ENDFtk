class Multiplicity : protected TabulationRecord {

public:
  /* constructor */
  using TabulationRecord::TabulationRecord;

  /* get methods */
  using TabulationRecord::NP;
  using TabulationRecord::NR;
  double ZAP() const { return TabulationRecord::C1(); }
  double AWP() const { return TabulationRecord::C2(); }
  int LIP() const { return TabulationRecord::L1(); }
  int LAW() const { return TabulationRecord::L2(); }
  auto energy() const { return TabulationRecord::x(); }
  auto multiplicity() const { return TabulationRecord::y(); }
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
