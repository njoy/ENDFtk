class Unknown : protected NoLawDataGiven {

public:

  /* get methods */
  static constexpr int LAW() { return 0; }

  using NoLawDataGiven::NC;
  using NoLawDataGiven::print;
};
