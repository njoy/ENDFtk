# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6 import AngularDistribution
from ENDFtk.MF6 import EnergyDistribution

class Test_ENDFtk_MF6_AngularDistribution( unittest.TestCase ) :
    """Unit test for the AngularDistribution class."""

    chunk = ( ' 0.000000+0 1.000000-5          0          0          1          29228 6  5     \n'
              '          2          4                                            9228 6  5     \n'
              ' 0.000000+0 1.000000+0          0          0          1          49228 6  5     \n'
              '          4          2                                            9228 6  5     \n'
              ' 1.000000-5 0.000000+0 1.100000+7 2.000000+0 1.147000+7 4.000000+09228 6  5     \n'
              ' 3.000000+7 6.000000+0                                            9228 6  5     \n'
              ' 0.000000+0-1.000000+0          0          0          1          39228 6  5     \n'
              '          3          5                                            9228 6  5     \n'
              ' 1.000000-5 6.000000+0 1.000000+6 4.000000+0 3.000000+7 2.000000+09228 6  5     \n' )

    invalid = ( ' 0.000000+0 1.000000-5          0          0          1          29228 6  5     \n'
                '          2          4                                            9228 6  5     \n'
                ' 0.000000+0 1.000000+0          0          0          1          59228 6  5     \n'
                '          4          2                                            9228 6  5     \n'
                ' 1.000000-5 0.000000+0 1.100000+7 2.000000+0 1.147000+7 4.000000+09228 6  5     \n'
                ' 3.000000+7 6.000000+0                                            9228 6  5     \n'
                ' 0.000000+0-1.000000+0          0          0          1          39228 6  5     \n'
                '          3          5                                            9228 6  5     \n'
                ' 1.000000-5 6.000000+0 1.000000+6 4.000000+0 3.000000+7 2.000000+09228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 2, chunk.NMU )
            self.assertEqual( 1, chunk.NRM )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 4, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )

            self.assertEqual( 2, len( chunk.MU ) )
            self.assertEqual( 2, len( chunk.cosines ) )
            self.assertAlmostEqual( 1., chunk.MU[0] )
            self.assertAlmostEqual( -1., chunk.MU[1] )
            self.assertAlmostEqual( 1., chunk.cosines[0] )
            self.assertAlmostEqual( -1., chunk.cosines[1] )

            distributions = chunk.energy_distributions
            self.assertEqual( 2, len( distributions ) )

            distribution = distributions[0]
            self.assertAlmostEqual( 1., distribution.MU )
            self.assertAlmostEqual( 1., distribution.cosine )
            self.assertEqual( 1, distribution.NRP )
            self.assertEqual( 4, distribution.NEP )
            self.assertEqual( 1, len( distribution.interpolants ) )
            self.assertEqual( 1, len( distribution.boundaries ) )
            self.assertEqual( 2, distribution.interpolants[0] )
            self.assertEqual( 4, distribution.boundaries[0] )
            self.assertEqual( 4, len( distribution.EP ) )
            self.assertEqual( 4, len( distribution.energies ) )
            self.assertEqual( 4, len( distribution.F ) )
            self.assertEqual( 4, len( distribution.probabilities ) )
            self.assertAlmostEqual( 1e-5, distribution.EP[0] )
            self.assertAlmostEqual( 1.1e+7, distribution.EP[1] )
            self.assertAlmostEqual( 1.147e+7, distribution.EP[2] )
            self.assertAlmostEqual( 3e+7, distribution.EP[3] )
            self.assertAlmostEqual( 1e-5, distribution.energies[0] )
            self.assertAlmostEqual( 1.1e+7, distribution.energies[1] )
            self.assertAlmostEqual( 1.147e+7, distribution.energies[2] )
            self.assertAlmostEqual( 3e+7, distribution.energies[3] )
            self.assertAlmostEqual( 0., distribution.F[0] )
            self.assertAlmostEqual( 2., distribution.F[1] )
            self.assertAlmostEqual( 4., distribution.F[2] )
            self.assertAlmostEqual( 6., distribution.F[3] )
            self.assertAlmostEqual( 0., distribution.probabilities[0] )
            self.assertAlmostEqual( 2., distribution.probabilities[1] )
            self.assertAlmostEqual( 4., distribution.probabilities[2] )
            self.assertAlmostEqual( 6., distribution.probabilities[3] )

            distribution = distributions[1]
            self.assertAlmostEqual( -1., distribution.MU )
            self.assertAlmostEqual( -1., distribution.cosine )
            self.assertEqual( 1, distribution.NRP )
            self.assertEqual( 3, distribution.NEP )
            self.assertEqual( 1, len( distribution.interpolants ) )
            self.assertEqual( 1, len( distribution.boundaries ) )
            self.assertEqual( 5, distribution.interpolants[0] )
            self.assertEqual( 3, distribution.boundaries[0] )
            self.assertEqual( 3, len( distribution.EP ) )
            self.assertEqual( 3, len( distribution.energies ) )
            self.assertEqual( 3, len( distribution.F ) )
            self.assertEqual( 3, len( distribution.probabilities ) )
            self.assertAlmostEqual( 1e-5, distribution.EP[0] )
            self.assertAlmostEqual( 1e+6, distribution.EP[1] )
            self.assertAlmostEqual( 3e+7, distribution.EP[2] )
            self.assertAlmostEqual( 1e-5, distribution.energies[0] )
            self.assertAlmostEqual( 1e+6, distribution.energies[1] )
            self.assertAlmostEqual( 3e+7, distribution.energies[2] )
            self.assertAlmostEqual( 6., distribution.F[0] )
            self.assertAlmostEqual( 4., distribution.F[1] )
            self.assertAlmostEqual( 2., distribution.F[2] )
            self.assertAlmostEqual( 6., distribution.probabilities[0] )
            self.assertAlmostEqual( 4., distribution.probabilities[1] )
            self.assertAlmostEqual( 2., distribution.probabilities[2] )

            self.assertEqual( 9, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = AngularDistribution( energy = 1e-5, boundaries = [ 2 ], interpolants = [ 4 ],
                                     distributions = [ EnergyDistribution(
                                                         1.0, [ 4 ], [ 2 ],
                                                         [ 1e-5, 1.1e+7, 1.147e+7, 3e+7 ], [ 0., 2., 4., 6. ] ),
                                                       EnergyDistribution(
                                                         -1.0, [ 3 ], [ 5 ],
                                                         [ 1e-5, 1e+6, 3e+7 ], [ 6., 4., 2. ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = AngularDistribution.from_string( self.chunk, 9228, 6, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = AngularDistribution( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = AngularDistribution( energy = 1e-5, boundaries = [ 2, 4 ], interpolants = [ 4 ],
                                         distributions = [ EnergyDistribution(
                                                             1.0, [ 4 ], [ 2 ],
                                                             [ 1e-5, 1.1e+7, 1.147e+7, 3e+7 ], [ 0., 2., 4., 6. ] ),
                                                           EnergyDistribution(
                                                             -1.0, [ 3 ], [ 5 ],
                                                             [ 1e-5, 1e+6, 3e+7 ], [ 6., 4., 2. ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = AngularDistribution.from_string( self.invalid, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
