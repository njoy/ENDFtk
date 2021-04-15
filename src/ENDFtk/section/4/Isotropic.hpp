/**
 *  @class
 *  @brief The angular distributions are all isotropic
 *
 *  The Isotropic class is used to represent the case in which all angular
 *  distributions are isotropic.
 *
 *  This class contains no data. The methods defined for this class allow for it
 *  to function in a variant along with other angular distribution
 *  representation types.
 *
 *  See ENDF102, section 4.2.1 for more information.
 */
class Isotropic {

public:

  /**
   *  @brief Return the isotropic angular distribution flag
   */
  static constexpr bool LI() { return true; }

  /**
   *  @brief Return the isotropic angular distribution flag
   */
  bool isotropicAngularDistributions() const { return this->LI(); }

  /**
   *  @brief Return the angular distribution law
   */
  static constexpr int LTT() { return 0; }

  /**
   *  @brief Return the angular distribution law
   */
  static constexpr int LAW() { return Isotropic::LTT(); }

  /**
   *  @brief Return the number of lines for this ENDF component
   */
  static constexpr long NC() { return 0; }

  /**
   *  @brief Print this ENDF component
   */
  template< typename OutputIterator >
  void print( OutputIterator&, int, int, int ) const { return; }
};
