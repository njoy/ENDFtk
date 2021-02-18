#ifndef NJOY_ENDFTK_GENDF_DATARECORD
#define NJOY_ENDFTK_GENDF_DATARECORD

// system includes

// other includes
#include "ENDFtk/ListRecord.hpp"
#include "range/v3/view.hpp"

namespace njoy {
namespace ENDFtk {
namespace gendf {

  class DataRecord : protected ListRecord {

  public:

    /**
     *  @brief Constructor from parameters
     *
     *  @param[in] temp   the temperature
     *  @param[in] ng2    the number of secondary positions
     *  @param[in] ig2lo  the index to lowest position
     *  @param[in] ig     the group index
     *  @param[in] list   the data contained
     */
    DataRecord( double temp, long ng2, long ig2lo, long ig,
                std::vector< double >&& list ) :
      ListRecord( temp, 0., ng2, ig2lo, ig,
                  std::move( list ) ) {}

    /**
     *  @brief Constructor from buffer
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] it           the iterator for begin
     *  @param[in] end          the iterator for end
     *  @param[in] lineNumber   the line number
     *  @param[in] MAT          the expected material number
     *  @param[in] MF           the expected file number
     *  @param[in] MT           the expected section number
     */
    template< typename Iterator >
    DataRecord( Iterator& it, const Iterator& end, long& lineNumber,
                long MAT, long MF, long MT ) :
      ListRecord( it, end, lineNumber, MAT, MF, MT ) {}

    /* getter methods */

    /**
     *  @brief The temperature
     */
    double TEMP() const { return this->C1(); }

    /**
     *  @brief The temperature
     */
    double temperature() const { return this->TEMP(); }


    /**
     *  @brief The number of secondary positions
     */
    long NG2() const { return this->L1(); }

    /**
     *  @brief The number of secondary positions
     */
    long numSecondaryPositions() const { return this->NG2(); }

    /**
     *  @brief The index to the lowest position
     */
    long IG2LO() const { return this->L2(); }

    /**
     *  @brief The index to the lowest position
     */
    long lowestPosition() const { return this->IG2LO(); }


    /**
     *  @brief The number of words in the list
     */
    long NW() const { return this->NPL(); }

    /**
     *  @brief The number of words in the list
     */
    long numWords() const { return this->NW(); }

    /**
     *  @brief The group index
     */
    long IG() const { return this->N2(); }

    /**
     *  @brief The group index
     */
    long groupIndex() const { return this->IG(); }

    /**
     *  @brief A block of data from the record
     *
     *  @param[in] position   the requested block
     */
    auto data( unsigned int block ) const {

      std::size_t size = this->NW() / this->NG2();
      return this->list() |
        ranges::view::drop_exactly( block * size ) |
        ranges::view::take_exactly( size );
    }

    using ListRecord::list;

  };

}
}
}

#endif
