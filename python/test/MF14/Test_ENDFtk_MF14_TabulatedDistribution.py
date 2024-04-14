# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF14 import TabulatedDistribution

class Test_ENDFtk_MF4_TabulatedDistribution( unittest.TestCase ) :
    """Unit test for the TabulatedDistribution class."""

    chunk = ( ' 0.000000+0 1.000000-5          0          0          1          3922814  2     \n'
              '          3          2                                            922814  2     \n'
              '-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+0922814  2     \n' )

    invalid = ( ' 0.000000+0 1.000000-5          0          0          2          3922814  2     \n'
                '          3          2                                            922814  2     \n'
                '-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+0922814  2     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )
            self.assertEqual( 3, chunk.NP )
            self.assertEqual( 3, chunk.number_points )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 3, chunk.NBT[0] )
            self.assertEqual( 2, chunk.INT[0] )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 3, len( chunk.cosines ) )
            self.assertAlmostEqual( -1.0 , chunk.MU[0] )
            self.assertAlmostEqual( 0.0, chunk.MU[1] )
            self.assertAlmostEqual( 1.0, chunk.MU[2] )
            self.assertAlmostEqual( -1.0 , chunk.cosines[0] )
            self.assertAlmostEqual( 0.0, chunk.cosines[1] )
            self.assertAlmostEqual( 1.0, chunk.cosines[2] )
            self.assertEqual( 3, len( chunk.probabilities ) )
            self.assertAlmostEqual( 0.0 , chunk.F[0] )
            self.assertAlmostEqual( 1.0, chunk.F[1] )
            self.assertAlmostEqual( 0.0, chunk.F[2] )
            self.assertAlmostEqual( 0.0 , chunk.probabilities[0] )
            self.assertAlmostEqual( 1.0, chunk.probabilities[1] )
            self.assertAlmostEqual( 0.0, chunk.probabilities[2] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 14, 2 ) )

        # the data is given explicitly
        chunk = TabulatedDistribution( energy = 1e-5,
                                       boundaries = [ 3 ], interpolants = [ 2 ],
                                       cosines = [ -1.0, 0.0, 1.0 ], probabilities = [ 0.0, 1.0, 0.0 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = TabulatedDistribution.from_string( self.chunk, 9228, 14, 2 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = TabulatedDistribution( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = TabulatedDistribution(
                        energy = 1e-5,
                        boundaries = [ 4 ], interpolants = [ 2 ],
                        cosines = [ -1.0, 0.0, 1.0 ], probabilities = [ 0.0, 1.0, 0.0 ] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedDistribution.from_string( self.invalid, 9228, 14, 2 )

if __name__ == '__main__' :

    unittest.main()
