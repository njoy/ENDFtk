# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6.LAW7 import EnergyDistribution

class Test_ENDFtk_MF6_EnergyDistribution( unittest.TestCase ) :
    """Unit test for the EnergyDistribution class."""

    chunk = ( ' 0.000000+0 1.000000+0          0          0          1          49228 6  5     \n'
              '          4          2                                            9228 6  5     \n'
              ' 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n'
              ' 3.000000+7 2.149790-1                                            9228 6  5     \n' )

    invalid = ( ' 0.000000+0 1.000000+0          0          0          1          59228 6  5     \n'
                '          4          2                                            9228 6  5     \n'
                ' 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n'
                ' 3.000000+7 2.149790-1                                            9228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1., chunk.MU )
            self.assertAlmostEqual( 1., chunk.cosine )

            self.assertEqual( 1, chunk.NRP )
            self.assertEqual( 4, chunk.NEP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 4, chunk.NP )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 4, chunk.boundaries[0] )
            self.assertEqual( 4, len( chunk.EP ) )
            self.assertEqual( 4, len( chunk.energies ) )
            self.assertEqual( 4, len( chunk.F ) )
            self.assertEqual( 4, len( chunk.probabilities ) )
            self.assertAlmostEqual( 1e-5, chunk.EP[0] )
            self.assertAlmostEqual( 1.1e+7, chunk.EP[1] )
            self.assertAlmostEqual( 1.147e+7, chunk.EP[2] )
            self.assertAlmostEqual( 3e+7, chunk.EP[3] )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 1.1e+7, chunk.energies[1] )
            self.assertAlmostEqual( 1.147e+7, chunk.energies[2] )
            self.assertAlmostEqual( 3e+7, chunk.energies[3] )
            self.assertAlmostEqual( 0., chunk.F[0] )
            self.assertAlmostEqual( 8.45368e-11, chunk.F[1] )
            self.assertAlmostEqual( 6.622950e-8, chunk.F[2] )
            self.assertAlmostEqual( 2.149790e-1, chunk.F[3] )
            self.assertAlmostEqual( 0., chunk.probabilities[0] )
            self.assertAlmostEqual( 8.45368e-11, chunk.probabilities[1] )
            self.assertAlmostEqual( 6.622950e-8, chunk.probabilities[2] )
            self.assertAlmostEqual( 2.149790e-1, chunk.probabilities[3] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = EnergyDistribution( cosine = 1.0, boundaries = [ 4 ], interpolants = [ 2 ],
                                    energies = [ 1e-5, 1.1e+7, 1.147e+7, 3e+7 ],
                                    probabilities = [ 0., 8.45368e-11,
                                                      6.622950e-8, 2.149790e-1 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = EnergyDistribution.from_string( self.chunk, 9228, 6, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = EnergyDistribution( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = EnergyDistribution( cosine = 1.0, boundaries = [ 4,5 ], interpolants = [ 2 ],
                                        energies = [ 1e-5, 1.1e+7, 1.147e+7, 3e+7 ],
                                        probabilities = [ 0., 8.45368e-11,
                                                          6.622950e-8, 2.149790e-1 ] )

        with self.assertRaises( Exception ) :

            chunk = EnergyDistribution.from_string( self.invalid, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
