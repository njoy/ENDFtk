# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF26 import Multiplicity
from ENDFtk.MF26 import ReactionProduct
from ENDFtk.MF26 import ContinuumEnergyAngle
from ENDFtk.MF26.LAW1 import LegendreCoefficients

class Test_ENDFtk_MF26_ReactionProduct( unittest.TestCase ) :
    """Unit test for the ReactionProduct class."""

    chunk_law1 = ( ' 1.000000+3 9.992414-1          0          1          1          2 10026525     \n'
                   '          2          4                                             10026525     \n'
                   ' 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n'
                   ' 0.000000+0 0.000000+0          1          2          1          2 10026525     \n'
                   '          2          1                                             10026525     \n'
                   ' 0.000000+0 1.000000+1          0          0          4          2 10026525     \n'
                   ' 1.000000-1 2.139400+0 1.000000+1 2.122450-2                       10026525     \n'
                   ' 0.000000+0 1.00000+11          0          0          4          2 10026525     \n'
                   ' 1.000000-1 1.848230+0 1.00000+11 8.766410-3                       10026525     \n' )

    chunk_law2 = ( ' 1.000000+3 9.992414-1          0          2          1          2 10026525     \n'
                   '          2          4                                             10026525     \n'
                   ' 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n'
                   ' 0.000000+0 0.000000+0          0          0          1          2 10026525     \n'
                   '          2          1                                             10026525     \n'
                   ' 0.000000+0 1.000000+1         12          0          4          2 10026525     \n'
                   '-1.000000+0 5.000000-1 1.000000+0 5.000000-1                       10026525     \n'
                   ' 0.000000+0 1.00000+11         12          0          4          2 10026525     \n'
                   '-1.000000+0 7.500000-1 1.000000+0 2.500000-1                       10026525     \n' )

    chunk_law8 = ( ' 1.100000+1 5.438673-4          0          8          1          2 10026525     \n'
                   '          2          2                                             10026525     \n'
                   ' 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n'
                   ' 0.000000+0 0.000000+0          0          0          1          2 10026525     \n'
                   '          2          2                                             10026525     \n'
                   ' 1.000000+1 1.000000-5 1.00000+11 2.000000+4                       10026525     \n' )

    invalid = ( ' 1.100000+1 5.438673-4          0          3          1          2 10026525     \n'
                '          2          2                                             10026525     \n'
                ' 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n'
                ' 0.000000+0 0.000000+0          0          0          1          2 10026525     \n'
                '          2          2                                             10026525     \n'
                ' 1.000000+1 1.000000-5 1.00000+11 2.000000+4                       10026525     \n' )

    def test_component( self ) :

        def verify_chunk_law1( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1000., chunk.ZAP )
            self.assertAlmostEqual( 0.9992414, chunk.AWI )
            self.assertEqual( 1, chunk.LAW )

            self.assertAlmostEqual( 1000., chunk.multiplicity.ZAP )
            self.assertAlmostEqual( 0.9992414, chunk.multiplicity.AWI )
            self.assertEqual( 1, chunk.multiplicity.LAW )

            self.assertEqual( 2, chunk.multiplicity.NP )
            self.assertEqual( 1, chunk.multiplicity.NR )
            self.assertEqual( 1, len( chunk.multiplicity.interpolants ) )
            self.assertEqual( 1, len( chunk.multiplicity.boundaries ) )
            self.assertEqual( 4, chunk.multiplicity.interpolants[0] )
            self.assertEqual( 2, chunk.multiplicity.boundaries[0] )
            self.assertEqual( 2, len( chunk.multiplicity.energies ) )
            self.assertEqual( 2, len( chunk.multiplicity.multiplicities ) )
            self.assertAlmostEqual( 10., chunk.multiplicity.energies[0] )
            self.assertAlmostEqual( 1.e+11, chunk.multiplicity.energies[1] )
            self.assertAlmostEqual( 1., chunk.multiplicity.multiplicities[0] )
            self.assertAlmostEqual( 1., chunk.multiplicity.multiplicities[1] )

            law = chunk.distribution

            self.assertEqual( 1, law.LAW )
            self.assertEqual( 2, law.NE )
            self.assertEqual( 1, law.NR )
            self.assertEqual( 1, len( law.interpolants ) )
            self.assertEqual( 1, len( law.boundaries ) )
            self.assertEqual( 1, law.interpolants[0] )
            self.assertEqual( 2, law.boundaries[0] )

            energies = law.distributions

            self.assertEqual( 10., energies[0].incident_energy )
            self.assertEqual( 0, energies[0].ND )
            self.assertEqual( 0, energies[0].NA )
            self.assertEqual( 4, energies[0].NW )
            self.assertEqual( 2, energies[0].NEP )
            self.assertEqual( 2, len( energies[0].energies ) )
            self.assertAlmostEqual( .1, energies[0].energies[0] )
            self.assertAlmostEqual( 10., energies[0].energies[1] )
            self.assertEqual( 2, len( energies[0].coefficients ) )
            self.assertAlmostEqual( 2.1394, energies[0].coefficients[0][0] )
            self.assertAlmostEqual( 2.122450e-2, energies[0].coefficients[1][0] )
            self.assertEqual( 2, len( energies[0].total_emission_probabilities ) )
            self.assertAlmostEqual( 2.1394, energies[0].total_emission_probabilities[0] )
            self.assertAlmostEqual( 2.12245e-2, energies[0].total_emission_probabilities[1] )

            self.assertEqual( 1e+11, energies[1].incident_energy )
            self.assertEqual( 1, energies[1].LANG )
            self.assertEqual( 0, energies[1].ND )
            self.assertEqual( 0, energies[1].NA )
            self.assertEqual( 4, energies[1].NW )
            self.assertEqual( 2, energies[1].NEP )
            self.assertEqual( 2, len( energies[1].energies ) )
            self.assertAlmostEqual( .1, energies[1].energies[0] )
            self.assertAlmostEqual( 1e+11, energies[1].energies[1] )
            self.assertEqual( 2, len( energies[1].coefficients ) )
            self.assertAlmostEqual( 1.84823, energies[1].coefficients[0][0] )
            self.assertAlmostEqual( 8.76641e-3, energies[1].coefficients[1][0] )
            self.assertEqual( 2, len( energies[1].total_emission_probabilities ) )
            self.assertAlmostEqual( 1.84823, energies[1].total_emission_probabilities[0] )
            self.assertAlmostEqual( 8.76641e-3, energies[1].total_emission_probabilities[1] )

            self.assertEqual( 9, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_law1, chunk.to_string( 100, 26, 525 ) )

        # the data is given explicitly
        multiplicity = Multiplicity( zap = 1000., awi = 0.9992414, law = 1,
                                     boundaries = [ 2 ], interpolants = [ 4 ],
                                     energies = [ 10., 1e+11 ],
                                     multiplicities = [ 1., 1. ] )
        distribution = ContinuumEnergyAngle(
            lep = 2, boundaries = [ 2 ], interpolants = [ 1 ],
            distributions =
            [ LegendreCoefficients( 10., 0, 0, [ .1, 10. ],
                                    [ [ 2.1394 ], [  .0212245 ] ] ),
              LegendreCoefficients( 1e+11, 0, 0, [ .1, 1e+11 ],
                                    [ [ 1.84823 ], [ .00876641 ] ] ) ] )

        chunk = ReactionProduct( multiplicity = multiplicity,
                                 distribution = distribution )

        verify_chunk_law1( self, chunk )

        # the data is read from a string
        chunk = ReactionProduct.from_string( self.chunk_law1, 100, 26, 525 )

        verify_chunk_law1( self, chunk )

        # the data is copied
        copy = ReactionProduct( chunk )

        verify_chunk_law1( self, copy )

        # TODO add other law tests?

    def test_failures( self ) :

        print( '\n' )

        # wrong law in multiplicity
        with self.assertRaises( Exception ) :

            multiplicity = Multiplicity( zap = 1000., awi = 0.9992414, law = 2,
                                         boundaries = [ 2 ], interpolants = [ 4 ],
                                         energies = [ 10., 1e+11 ],
                                         multiplicities = [ 1., 1. ] )
            distribution = ContinuumEnergyAngle(
                lep = 2, boundaries = [ 2 ], interpolants = [ 1 ],
                distributions =
                [ LegendreCoefficients( 10., 0, 0, [ .1, 10. ],
                                        [ [ 2.1394 ], [  .0212245 ] ] ),
                  LegendreCoefficients( 1e+11, 0, 0, [ .1, 1e+11 ],
                                        [ [ 1.84823 ], [ .00876641 ] ] ) ] )

            chunk = ReactionProduct( multiplicity = multiplicity,
                                     distribution = distribution )

        with self.assertRaises( Exception ) :

            chunk = ReactionProduct.from_string( self.invalid, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
