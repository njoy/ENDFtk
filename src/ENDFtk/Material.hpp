#ifndef NJOY_ENDFTK_MATERIAL
#define NJOY_ENDFTK_MATERIAL

// system includes
#include <list>
#include <variant>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/file/1.hpp"
#include "ENDFtk/file/2.hpp"
#include "ENDFtk/file/3.hpp"
#include "ENDFtk/file/4.hpp"
#include "ENDFtk/file/5.hpp"
#include "ENDFtk/file/6.hpp"
#include "ENDFtk/file/7.hpp"
#include "ENDFtk/file/8.hpp"
#include "ENDFtk/file/9.hpp"
#include "ENDFtk/file/10.hpp"
#include "ENDFtk/file/12.hpp"
#include "ENDFtk/file/13.hpp"
#include "ENDFtk/file/14.hpp"
#include "ENDFtk/file/15.hpp"
#include "ENDFtk/file/23.hpp"
#include "ENDFtk/file/26.hpp"
#include "ENDFtk/file/27.hpp"
#include "ENDFtk/file/28.hpp"
#include "ENDFtk/file/30.hpp"
#include "ENDFtk/file/31.hpp"
#include "ENDFtk/file/32.hpp"
#include "ENDFtk/file/33.hpp"
#include "ENDFtk/file/34.hpp"
#include "ENDFtk/file/35.hpp"
#include "ENDFtk/file/40.hpp"
#include "tools/overload.hpp"

namespace njoy {
namespace ENDFtk {

  class Material {

  public:

    using FileVariant = std::variant<
                            file::Type< 1 >, file::Type< 2 >, file::Type< 3 >,
                            file::Type< 4 >, file::Type< 5 >, file::Type< 6 >,
                            file::Type< 7 >, file::Type< 8 >, file::Type< 9 >,
                            file::Type< 10 >, file::Type< 12 >, file::Type< 13 >,
                            file::Type< 14 >, file::Type< 15 >, file::Type< 23 >,
                            file::Type< 26 >, file::Type< 27 >, file::Type< 28 >,
                            file::Type< 30 >, file::Type< 31 >, file::Type< 32 >,
                            file::Type< 33 >, file::Type< 34 >, file::Type< 35 >,
                            file::Type< 40 > >;

    using SectionVariant = std::variant<
                               std::reference_wrapper< const section::Type< 1, 451 > >,
                               std::reference_wrapper< const section::Type< 1, 452 > >,
                               std::reference_wrapper< const section::Type< 1, 455 > >,
                               std::reference_wrapper< const section::Type< 1, 456 > >,
                               std::reference_wrapper< const section::Type< 1, 458 > >,
                               std::reference_wrapper< const section::Type< 1, 460 > >,
                               std::reference_wrapper< const section::Type< 2, 151 > >,
                               std::reference_wrapper< const section::Type< 2, 152 > >,
                               std::reference_wrapper< const section::Type< 3 > >,
                               std::reference_wrapper< const section::Type< 4 > >,
                               std::reference_wrapper< const section::Type< 5 > >,
                               std::reference_wrapper< const section::Type< 6 > >,
                               std::reference_wrapper< const section::Type< 7, 2 > >,
                               std::reference_wrapper< const section::Type< 7, 4 > >,
                               std::reference_wrapper< const section::Type< 7, 451 > >,
                               std::reference_wrapper< const section::Type< 8, 454 > >,
                               std::reference_wrapper< const section::Type< 8, 457 > >,
                               std::reference_wrapper< const section::Type< 8, 459 > >,
                               std::reference_wrapper< const section::Type< 9 > >,
                               std::reference_wrapper< const section::Type< 10 > >,
                               std::reference_wrapper< const section::Type< 12 > >,
                               std::reference_wrapper< const section::Type< 13 > >,
                               std::reference_wrapper< const section::Type< 14 > >,
                               std::reference_wrapper< const section::Type< 15 > >,
                               std::reference_wrapper< const section::Type< 23 > >,
                               std::reference_wrapper< const section::Type< 26 > >,
                               std::reference_wrapper< const section::Type< 27 > >,
                               std::reference_wrapper< const section::Type< 28 > >,
                               std::reference_wrapper< const section::Type< 31 > >,
                               std::reference_wrapper< const section::Type< 32, 151 > >,
                               std::reference_wrapper< const section::Type< 33 > >,
                               std::reference_wrapper< const section::Type< 34 > >,
                               std::reference_wrapper< const section::Type< 35 > >,
                               std::reference_wrapper< const section::Type< 40 > > >;

  private:

    /* fields */
    int mat_;
    std::list< FileVariant > files_;

