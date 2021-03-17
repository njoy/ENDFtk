# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF14 import TabulatedDistribution
from ENDFtk.MF14 import TabulatedDistributions

class Test_ENDFtk_MF14_TabulatedDistributions( unittest.TestCase ) :
    """Unit test for the TabulatedDistributions class."""

    chunk = ( ' 1.000000+0 2.000000+0          0          0          1          2922814  2     \n'
              '          2          1                                            922814  2     \n'
              ' 0.000000+0 1.000000-5          0          0          1          2922814  2     \n'
              '          2          2                                            922814  2     \n'
              '-1.000000+0 5.000000-1 1.000000+0 5.000000-1                      922814  2     \n'
              ' 0.000000+0 2.000000+7          0          0          1          3922814  2     \n'
              '          3          2                                            922814  2     \n'
              '-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+0922814  2     \n' )

    invalid = ( ' 1.000000+0 2.000000+0          0          0          2          2922814  2     \n'
                '          2          1                                            922814  2     \n'
                ' 0.000000+0 1.000000-5          0          0          1          2922814  2     \n'
                '          2          2                                            922814  2     \n'
                '-1.000000+0 5.000000-1 1.000000+0 5.000000-1                      922814  2     \n'
                ' 0.000000+0 2.000000+7          0          0          1          3922814  2     \n'
                '          3          2                                            922814  2     \n'
                '-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+0922814  2     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( False, chunk.LI )
            self.assertEqual( False, chunk.isotropic_angular_distributions )
            self.assertEqual( 2, chunk.LTT )
            self.assertEqual( 2, chunk.LAW )

            self.assertAlmostEqual( 1., chunk.EG )
            self.assertAlmostEqual( 1., chunk.photon_energy )
            self.assertAlmostEqual( 2., chunk.ES )
            self.assertAlmostEqual( 2., chunk.level_energy )

            self.assertEqual( 2, chunk.NE )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )

            self.assertEqual( 2, len( chunk.incident_energies ) )
            self.assertEqual( 2, len( chunk.angular_distributions ) )

            self.assertAlmostEqual( 1e-5, chunk.incident_energies[0] )
            self.assertAlmostEqual( 2e+7, chunk.incident_energies[1] )

            distributions = chunk.angular_distributions

            d = distributions[0]
            self.assertAlmostEqual( 1e-5, d.E )
            self.assertAlmostEqual( 1e-5, d.incident_energy )
            self.assertEqual( 2, d.NP )
            self.assertEqual( 1, d.NR )
            self.assertEqual( 1, len( d.boundaries ) )
            self.assertEqual( 1, len( d.interpolants ) )
            self.assertEqual( 2, d.boundaries[0] )
            self.assertEqual( 2, d.interpolants[0] )
            self.assertEqual( 2, len( d.cosines ) )
            self.assertAlmostEqual( -1.0 , d.cosines[0] )
            self.assertAlmostEqual( 1.0, d.cosines[1] )
            self.assertEqual( 2, len( d.probabilities ) )
            self.assertAlmostEqual( 0.5 , d.probabilities[0] )
            self.assertAlmostEqual( 0.5, d.probabilities[1] )

            d = distributions[1]
            self.assertAlmostEqual( 2e+7, d.E )
            self.assertAlmostEqual( 2e+7, d.incident_energy )
            self.assertEqual( 3, d.NP )
            self.assertEqual( 1, d.NR )
            self.assertEqual( 1, len( d.boundaries ) )
            self.assertEqual( 1, len( d.interpolants ) )
            self.assertEqual( 3, d.boundaries[0] )
            self.assertEqual( 2, d.interpolants[0] )
            self.assertEqual( 3, len( d.cosines ) )
            self.assertAlmostEqual( -1.0 , d.cosines[0] )
            self.assertAlmostEqual( 0.0, d.cosines[1] )
            self.assertAlmostEqual( 1.0, d.cosines[2] )
            self.assertEqual( 3, len( d.probabilities ) )
            self.assertAlmostEqual( 0.0 , d.probabilities[0] )
            self.assertAlmostEqual( 1.0, d.probabilities[1] )
            self.assertAlmostEqual( 0.0, d.probabilities[2] )

            self.assertEqual( 8, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 14, 2 ) )

        # the data is given explicitly
        chunk = TabulatedDistributions(
                  energy = 1.0, level = 2.0,
                  boundaries = [ 2 ], interpolants = [ 1 ],
                  distributions = [ TabulatedDistribution( 1e-5, [ 2 ], [ 2 ], [ -1.0, 1.0 ], [ 0.5, 0.5 ] ),
                                    TabulatedDistribution( 2e+7, [ 3 ], [ 2 ], [ -1.0, 0.0, 1.0 ], [ 0.0, 1.0, 0.0 ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = TabulatedDistributions.from_string( self.chunk, 9228, 14, 2 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = TabulatedDistributions( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = TabulatedDistributions(
                      energy = 1.0, level = 2.0,
                      boundaries = [ 2, 4 ], interpolants = [ 1 ],
                      distributions = [ TabulatedDistribution( 1e-5, [ 2 ], [ 2 ], [ -1.0, 1.0 ], [ 0.5, 0.5 ] ),
                                        TabulatedDistribution( 2e+7, [ 3 ], [ 2 ], [ -1.0, 0.0, 1.0 ], [ 0.0, 1.0, 0.0 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedDistributions(
                      energy = 1.0, level = 2.0,
                      boundaries = [ 2 ], interpolants = [ 1, 2 ],
                      distributions = [ TabulatedDistribution( 1e-5, [ 2 ], [ 2 ], [ -1.0, 1.0 ], [ 0.5, 0.5 ] ),
                                        TabulatedDistribution( 2e+7, [ 3 ], [ 2 ], [ -1.0, 0.0, 1.0 ], [ 0.0, 1.0, 0.0 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedDistributions(
                      energy = 1.0, level = 2.0,
                      boundaries = [ 2 ], interpolants = [ 1 ],
                      distributions = [ TabulatedDistribution( 1e-5, [ 2 ], [ 2 ], [ -1.0, 1.0 ], [ 0.5, 0.5 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedDistributions.from_string( self.invalid, 9228, 14, 2 )

if __name__ == '__main__' :

    unittest.main()
