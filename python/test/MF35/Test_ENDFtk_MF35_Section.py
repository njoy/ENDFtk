# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF35 import Section
from ENDFtk.MF35 import SquareMatrix
from ENDFtk.tree import Tape

class Test_ENDFtk_MF35_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( " 9.423900+4 2.369986+2          0          0          1          0943735 18     \n"
              " 0.000000+0 1.000000+6          1          7          6          3943735 18     \n"
              " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943735 18     \n" )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  943735  0     \n'
    valid_FEND = '                                                                  9437 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  943735  1     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 18, chunk.MT )
            self.assertEqual( 18, chunk.section_number )
            self.assertEqual( 94239, chunk.ZA )
            self.assertEqual( 94239, chunk.target_identifier )
            self.assertAlmostEqual( 2.369986e+2, chunk.AWR )
            self.assertAlmostEqual( 2.369986e+2, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.NK )
            self.assertEqual( 1, chunk.number_energy_blocks )
            self.assertEqual( 1, len(chunk.energy_blocks) )
            self.assertEqual( 18, chunk.MT )
            self.assertEqual( 18, chunk.section_number )

            sub = chunk.energy_blocks[0]

            # subsection
            self.assertEqual( 7, sub.LB );
            self.assertEqual( 7, sub.procedure );
            self.assertEqual( 6, sub.NT );
            self.assertEqual( 6, sub.number_values );
            self.assertEqual( 3, sub.NE );
            self.assertEqual( 3, sub.number_energies );
            self.assertAlmostEqual( 0., sub.energies[0] );
            self.assertAlmostEqual( 100., sub.energies[1] );
            self.assertAlmostEqual( 200., sub.energies[2] );
            self.assertAlmostEqual( 1., sub.values[0] );
            self.assertAlmostEqual( 2., sub.values[1] );
            self.assertAlmostEqual( 3., sub.values[2] );

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 9437, 35 ) )

        # the data is given explicitly
        chunk = Section(
            mt=18, zaid=94239, awr=2.369986e+2,
            blocks=[SquareMatrix(
                        0, 1.0e6, [0, 100, 200], [1, 2, 3]
                        )]
            )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.materials.front().file( 35 ).section( 18 ).parse()

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
