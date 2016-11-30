struct Zipper {

  /* helper structs */  
#include "ENDFtk/record/Zipper/src/ReadingPack.hpp"
#include "ENDFtk/record/Zipper/src/Zipped.hpp"
    
  /* convenience aliases */
  using tail = ENDFtk::record::TailVerifying< ENDFtk::record::MAT,
                                              ENDFtk::record::MF,
                                              ENDFtk::record::MT >;
  
  template< std::size_t index >
  using shouldContinueToRecurse =
    std::conditional_t< ( index != 0 ), std::true_type, std::false_type >;

  /* helper methods */
#include "ENDFtk/record/Zipper/src/reserve.hpp"
#include "ENDFtk/record/Zipper/src/increment.hpp"
#include "ENDFtk/record/Zipper/src/makeIteratorTuple.hpp"
#include "ENDFtk/record/Zipper/src/verifyTail.hpp"
#include "ENDFtk/record/Zipper/src/process.hpp"
#include "ENDFtk/record/Zipper/src/expandReferencePack.hpp"
#include "ENDFtk/record/Zipper/src/readLine.hpp"
#include "ENDFtk/record/Zipper/src/readPartialLine.hpp"

  /* methods */
#include "ENDFtk/record/Zipper/src/unzip.hpp"
};
