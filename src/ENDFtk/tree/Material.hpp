#ifndef NJOY_ENDFTK_TREE_MATERIAL
#define NJOY_ENDFTK_TREE_MATERIAL

// system includes
#include <vector>
#include <map>

// other includes
#include "header-utilities/echoErroneousLine.hpp"
#include "ENDFtk/tree/File.hpp"
#include "boost/hana.hpp"

namespace njoy {
namespace ENDFtk {

  // hana namespace declaration inside ENDFtk
  namespace hana = boost::hana;
  inline namespace literals { using namespace hana::literals; }

namespace tree {

  /**
   *  @class
   *  @brief The ENDF tree material to index and access ENDF file data
   *
   *  This class represents a single material in an ENDF tape and contains the
   *  indexed ENDF files. It is created by the ENDF tree Tape class and should
   *  not be directly constructed by a user.
   */
  class Material {

  public:

    /* type aliases */
    using iterator = typename std::vector< File >::iterator;
    using const_iterator = typename std::vector< File >::iterator;

  private:

    /* fields */
    int mat_;
    std::map< int, File > files_;

    /* auxiliary functions */
    #include "ENDFtk/tree/Material/src/createMap.hpp"

  public:

    /* constructor */
    #include "ENDFtk/tree/Material/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return MAT number of the material
     */
    int MAT() const { return this->mat_; }

    /**
     *  @brief Return MAT number of the material
     */
    int materialNumber() const { return this->MAT(); }

    /**
     *  @brief Return all file numbers in the material
     */
    auto fileNumbers() const {

      return ranges::cpp20::views::keys( this->files_ );
    }

    #include "ENDFtk/tree/Material/src/file.hpp"

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in]   mf   the MF number of the material to be returned
     */
    const File& MF( int mf ) const { return this->file( mf ); }

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in]   mf   the MF number of the material to be returned
     */
    File& MF( int mf ) { return this->file( mf ); }

    /**
     *  @brief Return whether or not the material has a file with the given MF
     *         number
     *
     *  @param[in]   mf   the MF number of the file
     */
    bool hasMF( int mf ) const { return this->files_.count( mf ); }

    /**
     *  @brief Return whether or not the material has a file with the given MF
     *         number
     *
     *  @param[in]   mf   the MF number of the file
     */
    bool hasFile( int mf ) const { return this->hasMF( mf ); }

    /**
     *  @brief Return all files in the material
     */
    auto files() const { return this->files_ | ranges::cpp20::views::values; }

    /**
     *  @brief Return a begin iterator to all files
     */
    auto begin() const {

      return ( this->files_ | ranges::cpp20::views::values ).begin();
    }

    /**
     *  @brief Return an end iterator to all files
     */
    auto end() const {

      return ( this->files_ | ranges::cpp20::views::values ).end();
    }

    /**
     *  @brief Return the number of files in the materials
     */
    std::size_t size() const { return files_.size(); }

    /**
     *  @brief Return the material's content
     */
    auto content() const {

      std::string content;
      for ( const auto& file : this->files() ) {

        content += file.content();
      }

      if ( content.size() ) {

        auto output = std::back_inserter( content );
        MEND().print( output );
      }

      return content;
    }

    #include "ENDFtk/tree/Material/src/remove.hpp"
    #include "ENDFtk/tree/Material/src/insert.hpp"

    #include "ENDFtk/tree/Material/src/parse.hpp"
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
