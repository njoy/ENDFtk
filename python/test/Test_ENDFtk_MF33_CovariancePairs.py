# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF33 import CovariancePairs

class Test_ENDFtk_MF33_CovariancePairs( unittest.TestCase ) :
    """Unit test for the CovariancePairs class."""

    chunk = (
        " 0.000000+0 0.000000+0          0          1          4          2922833  5     \n"
        " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      922833  5     \n" )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # metadata
            self.assertEqual( 0, chunk.LT )
            self.assertEqual( 0, chunk.number_second_pairs )
            self.assertEqual( 1, chunk.LB )
            self.assertEqual( 1, chunk.procedure )
            self.assertEqual( 4, chunk.NT )
            self.assertEqual( 4, chunk.number_values )
            self.assertEqual( 2, chunk.NP )
            self.assertEqual( 2, chunk.number_pairs )

            # values
            self.assertAlmostEqual( 1., chunk.Ek[0] )
            self.assertAlmostEqual( 2., chunk.Fk[0] )
            self.assertAlmostEqual( 3., chunk.Ek[1] )
            self.assertAlmostEqual( 4., chunk.Fk[1] )
            self.assertAlmostEqual( 1., chunk.first_array_energies[0] )
            self.assertAlmostEqual( 2., chunk.first_array_fvalues[0] )
            self.assertAlmostEqual( 3., chunk.first_array_energies[1] )
            self.assertAlmostEqual( 4., chunk.first_array_fvalues[1] )

            self.assertEqual( 2, chunk.NC )

        # the data is given explicitly
        chunk = CovariancePairs(1, [1, 3], [2, 4])

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = CovariancePairs.from_string( self.chunk, 9228, 33, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = CovariancePairs( chunk )

        verify_chunk( self, copy )


if __name__ == '__main__' :

    unittest.main()
