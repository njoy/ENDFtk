class DiscreteTwoBodyRecoils : protected NoLawDataGiven {

public:

  /* get methods */
  static constexpr int LAW() { return 4; }

  using NoLawDataGiven::NC;
  using NoLawDataGiven::print;
};
