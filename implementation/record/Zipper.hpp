#include <utility>

struct ENDFtk::implementation::record::Zipper {

  /* helper structs */  
#include "ENDFtk/implementation/record/Zipper/ReadingPack.hpp"
#include "ENDFtk/implementation/record/Zipper/Zipped.hpp"
    
  /* convenience aliases */
  using tail =
    ENDFtk::implementation::record::TailVerifying
    < ENDFtk::implementation::record::MAT,
      ENDFtk::implementation::record::MF,
      ENDFtk::implementation::record::MT >;
  
  template< std::size_t index >
  using shouldContinueToRecurse =
    typename std::conditional< ( index != 0 ),
                               std::true_type, std::false_type >::type;

  /* helper methods */
#include "ENDFtk/implementation/record/Zipper/src/reserve.hpp"
#include "ENDFtk/implementation/record/Zipper/src/increment.hpp"
#include "ENDFtk/implementation/record/Zipper/src/makeIteratorTuple.hpp"
#include "ENDFtk/implementation/record/Zipper/src/verifyTail.hpp"
#include "ENDFtk/implementation/record/Zipper/src/process.hpp"
#include "ENDFtk/implementation/record/Zipper/src/expandReferencePack.hpp"
#include "ENDFtk/implementation/record/Zipper/src/readLine.hpp"
#include "ENDFtk/implementation/record/Zipper/src/readPartialLine.hpp"

  /* methods */
#include "ENDFtk/implementation/record/Zipper/src/unzip.hpp"
};
