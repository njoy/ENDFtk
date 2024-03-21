/**
 *  @class
 *  @brief The energy dependent scattering radius covariances
 *
 *  See ENDF102, section 32.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ScatteringRadiusCovariances {

  /* fields */
  std::vector< ExplicitCovariance > ni_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/32/151/ScatteringRadiusCovariances/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of NI-type data blocks
   */
  int NI() const { return this->ni_.size(); }

  /**
   *  @brief Return the number of NI-type data blocks
   */
  int numberDataBlocks() const { return this->NI(); }

  /**
   *  @brief Return the NI-type subsubsections
   */
  auto data() const {

    return ranges::cpp20::views::all( this->ni_ );
  }

  #include "ENDFtk/section/32/151/ScatteringRadiusCovariances/src/NC.hpp"
  #include "ENDFtk/section/32/151/ScatteringRadiusCovariances/src/print.hpp"
};
