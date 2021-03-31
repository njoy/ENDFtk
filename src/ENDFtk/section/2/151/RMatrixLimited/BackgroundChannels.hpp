/**
 *  @class
 *  @brief Background R-matrix values for each channel in the spin group
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class BackgroundChannels {

  /* fields */
  std::vector< std::optional< BackgroundRMatrix > > channels_;

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
  auto NCH() const { return this->channels_.size(); }

  /**
   *  @brief Return the number of channels
   */
  auto numberChannels() const { return this->NCH(); }

  /**
   *  @brief Return the background R-matrix values for all channels
   */
  auto backgroundRMatrices() const {

    return ranges::view::all( this->channels_ );
  }

  /**
   *  @brief Return the number of channels with background R-matrix values
   */
  auto KBK() const {

    return ranges::count( this->backgroundRMatrices()
                              | ranges::view::transform(
                                    [] ( const auto& value )
                                       { return bool( value ); } ),
                          true );
  }

  /**
   *  @brief Return the number of channels with background R-matrix values
   */
  auto numberBackgroundChannels() const { return this->KBK(); }

  #include "ENDFtk/section/2/151/RMatrixLimited/BackgroundChannels/src/NC.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/BackgroundChannels/src/print.hpp"
};
