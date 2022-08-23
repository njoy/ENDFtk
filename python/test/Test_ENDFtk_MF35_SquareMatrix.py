# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF35 import SquareMatrix

class Test_ENDFtk_MF35_SquareMatrix( unittest.TestCase ) :
    """Unit test for the SquareMatrix class."""

    chunk = (
        " 0.000000+0 0.000000+0          0          5          7          3922833  5     \n"
        " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0922833  5     \n"
        " 4.000000+0                                                       922833  5     \n" )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # metadata
            self.assertEqual( 0, chunk.LS )
            self.assertEqual( 0, chunk.symmetry_flag )
            self.assertFalse( chunk.is_symmetric )
            self.assertEqual( 5, chunk.LB )
            self.assertEqual( 5, chunk.procedure )
            self.assertEqual( 7, chunk.NT )
            self.assertEqual( 7, chunk.number_values )
            self.assertEqual( 3, chunk.NE )
            self.assertEqual( 3, chunk.number_energies )

            # values
            self.assertAlmostEqual( 0., chunk.energies[0] )
            self.assertAlmostEqual( 100., chunk.energies[1] )
            self.assertAlmostEqual( 200., chunk.energies[2] )
            self.assertAlmostEqual( 1., chunk.values[0] )
            self.assertAlmostEqual( 2., chunk.values[1] )
            self.assertAlmostEqual( 3., chunk.values[2] )
            self.assertAlmostEqual( 4., chunk.values[3] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk,
                              chunk.to_string( 9228, 33, 5 ) )

        # the data is given explicitly
        chunk = SquareMatrix(ls=0, energies=[0, 100, 200], values=[1, 2, 3, 4])

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = SquareMatrix.from_string( self.chunk, 9228, 33, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = SquareMatrix( chunk )

        verify_chunk( self, copy )


if __name__ == '__main__' :

    unittest.main()
