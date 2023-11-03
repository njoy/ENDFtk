# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import SquareMatrix
from ENDFtk import RectangularMatrix
from ENDFtk import CovariancePairs
from ENDFtk.MF32.MT151 import ScatteringRadiusCovariances

class Test_ENDFtk_MF32_MT151_ScatteringRadiusCovariances( unittest.TestCase ) :
    """Unit test for the ScatteringRadiusCovariances class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          0          3943732151     \n'
              ' 0.000000+0 0.000000+0          0          5          7          3943732151     \n'
              ' 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943732151     \n'
              ' 4.000000+0                                                       943732151     \n'
              ' 0.000000+0 0.000000+0          0          6         13          3943732151     \n'
              ' 1.100000+0 1.200000+0 1.300000+0 2.100000+0 2.200000+0 2.300000+0943732151     \n'
              ' 2.400000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0943732151     \n'
              ' 6.000000+0                                                       943732151     \n'
              ' 0.000000+0 0.000000+0          0          1          4          2943732151     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      943732151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.NI )
            self.assertEqual( 3, chunk.number_data_blocks )
            self.assertEqual( 3, len( chunk.data ) )

            stuff = chunk.data[0]

            self.assertEqual( 0, stuff.LS )
            self.assertEqual( 0, stuff.symmetry_flag )
            self.assertEqual( False, stuff.is_symmetric )
            self.assertEqual( 5, stuff.LB )
            self.assertEqual( 5, stuff.procedure )
            self.assertEqual( 7, stuff.NT )
            self.assertEqual( 7, stuff.number_values )
            self.assertEqual( 3, stuff.NE )
            self.assertEqual( 3, stuff.number_energies )

            self.assertAlmostEqual( 0., stuff.energies[0] )
            self.assertAlmostEqual( 100., stuff.energies[1] )
            self.assertAlmostEqual( 200., stuff.energies[2] )
            self.assertAlmostEqual( 1.,stuff.values[0] )
            self.assertAlmostEqual( 2.,stuff.values[1] )
            self.assertAlmostEqual( 3.,stuff.values[2] )
            self.assertAlmostEqual( 4.,stuff.values[3] )

            self.assertEqual( 10, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9437, 32, 151 ) )

        # the data is given explicitly
        chunk = ScatteringRadiusCovariances(
                   data = [
                       SquareMatrix( 0, [ 0, 100, 200 ], [ 1, 2, 3, 4 ] ),
                       RectangularMatrix( [ 1.1, 1.2, 1.3 ],
                                          [ 2.1, 2.2, 2.3, 2.4 ],
                                          [ 1, 2, 3, 4, 5, 6 ] ),
                       CovariancePairs( 1, [ 1., 3. ], [ 2., 4. ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ScatteringRadiusCovariances.from_string( self.chunk, 9437, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ScatteringRadiusCovariances( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
