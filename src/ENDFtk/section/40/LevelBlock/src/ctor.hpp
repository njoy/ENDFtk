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

private:

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
