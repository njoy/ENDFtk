class Tabulated : protected TabulationRecord {

public:
  /* constructor */
  using TabulationRecord::TabulationRecord;

  /* get methods */
  static constexpr int LNU(){ return 2; }
  using TabulationRecord::NP;
  using TabulationRecord::NR;
  auto energy() const { return TabulationRecord::x(); }
  auto nubar() const { return TabulationRecord::y(); }
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};

