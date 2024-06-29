#ifndef NJOY_ENDFTK_TREE_FILE
#define NJOY_ENDFTK_TREE_FILE

// system includes
#include <list>

// other includes
#include "range/v3/view/all.hpp"
#include "range/v3/view/subrange.hpp"
#include "ENDFtk/file/Type.hpp"
#include "ENDFtk/tree/Section.hpp"
#include "ENDFtk/tree/toSection.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @class
   *  @brief The ENDF tree file to index and access ENDF section data
   *
   *  This class represents a single file in an ENDF tape and contains the
   *  indexed ENDF sections from that file. It is created by the ENDF tree
   *  Material class and should not be directly constructed by a user.
   */
  class File {

    /* fields */
    int mat_;
    int mf_;
    std::list< Section > sections_;

    /* auxiliary functions */
    #include "ENDFtk/tree/File/src/find.hpp"
    #include "ENDFtk/tree/File/src/createMap.hpp"

  public:

    /* constructor */
    #include "ENDFtk/tree/File/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return MAT number of the file
     */
    int MAT() const { return this->mat_; }

    /**
     *  @brief Return MAT number of the file
     */
    int materialNumber() const { return this->MAT(); }

    /**
     *  @brief Return MF number of the file
     */
    int MF() const { return this->mf_; }

    /**
     *  @brief Return MF number of the file
     */
    int fileNumber() const { return this->MF(); }

    /**
     *  @brief Return all section numbers in the file
     */
    auto sectionNumbers() const {

      return this->sections_ | ranges::cpp20::views::transform(
                                   [] ( auto&& section )
                                      { return section.sectionNumber(); } );
    }

    #include "ENDFtk/tree/File/src/section.hpp"

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in]   mt   the MT number of the section to be returned
     */
    const Section& MT( int mt ) const { return this->section( mt ); }

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in]   mt   the MT number of the section to be returned
     */
    Section& MT( int mt ) { return this->section( mt ); }

    /**
     *  @brief Return whether or not the file has a section with the given MT
     *         number
     *
     *  @param[in]   mt   the MT number of the section
     */
    bool hasMT( int mt ) const {

      return this->find( mt ) != this->sections_.end();
    }

    /**
     *  @brief Return whether or not the file has a section with the given MT
     *         number
     *
     *  @param[in]   mt   the MT number of the section
     */
    bool hasSection( int mt ) const {  return this->hasMT( mt ); }

    /**
     *  @brief Return all sections in the file
     */
    auto sections() const {

      return this->sections_ | ranges::cpp20::views::all;
    }

    /**
     *  @brief Return all sections in the file
     */
    auto sections() {

      return this->sections_ | ranges::cpp20::views::all;
    }

    /**
     *  @brief Return a begin iterator to all sections
     */
    auto begin() const {

      return this->sections().begin();
    }

    /**
     *  @brief Return an end iterator to all sections
     */
    auto end() const {

      return this->sections().end();
    }

    /**
     *  @brief Return a begin iterator to all sections
     */
    auto begin() {

      return this->sections().end();
    }

    /**
     *  @brief Return an end iterator to all sections
     */
    auto end() {

      return this->sections().end();
    }

    /**
     *  @brief Return the number of files in the materials
     */
    std::size_t size() const { return this->sections_.size(); }

    /**
     *  @brief Return the file's content
     */
    auto content() const {

      std::string content;
      for ( const auto& section : this->sections() ) {

        content += section.content();
      }

      if ( content.size() ) {

        auto output = std::back_inserter( content );
        FEND( this->MAT() ).print( output );
      }

      return content;
    }

    #include "ENDFtk/tree/File/src/remove.hpp"
    #include "ENDFtk/tree/File/src/insertOrReplace.hpp"
    #include "ENDFtk/tree/File/src/insert.hpp"

    #include "ENDFtk/tree/File/src/parse.hpp"

    #include "ENDFtk/tree/File/src/clean.hpp"
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
