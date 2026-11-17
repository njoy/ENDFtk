#ifndef NJOY_ENDFTK_GENDF_DATARECORD
#define NJOY_ENDFTK_GENDF_DATARECORD

// system includes

// other includes
#include "ENDFtk/ListRecord.hpp"

namespace njoy {
namespace ENDFtk {

    class DataRecord: protected ListRecord {

        public:

        /**
         *  @brief constructor from parameters
         *
         *  @param[in]  temp    the temperature
         *  @param[in]  ng2     the number of secondary positions
         *  @param[in]  ig2lo   the index to lowest position
         *  @param[in]  nw      length of list
         *  @param[in]  ig      the group index
         *  @param[in]  list    the data contained (i.e. fluxes, ratios, sigmas, matrix)
         */
        DataRecord( double temp, int ng2, int ig2lo, int ig, std::vector<double>&& list):
        ListRecord(temp, 0, ng2, ig2lo, ig,
                   std::move(list)) {}

        /**
         *  @brief constructor from a buffer
         *
         *  @tparam Iterator        buffer iterator
         *
         *  @param[in]  it          the current position in the buffer
         *  @param[in]  end         the end of the buffer
         *  @param[in]  lineNumber  the current line number
         *  @param[in]  MAT         the material number
         *  @param[in]  MF          the file number
         *  @param[in]  MT          the section number
         */
        template<typename Iterator>
        DataRecord(Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT):
                ListRecord(it, end, lineNumber, MAT, MF, MT) {}


        /* methods */

        /**
         *  @brief Return the temperature
         */
        double TEMP() const {return this->C1();}

        /**
         *  @brief Return the temperature
         */
        double temperature() const {return this->TEMP();}

        /**
         *  @brief Return the number of secondary positions
         */
        int NG2() const {return this->L1();}

        /**
         *  @brief Return the number of secondary positions
         */
        int numberDataTypes() const {return this->NG2();}

        /**
         *  @brief Return this group's index to lowest non-zero group
         */
        int IG2LO() const {return this->L2();}

        /**
         *  @brief Return this group's index to lowest non-zero group
         */
        int indexToLowestNonzero() const {return this->IG2LO();}

        /**
         *  @brief Return the number of words in list
         */
        int NW() const {return this->NPL();}

        /**
         *  @brief Return the number of words in list
         */
        int numberWords() const {return this->NW();}

        /**
         *  @brief Return the group index
         */
        int IG() const {return this->N2();}

        /**
         *  @brief Return the group index
         */
        int groupIndex() const {return this->IG();}

        using ListRecord::list;
        using ListRecord::print;

    };


} // ENDFtk
} // njoy

#endif