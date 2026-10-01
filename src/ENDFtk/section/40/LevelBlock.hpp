/**
 *  @class
 *  @brief A Level block (subsection) given in an MF40 covariance section
 *
 *  The LevelBlock class is used to represent a subsection in
 *  an ENDF MF40 section, which represents a covariance of radionuclide
 *  production cross sections (MT, XLFS) relative to another reaction
 *  (MF1/MT1/XLFS1).
 *
 *  See ENDF102, section 40.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT LevelBlock {

  /* fields */

  double qm_;
  double qi_;
  int izap_;
  int lfs_;
  std::vector< ReactionBlock > reactions_;

  /* constructor */

  template< typename Iterator >
  LevelBlock( ControlRecord&& cont,
              Iterator& begin,
              const Iterator& end,
              long& lineNumber,
              int MAT, int MF, int MT ) :
    LevelBlock( cont.C1(), cont.C2(), cont.L1(), cont.L2(),
                readSequence< ReactionBlock >(
                  begin, end, lineNumber,
                  MAT, MF, MT, cont.N2() ) ) {};

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] qm            the mass difference Q-value
   *  @param[in] qi            the reaction Q-value
   *  @param[in] izap          the product identifier (ZA)
   *  @param[in] lfs           the excited level of the product
   *  @param[in] reactions     the reaction blocks
   *
   */
  LevelBlock( double qm, double qi, int izap, int lfs,
              std::vector< ReactionBlock >&& reactions ) :
    qm_( qm ), qi_( qi ), izap_( izap ), lfs_( lfs ),
    reactions_( std::move( reactions ) ) {};

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] head         the head record of the section
   *  @param[in] it           the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   */
  template< typename Iterator >
  LevelBlock( Iterator& begin,
                 const Iterator& end,
                 long& lineNumber,
                 int MAT, int MF, int MT )
  try :
    LevelBlock(
      ControlRecord( begin, end, lineNumber, MAT, MF, MT ),
      begin, end, lineNumber, MAT, MF, MT ) {

  } catch( std::exception& e ) {

    Log::info( "Trouble while creating an MF34 ReactionBlock",
               MT, MAT );
    throw e;
  };

  /* methods */

  /**
   *  @brief Return the mass-difference Q-value
   */
  double QM() const { return this->qm_; }

  /**
   *  @brief Return the mass-difference Q-value
   */
  double massDifferenceQValue() const { return this->QM(); }

  /**
   *  @brief Return the reaction Q-value
   */
  double QI() const { return this->qi_; }

  /**
   *  @brief Return the reaction Q-value
   */
  double reactionQValue() const { return this->QI(); }

  /**
   *  @brief Return the product ZA identifier
   */
  int IZAP() const { return this->izap_; }

  /**
   *  @brief Return the product ZA identifier
   */
  int productIdentifier() const { return this->IZAP(); }

  /**
   *  @brief Return the level number of the product
   */
  int LFS() const { return this->lfs_; }

  /**
   *  @brief Return the level number of the product
   */
  int excitedLevel() const { return this->LFS(); }

  /**
   *  @brief Return the number of reaction blocks
   */
  int NL() const { return this->reactions_.size(); }

  /**
   *  @brief Return the number of reaction blocks
   */
  int numberReactions() const { return this->NL(); }

  /**
   *  @brief Return the reaction blocks
   */
  auto reactionBlocks() const {

    using namespace njoy::tools;
    return std20::views::all( this->reactions_ );
  }

  /**
   *  @brief Return the number of lines in this MF40 subsection
   */
  long NC() const {

    long result = 1;

    for ( const auto& block : this->reactions_ ) {
      result += block.NC();
    }

    return result;
  }

  /**
   *  @brief Print this MF40 component
   *
   *  @tparam OutputIterator   an output iterator
   *
   *  @param[in] it            the current position in the output
   *  @param[in] MAT           the MAT number
   *  @param[in] MF            the MF number
   *  @param[in] MT            the MT number
   */
  template< typename OutputIterator >
  void print( OutputIterator& it, int MAT, int MF, int MT ) const {

    // metadata
    ControlRecord( this->QM(), this->QI(), this->IZAP(), this->LFS(),
                   0, this->NL() ).print( it, MAT, MF, MT );

    for ( const auto& block : this->reactions_ ) {
      block.print( it, MAT, MF, MT );
    }
  }
};
