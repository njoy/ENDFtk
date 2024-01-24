# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF23 import Section
from ENDFtk.tree import Tape

class Test_ENDFtk_MF23_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 1.000000+3 9.992414-1          0          0          0          0 10023525     \n'
              ' 1.000000+0 2.000000+0          0          0          1          2 10023525     \n'
              '          2          2                                             10023525     \n'
              ' 1.000000+1 2.748960+8 1.00000+11 1.311760-5                       10023525     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                   10023  0     \n'
    valid_FEND = '                                                                   100 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                   10023  1     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 525, chunk.MT )
            self.assertEqual( 525, chunk.section_number )
            self.assertEqual( 1000, chunk.ZA )
            self.assertEqual( 1000, chunk.target_identifier )
            self.assertAlmostEqual( 0.9992414, chunk.AWR )
            self.assertAlmostEqual( 0.9992414, chunk.atomic_weight_ratio )
            self.assertAlmostEqual( 1., chunk.EPE )
            self.assertAlmostEqual( 1., chunk.subshell_binding_energy )
            self.assertAlmostEqual( 2., chunk.EFL )
            self.assertAlmostEqual( 2., chunk.fluorescence_yield )

            self.assertEqual( 2, chunk.NP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] );
            self.assertEqual( 2, chunk.boundaries[0] );
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertEqual( 2, len( chunk.cross_sections ) )
            self.assertAlmostEqual( 10., chunk.energies[0] )
            self.assertAlmostEqual( 1e+11, chunk.energies[1] )
            self.assertAlmostEqual( 2.748960e+8, chunk.cross_sections[0] )
            self.assertAlmostEqual( 1.31176E-5, chunk.cross_sections[1] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 100, 23 ) )

        # the data is given explicitly
        chunk = Section( mt = 525,  zaid = 1000, awr = 0.9992414,
                         epe = 1., efl = 2.,
                         interpolants = [ 2 ], boundaries = [ 2 ],
                         energies = [ 10., 1e+11 ],
                         xs = [ 2.748960e+8, 1.31176E-5 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 100 ).file( 23 ).section( 525 ).parse()

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
