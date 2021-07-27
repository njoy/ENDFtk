# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF33 import CovariancePairs

class Test_ENDFtk_MF33_CovariancePairs( unittest.TestCase ) :
    """Unit test for the CovariancePairs class."""

    chunk1 = (
        " 0.000000+0 0.000000+0          0          1          4          2922833  5     \n"
        " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      922833  5     \n" )

    chunk3 = (
        " 0.000000+0 0.000000+0          2          3         10          5922833  5     \n"
        " 1.000000+0 2.000000+0 3.000000+0 4.000000+0  5.00000+0 6.000000+0922833  5     \n"
        " 7.000000+0 8.000000+0 9.000000+0 1.000000+1                      922833  5     \n" )

    def test_lb1( self ) :

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
            self.assertAlmostEqual( 1., chunk.EK[0] )
            self.assertAlmostEqual( 2., chunk.FK[0] )
            self.assertAlmostEqual( 3., chunk.EK[1] )
            self.assertAlmostEqual( 4., chunk.FK[1] )
            self.assertAlmostEqual( 1., chunk.first_array_energies[0] )
            self.assertAlmostEqual( 2., chunk.first_array_fvalues[0] )
            self.assertAlmostEqual( 3., chunk.first_array_energies[1] )
            self.assertAlmostEqual( 4., chunk.first_array_fvalues[1] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk1,
                              chunk.to_string( 9228, 33, 5 ) )

        # the data is given explicitly
        chunk = CovariancePairs(lb=1, energies=[1, 3], fvalues=[2, 4])

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = CovariancePairs.from_string( self.chunk1, 9228, 33, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = CovariancePairs( chunk )

        verify_chunk( self, copy )

    def test_lb3( self ) :

        def verify_chunk( self, chunk ) :

            # metadata
            self.assertEqual( 2, chunk.LT );
            self.assertEqual( 2, chunk.number_second_pairs );
            self.assertEqual( 3, chunk.LB );
            self.assertEqual( 3, chunk.procedure );
            self.assertEqual( 10, chunk.NT );
            self.assertEqual( 10, chunk.number_values );
            self.assertEqual( 5, chunk.NP );
            self.assertEqual( 5, chunk.number_pairs );

            # values
            self.assertAlmostEqual( 1., chunk.EK[0] );
            self.assertAlmostEqual( 2., chunk.FK[0] );
            self.assertAlmostEqual( 3., chunk.EK[1] );
            self.assertAlmostEqual( 4., chunk.FK[1] );
            self.assertAlmostEqual( 7., chunk.EL[0] );
            self.assertAlmostEqual( 8., chunk.FL[0] );
            self.assertAlmostEqual( 9., chunk.EL[1] );
            self.assertAlmostEqual( 10., chunk.FL[1] );
            self.assertAlmostEqual( 1., chunk.first_array_energies[0] );
            self.assertAlmostEqual( 2., chunk.first_array_fvalues[0] );
            self.assertAlmostEqual( 3., chunk.first_array_energies[1] );
            self.assertAlmostEqual( 4., chunk.first_array_fvalues[1] );
            self.assertAlmostEqual( 7., chunk.second_array_energies[0] );
            self.assertAlmostEqual( 8., chunk.second_array_fvalues[0] );
            self.assertAlmostEqual( 9., chunk.second_array_energies[1] );
            self.assertAlmostEqual( 10., chunk.second_array_fvalues[1] );

            self.assertEqual( 3, chunk.NC );

            # verify string
            self.assertEqual( self.chunk3,
                              chunk.to_string( 9228, 33, 5 ) )

        # the data is given explicitly
        chunk = CovariancePairs(lb=3,
                                ek=[1, 3, 5], fk=[2, 4, 6],
                                el=[7, 9], fl=[8, 10])

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = CovariancePairs.from_string( self.chunk3, 9228, 33, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = CovariancePairs( chunk )

        verify_chunk( self, copy )


if __name__ == '__main__' :

    unittest.main()
