#ifndef NJOY_ENDFTK_GENDF_DATARECORD
#define NJOY_ENDFTK_GENDF_DATARECORD

// system includes

// other includes
#include "ENDFtk/ListRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace gendf {

  class DataRecord : protected ListRecord {

  public:

    /* ctor */

    // from parameters
    DataRecord( double temp, long ng2, long ig2lo, long ig,
                std::vector< double >&& list ) :
      ListRecord( temp, 0., ng2, ig2lo, ig,
                  std::move( list ) )
    {}

    // from buffer
    template< typename Iterator >
    DataRecord( Iterator& it, const Iterator& end, long& lineNumber,
                long MAT, long MF, long MT ) :
      ListRecord( it, end, lineNumber, MAT, MF, MT )
    {}

    /* getter methods */

    double TEMP() const { return this->C1(); }
    double temperature() const { return this->TEMP(); }

    long NG2() const { return this->L1(); }
    long numSecondaryPositions() const { return this->NG2(); }

    long IG2LO() const { return this->L2(); }
    long lowestPosition() const { return this->IG2LO(); }

    long NW() const { return this->NPL(); }
    long numWords() const { return this->NW(); }

    long IG() const { return this->N2(); }
    long groupIndex() const { return this->IG(); }

    using ListRecord::list;

  };

}
}
}

#endif
