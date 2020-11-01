/**
 *  @class
 *  @brief The distribution is unknown and no data is given
 *
 *  See ENDF102, section 6.2.1 for more information.
 */
class Unknown : protected NoLawDataGiven {

public:

  /* methods */

  /**
   *  @brief Return the distribution type (the LAW flag)
   */
  static constexpr int LAW() { return 0; }

  using NoLawDataGiven::NC;
  using NoLawDataGiven::print;
};
