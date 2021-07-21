/**
 *  @class
 *  @brief NI-Type Sub-subsection
 *
 *  See ENDF102, section 33.2 for more information.
 */
class NIType : protected ListRecord {


public:

  /* constructor */
  #include "ENDFtk/section/33/NIType/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of pairs in the second array
   */
  int LT() { return ListRecord::L1(); }

  /**
   *  @brief Return the number of pairs in the second array
   */
  int numberSecondPairs() { return this->LT(); }

  /**
   *  @brief Return the procedure type
   */
  int LB() const { return this->L2(); }

  /**
   *  @brief Return the procedure type
   */
  int procedure() const { return this->LB(); }

  /**
   *  @brief Return the number of values in this component
   */
  long NT() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the total number of pairs
   */
  long NP() const { return ListRecord::N2(); }

  /**
   *  @brief Return the total number of pairs
   */
  long numberPairs() const { return this->NP(); }

  // add ranges magic for Ek, Fk, El, Fl

  using ListRecord::NC;
  using ListRecord::print;
};
