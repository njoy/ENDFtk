class NBodyPhaseSpace : protected ControlRecord {

public:
  /* constructor */
  using ControlRecord::ControlRecord;

  /* get methods */
  static constexpr int LAW() { return 6; }
  double APSX() const { return ControlRecord::C1(); }
  int NPSX() const { return ControlRecord::N2(); }
  using ControlRecord::NC;
  using ControlRecord::print;
};
