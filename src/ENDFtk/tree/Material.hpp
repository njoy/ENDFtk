#ifndef NJOY_ENDFTK_TREE_MATERIAL
#define NJOY_ENDFTK_TREE_MATERIAL

// system includes
#include <list>

// other includes
#include "range/v3/view/all.hpp"
#include "ENDFtk/tree/Section.hpp"
#include "ENDFtk/tree/toSection.hpp"
#include "ENDFtk/tree/File.hpp"
#include "ENDFtk/tree/toFile.hpp"

namespace njoy {
namespace ENDFtk {
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

    /* fields */
    int mat_;
    std::list< File > files_;

    /* auxiliary functions */
    #include "ENDFtk/tree/Material/src/find.hpp"
    #include "ENDFtk/tree/Material/src/fill.hpp"

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

      using namespace njoy::tools;
      return this->files_ | std20::views::transform(
                                   [] ( auto&& file )
                                      { return file.fileNumber(); } );
    }

    #include "ENDFtk/tree/Material/src/file.hpp"

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in]   mf   the MF number of the file to be returned
     */
    const File& MF( int mf ) const { return this->file( mf ); }

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in]   mf   the MF number of the file to be returned
     */
    File& MF( int mf ) { return this->file( mf ); }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  @param[in]   mf   the MF number of the section to be returned
     *  @param[in]   mt   the MT number of the section to be returned
     */
    const Section& section( int mf, int mt ) const {

      return this->file( mf ).section( mt );
    }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  @param[in]   mf   the MF number of the section to be returned
     *  @param[in]   mt   the MT number of the section to be returned
     */
    Section& section( int mf, int mt ) {

      return this->file( mf ).section( mt );
    }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  @param[in]   mf   the MF number of the section to be returned
     *  @param[in]   mt   the MT number of the section to be returned
     */
    const Section& MFMT( int mf, int mt ) const {

      return this->section( mf, mt );
    }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  @param[in]   mf   the MF number of the section to be returned
     *  @param[in]   mt   the MT number of the section to be returned
     */
    Section& MFMT( int mf, int mt ) {

      return this->section( mf, mt );
    }

    /**
     *  @brief Return whether or not the material has a file with the given MF
     *         number
     *
     *  @param[in]   mf   the MF number of the file
     */
    bool hasMF( int mf ) const { return this->find( mf ) != this->files_.end(); }

    /**
     *  @brief Return whether or not the material has a file with the given MF
     *         number
     *
     *  @param[in]   mf   the MF number of the file
     */
    bool hasFile( int mf ) const { return this->hasMF( mf ); }

    /**
     *  @brief Return whether or not the material has a section with the given
     *         MF and MT number
     *
     *  @param[in]   mf   the MF number of the section
     *  @param[in]   mt   the MT number of the section
     */
    bool hasMFMT( int mf, int mt ) const {

      return this->hasMF( mf ) ? this->file( mf ).hasMT( mt ) : false;
    }

    /**
     *  @brief Return whether or not the material has a section with the given
     *         MF and MT number
     *
     *  @param[in]   mf   the MF number of the section
     *  @param[in]   mt   the MT number of the section
     */
    bool hasSection( int mf, int mt ) const { return this->hasMFMT( mf, mt ); }

    /**
     *  @brief Return all files in the material
     */
    auto files() const {

      using namespace njoy::tools;
      return this->files_ | std20::views::all;
    }

    /**
     *  @brief Return all files in the material
     */
    auto files() {

      using namespace njoy::tools;
      return this->files_ | std20::views::all;
    }

    /**
     *  @brief Return a begin iterator to all files
     */
    auto begin() const { return this->files().begin(); }

    /**
     *  @brief Return an end iterator to all files
     */
    auto end() const { return this->files().end(); }

    /**
     *  @brief Return a begin iterator to all files
     */
    auto begin()  { return this->files().begin(); }

    /**
     *  @brief Return an end iterator to all files
     */
    auto end()  { return this->files().end(); }

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
    #include "ENDFtk/tree/Material/src/insertOrReplace.hpp"
    #include "ENDFtk/tree/Material/src/insert.hpp"

    #include "ENDFtk/tree/Material/src/parse.hpp"

    #include "ENDFtk/tree/Material/src/clean.hpp"
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
