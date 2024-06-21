/**
 *  @class
 *  @brief Background R-matrix values for each channel in the spin group
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT BackgroundChannels {

public:

  /* type aliases */
  using OptionalBackgroundRMatrix = std::optional< BackgroundRMatrix >;

private:

  /* fields */
  std::vector< OptionalBackgroundRMatrix > channels_;

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/RMatrixLimited/BackgroundChannels/src/makeBackgroundMatrices.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/BackgroundChannels/src/readBackgroundMatrices.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/2/151/RMatrixLimited/BackgroundChannels/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number of channels
   */
  unsigned int NCH() const { return this->channels_.size(); }

  /**
   *  @brief Return the number of channels
   */
  unsigned int numberChannels() const { return this->NCH(); }

  /**
   *  @brief Return the background R-matrix values for all channels
   */
  auto backgroundRMatrices() const {

    using namespace njoy::tools;
    return this->channels_ | std20::views::all;
  }

  /**
   *  @brief Return the number of channels with background R-matrix values
   */
  unsigned int KBK() const {

    auto matrices = this->backgroundRMatrices();
    return std::count_if( matrices.begin(), matrices.end(),
                          [] ( auto&& matrix ) { return matrix.has_value(); } );
  }

  /**
   *  @brief Return the number of channels with background R-matrix values
   */
  unsigned int numberBackgroundChannels() const { return this->KBK(); }

  #include "ENDFtk/section/2/151/RMatrixLimited/BackgroundChannels/src/NC.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/BackgroundChannels/src/print.hpp"
};