    /* auxiliary functions */
    #include "ENDFtk/Material/src/find.hpp"
    #include "ENDFtk/Material/src/fill.hpp"
    #include "ENDFtk/Material/src/read.hpp"
    #include "ENDFtk/Material/src/verifyMEND.hpp"

  public:

    /* constructors */
    #include "ENDFtk/Material/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the material number
     */
    int MAT() const { return this->mat_; }

    /**
     *  @brief Return the material number
     */
    int materialNumber() const { return this->MAT(); }

    /**
     *  @brief Return the files stored in this material
     */
    auto MFs() {

      using namespace njoy::tools;
      return std20::views::all( this->files_ );
    }

    /**
     *  @brief Return the files stored in this material
     */
    auto files() { return this->MFs(); }

    /**
     *  @brief Return the files stored in this material
     */
    auto MFs() const {

      using namespace njoy::tools;
      return std20::views::all( this->files_ );
    }

    /**
     *  @brief Return the files stored in this material
     */
    auto files() const { return this->MFs(); }

    /**
     *  @brief Return an iterator to the start of the files
     */
    auto begin() { return this->files().begin(); }

    /**
     *  @brief Return an iterator to the end of the files
     */
    auto end() { return this->files().end(); }

    /**
     *  @brief Return an iterator to the start of the files
     */
    auto begin() const { return this->files().begin(); }

    /**
     *  @brief Return an iterator to the end of the files
     */
    auto end() const { return this->files().end(); }

    /**
     *  @brief Verify if a given file (defined by the MF number) is defined
     *
     *  @param mf   the MF number of the file to be verified
     */
    bool hasMF( int mf ) const {

      return this->find( mf ) != this->files_.end();
    }

    /**
     *  @brief Verify if a given file (defined by the MF number) is defined
     *
     *  @param mf   the MF number of the file to be verified
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

      return this->hasMF( mf )
                 ? std::visit( [&] ( const auto& file ) -> bool
                                   { return file.hasMT( mt ); },
                               this->MF( mf ) )
                 : false;
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
     *  @brief Return the file with the requested MF number
     *
     *  @param[in] mf   the MF number of the file to be returned
     */
    const FileVariant& file( int mf ) const {

      auto iter = this->find( mf );
      if ( iter != this->files_.end() ) {

        return *iter;
      }

      Log::error( "Requested file number (MF) does not"
                  " correspond to a stored file" );
      Log::info( "Requested file number: {}", mf );
      Log::info( "Material queried: ", this->MAT() );
      throw std::exception();
    }

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in] mf   the MF number of the file to be returned
     */
    const FileVariant& MF( int mf ) const {

      return this->file( mf );
    }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  Note: this returns a variant of reference wrappers since the data is
     *        stored by file first.
     *
     *  @param[in] mf   the MF number of the section to be returned
     *  @param[in] mt   the MT number of the section to be returned
     */
    SectionVariant section( int mf, int mt ) const {

      return std::visit(
                 tools::overload{
                     [=] ( const file::Type< 1 >& file ) -> SectionVariant
                         { return std::visit(
                                      [=] ( const auto& section ) -> SectionVariant
                                          { return std::cref( section ); },
                                      file.section( mt ) ); },
                     [=] ( const file::Type< 2 >& file ) -> SectionVariant
                         { return std::visit(
                                      [=] ( const auto& section ) -> SectionVariant
                                          { return std::cref( section ); },
                                      file.section( mt ) ); },
                     [=] ( const file::Type< 7 >& file ) -> SectionVariant
                         { return std::visit(
                                      [=] ( const auto& section ) -> SectionVariant
                                          { return std::cref( section ); },
                                      file.section( mt ) ); },
                     [=] ( const file::Type< 8 >& file ) -> SectionVariant
                         { return std::visit(
                                      [=] ( const auto& section ) -> SectionVariant
                                          { return std::cref( section ); },
                                      file.section( mt ) ); },
                     [] ( const file::Type< 30 >& ) -> SectionVariant
                        { throw std::exception(); },
                     // MF=32 is enumerated but only one section is allowed so
                     // we do not need a visit on the section
                     [=] ( const auto& file ) -> SectionVariant
                         { return std::cref( file.section( mt ) ); } },
                 this->file( mf ) );
    }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  Note: this returns a variant of reference wrappers since the data is
     *        stored by file first.
     *
     *  @param[in] mf   the MF number of the section to be returned
     *  @param[in] mt   the MT number of the section to be returned
     */
    SectionVariant MFMT( int mf, int mt ) const {

      return this->section( mf, mt );
    }

    #include "ENDFtk/Material/src/print.hpp"
  };

} // ENDFtk namespace
} // njoy namespace

#endif
