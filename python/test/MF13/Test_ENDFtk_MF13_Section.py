# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF13 import Section
from ENDFtk.MF13 import PartialCrossSection
from ENDFtk.tree import Tape

class Test_ENDFtk_MF13_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 9.223500+4 2.330250+2          0          0          1          0922813 18     \n'
              ' 0.000000+0 0.000000+0          0          1          1          2922813 18     \n'
              '          2          2                                            922813 18     \n'
              ' 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922813 18     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  922813  0     \n'
    valid_FEND = '                                                                  9228 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  922813  1     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 18, chunk.MT )
            self.assertEqual( 18, chunk.section_number )

            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 2.330250e+2, chunk.AWR )
            self.assertAlmostEqual( 2.330250e+2, chunk.atomic_weight_ratio )

            self.assertEqual( None, chunk.total_cross_section )
            self.assertEqual( 1, len( chunk.photon_partial_cross_sections ) )

            self.assertEqual( 1, chunk.NK )
            self.assertEqual( 1, chunk.number_photons )

            partial = chunk.photon_partial_cross_sections[0]
            self.assertAlmostEqual( 0.0, partial.EG )
            self.assertAlmostEqual( 0.0, partial.photon_or_binding_energy )
            self.assertAlmostEqual( 0.0, partial.ES )
            self.assertAlmostEqual( 0.0, partial.level_energy )
            self.assertEqual( 0, partial.LP )
            self.assertEqual( 0, partial.primary_photon_flag )
            self.assertEqual( 1, partial.LF )
            self.assertEqual( 1, partial.LAW )
            self.assertEqual( 2, partial.NP )
            self.assertEqual( 2, partial.number_points )
            self.assertEqual( 1, partial.NR )
            self.assertEqual( 1, partial.number_interpolation_regions )
            self.assertEqual( 1, len( partial.INT ) )
            self.assertEqual( 1, len( partial.NBT ) )
            self.assertEqual( 2, partial.INT[0] )
            self.assertEqual( 2, partial.NBT[0] )
            self.assertEqual( 1, len( partial.interpolants ) )
            self.assertEqual( 1, len( partial.boundaries ) )
            self.assertEqual( 2, partial.interpolants[0] )
            self.assertEqual( 2, partial.boundaries[0] )
            self.assertEqual( 2, len( partial.energies ) )
            self.assertEqual( 2, len( partial.cross_sections ) )
            self.assertAlmostEqual( 1e-5, partial.energies[0] )
            self.assertAlmostEqual( 3e+7, partial.energies[1] )
            self.assertAlmostEqual( 8.579050e+0, partial.cross_sections[0] )
            self.assertAlmostEqual( 1.487778e+1, partial.cross_sections[1] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 9228, 13 ) )

        # the data is given explicitly
        chunk = Section( mt = 18, zaid = 92235, awr = 2.330250e+2,
                         partial = PartialCrossSection( 0.0, 0.0, 0, 1,
                                                        [ 2 ], [ 2 ],
                                                        [ 1e-5, 3e+7 ],
                                                        [ 8.579050e+0, 1.487778e+1 ] ) )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.materials.front().file( 13 ).section( 18 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
