# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF5 import PartialDistribution
from ENDFtk.MF5 import Probability
from ENDFtk.MF5 import PartialDistribution
from ENDFtk.MF5 import Probability
from ENDFtk.MF5 import TabulatedSpectrum
from ENDFtk.MF5 import GeneralEvaporationSpectrum
from ENDFtk.MF5 import MaxwellianFissionSpectrum
from ENDFtk.MF5 import EvaporationSpectrum
from ENDFtk.MF5 import WattSpectrum
from ENDFtk.MF5 import MadlandNixSpectrum
from ENDFtk.MF5 import OutgoingEnergyDistribution
from ENDFtk.MF5 import Parameter
from ENDFtk.MF5 import EffectiveTemperature
from ENDFtk.MF5 import DistributionFunction

class Test_ENDFtk_MF5_PartialDistribution( unittest.TestCase ) :
    """Unit test for the PartialDistribution class."""

    chunk_lf1 = ( ' 0.000000+0 0.000000+0          0          1          1          29437 5 18     \n'
                  '          2          2                                            9437 5 18     \n'
                  ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9437 5 18     \n'
                  ' 0.000000+0 0.000000+0          0          0          1          29437 5 18     \n'
                  '          2          4                                            9437 5 18     \n'
                  ' 0.000000+0 1.000000-5          0          0          1          39437 5 18     \n'
                  '          3          2                                            9437 5 18     \n'
                  ' 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-99437 5 18     \n'
                  ' 0.000000+0 3.000000+7          0          0          1          49437 5 18     \n'
                  '          4          2                                            9437 5 18     \n'
                  ' 0.000000+0 0.000000+0 1.000000+1 1.733405-9 1.100000+1 1.818010-99437 5 18     \n'
                  ' 3.000000+7 1.898849-9                                            9437 5 18     \n' )

    chunk_lf5 =( '-3.000000+7 0.000000+0          0          5          1          29443 5455     \n'
                 '          2          2                                            9443 5455     \n'
                 ' 1.000000-5 1.804944-2 3.000000+7 1.804944-2                      9443 5455     \n'
                 ' 0.000000+0 0.000000+0          0          0          1          29443 5455     \n'
                 '          2          2                                            9443 5455     \n'
                 ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9443 5455     \n'
                 ' 0.000000+0 0.000000+0          0          0          1          69443 5455     \n'
                 '          6          1                                            9443 5455     \n'
                 ' 0.000000+0 1.533738-7 1.000000+4 1.378483-6 2.000000+4 1.550360-69443 5455     \n'
                 ' 1.800000+6 7.90779-31 1.810000+6 0.000000+0 1.820000+6 0.000000+09443 5455     \n' )

    chunk_lf7 = ( '-3.000000+7 0.000000+0          0          7          1          29455 5 18     \n'
                  '          2          2                                            9455 5 18     \n'
                  ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9455 5 18     \n'
                  ' 0.000000+0 0.000000+0          0          0          1          39455 5 18     \n'
                  '          3          2                                            9455 5 18     \n'
                  ' 1.000000-5 1.365200+6 5.000000+5 1.374800+6 3.000000+7 1.691200+69455 5 18     \n' )

    chunk_lf9 = ( ' 1.789920+7 0.000000+0          0          9          1          29237 5 37     \n'
                  '          2          2                                            9237 5 37     \n'
                  ' 1.789920+7 1.000000+0 2.000000+7 1.000000+0                      9237 5 37     \n'
                  ' 0.000000+0 0.000000+0          0          0          1          49237 5 37     \n'
                  '          4          2                                            9237 5 37     \n'
                  ' 1.789920+7 1.009900+5 1.800000+7 1.009900+5 1.900000+7 1.129200+59237 5 37     \n'
                  ' 2.000000+7 1.614300+5                                            9237 5 37     \n' )

    chunk_lf11 = ( '-3.000000+7 0.000000+0          0         11          1          29222 5 18     \n'
                   '          2          2                                            9222 5 18     \n'
                   ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9222 5 18     \n'
                   ' 0.000000+0 0.000000+0          0          0          1          39222 5 18     \n'
                   '          3          2                                            9222 5 18     \n'
                   ' 1.000000-5 9.770000+5 1.500000+6 1.000000+6 3.000000+7 1.060000+69222 5 18     \n'
                   ' 0.000000+0 0.000000+0          0          0          1          59222 5 18     \n'
                   '          5          2                                            9222 5 18     \n'
                   ' 1.000000-5 2.546000-6 1.500000+6 2.546000-6 1.000000+7 2.474000-69222 5 18     \n'
                   ' 1.220000+7 2.612000-6 3.000000+7 2.620000-6                      9222 5 18     \n' )

    chunk_lf12 = ( ' 0.000000+0 0.000000+0          0         12          1          29543 5 18     \n'
                   '          2          2                                            9543 5 18     \n'
                   ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9543 5 18     \n'
                   ' 1.029979+6 5.467297+5          0          0          1          49543 5 18     \n'
                   '          4          5                                            9543 5 18     \n'
                   ' 1.000000-5 1.092064+6 5.000001+5 1.101483+6 1.400000+7 1.129269+69543 5 18     \n'
                   ' 3.000000+7 1.182884+6                                            9543 5 18     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          2          1          29222 5 18     \n'
                '          2          2                                            9222 5 18     \n'
                ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9222 5 18     \n'
                ' 0.000000+0 0.000000+0          0          0          1          39222 5 18     \n'
                '          3          2                                            9222 5 18     \n'
                ' 1.000000-5 9.770000+5 1.500000+6 1.000000+6 3.000000+7 1.060000+69222 5 18     \n'
                ' 0.000000+0 0.000000+0          0          0          1          59222 5 18     \n'
                '          5          2                                            9222 5 18     \n'
                ' 1.000000-5 2.546000-6 1.500000+6 2.546000-6 1.000000+7 2.474000-69222 5 18     \n'
                ' 1.220000+7 2.612000-6 3.000000+7 2.620000-6                      9222 5 18     \n' )

    def test_component( self ) :

        def verify_chunk_lf1( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 0.0, chunk.U )
            self.assertAlmostEqual( 0.0, chunk.energy_limit_constant )

            p = chunk.probability

            self.assertEqual( 1, p.LF )
            self.assertEqual( 1, p.LAW )

            self.assertEqual( 2, p.NP )
            self.assertEqual( 1, p.NR )
            self.assertEqual( 1, len( p.interpolants ) )
            self.assertEqual( 1, len( p.boundaries ) )
            self.assertEqual( 2, p.interpolants[0] )
            self.assertEqual( 2, p.boundaries[0] )
            self.assertEqual( 2, len( p.E ) )
            self.assertEqual( 2, len( p.energies ) )
            self.assertEqual( 2, len( p.P ) )
            self.assertEqual( 2, len( p.probabilities ) )
            self.assertAlmostEqual( 1e-5, p.E[0] )
            self.assertAlmostEqual( 3e+7, p.E[1] )
            self.assertAlmostEqual( 1e-5, p.energies[0] )
            self.assertAlmostEqual( 3e+7, p.energies[1] )
            self.assertAlmostEqual( 1., p.P[0] )
            self.assertAlmostEqual( 1., p.P[1] )
            self.assertAlmostEqual( 1., p.probabilities[0] )
            self.assertAlmostEqual( 1., p.probabilities[1] )

            d = chunk.distribution

            self.assertEqual( True, isinstance( d, TabulatedSpectrum ) )

            self.assertEqual( 1, d.NR )
            self.assertEqual( 2, d.NE )
            self.assertEqual( 1, len( d.boundaries ) )
            self.assertEqual( 2, d.boundaries[0] )
            self.assertEqual( 1, len( d.interpolants ) )
            self.assertEqual( 4, d.interpolants[0] )

            self.assertEqual( 2, len( d.incident_energies ) )
            self.assertAlmostEqual( 1e-5, d.incident_energies[0] )
            self.assertAlmostEqual( 3e+7, d.incident_energies[1] )

            value = d.outgoing_distributions[0]
            self.assertAlmostEqual( 1e-5, value.incident_energy )
            self.assertEqual( 3, value.NP )
            self.assertEqual( 1, value.NR )
            self.assertEqual( 1, len( value.interpolants ) )
            self.assertEqual( 1, len( value.boundaries ) )
            self.assertEqual( 2, value.interpolants[0] )
            self.assertEqual( 3, value.boundaries[0] )
            self.assertEqual( 3, len( value.EP ) )
            self.assertEqual( 3, len( value.outgoing_energies ) )
            self.assertEqual( 3, len( value.G ) )
            self.assertEqual( 3, len( value.probabilities ) )
            self.assertAlmostEqual( 0.0, value.EP[0] )
            self.assertAlmostEqual( 1e+5, value.EP[1] )
            self.assertAlmostEqual( 3e+7, value.EP[2] )
            self.assertAlmostEqual( 0.0, value.outgoing_energies[0] )
            self.assertAlmostEqual( 1e+5, value.outgoing_energies[1] )
            self.assertAlmostEqual( 3e+7, value.outgoing_energies[2] )
            self.assertAlmostEqual( 0., value.G[0] )
            self.assertAlmostEqual( 1.757570e-9, value.G[1] )
            self.assertAlmostEqual( 1.843350e-9, value.G[2] )
            self.assertAlmostEqual( 0., value.probabilities[0] )
            self.assertAlmostEqual( 1.757570e-9, value.probabilities[1] )
            self.assertAlmostEqual( 1.843350e-9, value.probabilities[2] )

            value = d.outgoing_distributions[1]
            self.assertAlmostEqual( 3e+7, value.incident_energy )
            self.assertEqual( 4, value.NP )
            self.assertEqual( 1, value.NR )
            self.assertEqual( 1, len( value.interpolants ) )
            self.assertEqual( 1, len( value.boundaries ) )
            self.assertEqual( 2, value.interpolants[0] )
            self.assertEqual( 4, value.boundaries[0] )
            self.assertEqual( 4, len( value.EP ) )
            self.assertEqual( 4, len( value.outgoing_energies ) )
            self.assertEqual( 4, len( value.G ) )
            self.assertEqual( 4, len( value.probabilities ) )
            self.assertAlmostEqual( 0.0, value.EP[0] )
            self.assertAlmostEqual( 10., value.EP[1] )
            self.assertAlmostEqual( 11., value.EP[2] )
            self.assertAlmostEqual( 3e+7, value.EP[3] )
            self.assertAlmostEqual( 0.0, value.outgoing_energies[0] )
            self.assertAlmostEqual( 10., value.outgoing_energies[1] )
            self.assertAlmostEqual( 11., value.outgoing_energies[2] )
            self.assertAlmostEqual( 3e+7, value.outgoing_energies[3] )
            self.assertAlmostEqual( 0., value.G[0] )
            self.assertAlmostEqual( 1.733405e-9, value.G[1] )
            self.assertAlmostEqual( 1.818010e-9, value.G[2] )
            self.assertAlmostEqual( 1.898849e-9, value.G[3] )
            self.assertAlmostEqual( 0., value.probabilities[0] )
            self.assertAlmostEqual( 1.733405e-9, value.probabilities[1] )
            self.assertAlmostEqual( 1.818010e-9, value.probabilities[2] )
            self.assertAlmostEqual( 1.898849e-9, value.probabilities[3] )

            self.assertEqual( 12, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lf1, chunk.to_string( 9437, 5, 18 ) )

        def verify_chunk_lf5( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -3e+7, chunk.U )
            self.assertAlmostEqual( -3e+7, chunk.energy_limit_constant )

            p = chunk.probability

            self.assertEqual( 5, p.LF )
            self.assertEqual( 5, p.LAW )

            self.assertEqual( 2, p.NP )
            self.assertEqual( 1, p.NR )
            self.assertEqual( 1, len( p.interpolants ) )
            self.assertEqual( 1, len( p.boundaries ) )
            self.assertEqual( 2, p.interpolants[0] )
            self.assertEqual( 2, p.boundaries[0] )
            self.assertEqual( 2, len( p.E ) )
            self.assertEqual( 2, len( p.energies ) )
            self.assertEqual( 2, len( p.P ) )
            self.assertEqual( 2, len( p.probabilities ) )
            self.assertAlmostEqual( 1e-5, p.E[0] )
            self.assertAlmostEqual( 3e+7, p.E[1] )
            self.assertAlmostEqual( 1e-5, p.energies[0] )
            self.assertAlmostEqual( 3e+7, p.energies[1] )
            self.assertAlmostEqual( 1.804944e-2, p.P[0] )
            self.assertAlmostEqual( 1.804944e-2, p.P[1] )
            self.assertAlmostEqual( 1.804944e-2, p.probabilities[0] )
            self.assertAlmostEqual( 1.804944e-2, p.probabilities[1] )

            d = chunk.distribution

            self.assertEqual( True, isinstance( d, GeneralEvaporationSpectrum ) )

            self.assertEqual( 5, d.LF )
            self.assertEqual( 5, d.LAW )

            t = d.effective_temperature
            self.assertEqual( 2, t.NP )
            self.assertEqual( 1, t.NR )
            self.assertEqual( 1, len( t.interpolants ) )
            self.assertEqual( 1, len( t.boundaries ) )
            self.assertEqual( 2, t.interpolants[0] )
            self.assertEqual( 2, t.boundaries[0] )
            self.assertEqual( 2, len( t.E ) )
            self.assertEqual( 2, len( t.energies ) )
            self.assertEqual( 2, len( t.thetas ) )
            self.assertAlmostEqual( 1e-5, t.E[0] )
            self.assertAlmostEqual( 3e+7, t.E[1] )
            self.assertAlmostEqual( 1e-5, t.energies[0] )
            self.assertAlmostEqual( 3e+7, t.energies[1] )
            self.assertAlmostEqual( 1.0, t.thetas[0] )
            self.assertAlmostEqual( 1.0, t.thetas[1] )

            df = d.distribution_function
            self.assertEqual( 6, df.NP )
            self.assertEqual( 1, df.NR )
            self.assertEqual( 1, len( df.interpolants ) )
            self.assertEqual( 1, len( df.boundaries ) )
            self.assertEqual( 1, df.interpolants[0] )
            self.assertEqual( 6, df.boundaries[0] )
            self.assertEqual( 6, len( df.X ) )
            self.assertEqual( 6, len( df.G ) )
            self.assertAlmostEqual( 0.0, df.X[0] )
            self.assertAlmostEqual( 1e+4, df.X[1] )
            self.assertAlmostEqual( 2e+4, df.X[2] )
            self.assertAlmostEqual( 1.8e+6, df.X[3] )
            self.assertAlmostEqual( 1.81e+6, df.X[4] )
            self.assertAlmostEqual( 1.82e+6, df.X[5] )
            self.assertAlmostEqual( 1.533738e-7, df.G[0] )
            self.assertAlmostEqual( 1.378483e-6, df.G[1] )
            self.assertAlmostEqual( 1.550360e-6, df.G[2] )
            self.assertAlmostEqual( 7.90779e-31, df.G[3] )
            self.assertAlmostEqual( 0.0, df.G[4] )
            self.assertAlmostEqual( 0.0, df.G[5] )

            self.assertEqual( 10, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lf5, chunk.to_string( 9443, 5, 455 ) )

        def verify_chunk_lf7( self, chunk ) :

            # verify content
            self.assertEqual( -3e+7, chunk.U )
            self.assertEqual( -3e+7, chunk.energy_limit_constant )

            p = chunk.probability

            self.assertEqual( 7, p.LF )
            self.assertEqual( 7, p.LAW )

            self.assertEqual( 2, p.NP )
            self.assertEqual( 1, p.NR )
            self.assertEqual( 1, len( p.interpolants ) )
            self.assertEqual( 1, len( p.boundaries ) )
            self.assertEqual( 2, p.interpolants[0] )
            self.assertEqual( 2, p.boundaries[0] )
            self.assertEqual( 2, len( p.E ) )
            self.assertEqual( 2, len( p.energies ) )
            self.assertEqual( 2, len( p.P ) )
            self.assertEqual( 2, len( p.probabilities ) )
            self.assertAlmostEqual( 1e-5, p.E[0] )
            self.assertAlmostEqual( 3e+7, p.E[1] )
            self.assertAlmostEqual( 1e-5, p.energies[0] )
            self.assertAlmostEqual( 3e+7, p.energies[1] )
            self.assertAlmostEqual( 1., p.P[0] )
            self.assertAlmostEqual( 1., p.P[1] )
            self.assertAlmostEqual( 1., p.probabilities[0] )
            self.assertAlmostEqual( 1., p.probabilities[1] )

            d = chunk.distribution

            self.assertEqual( True, isinstance( d, MaxwellianFissionSpectrum ) )

            self.assertEqual( 7, d.LF )
            self.assertEqual( 7, d.LAW )
            self.assertEqual( 3, d.NP )
            self.assertEqual( 1, d.NR )
            self.assertEqual( 1, len( d.interpolants ) )
            self.assertEqual( 1, len( d.boundaries ) )
            self.assertEqual( 2, d.interpolants[0] )
            self.assertEqual( 3, d.boundaries[0] )
            self.assertEqual( 3, len( d.E ) )
            self.assertEqual( 3, len( d.energies ) )
            self.assertEqual( 3, len( d.thetas ) )
            self.assertAlmostEqual( 1e-5, d.E[0] )
            self.assertAlmostEqual( 5e+5, d.E[1] )
            self.assertAlmostEqual( 3e+7, d.E[2] )
            self.assertAlmostEqual( 1e-5, d.energies[0] )
            self.assertAlmostEqual( 5e+5, d.energies[1] )
            self.assertAlmostEqual( 3e+7, d.energies[2] )
            self.assertAlmostEqual( 1.3652e+6, d.thetas[0] )
            self.assertAlmostEqual( 1.3748e+6, d.thetas[1] )
            self.assertAlmostEqual( 1.6912e+6, d.thetas[2] )

            self.assertEqual( 6, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lf7, chunk.to_string( 9455, 5, 18 ) )

        def verify_chunk_lf9( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1.789920e+7, chunk.U )
            self.assertAlmostEqual( 1.789920e+7, chunk.energy_limit_constant )

            p = chunk.probability

            self.assertEqual( 9, p.LF )
            self.assertEqual( 9, p.LAW )

            self.assertEqual( 2, p.NP )
            self.assertEqual( 1, p.NR )
            self.assertEqual( 1, len( p.interpolants ) )
            self.assertEqual( 1, len( p.boundaries ) )
            self.assertEqual( 2, p.interpolants[0] )
            self.assertEqual( 2, p.boundaries[0] )
            self.assertEqual( 2, len( p.E ) )
            self.assertEqual( 2, len( p.energies ) )
            self.assertEqual( 2, len( p.P ) )
            self.assertEqual( 2, len( p.probabilities ) )
            self.assertAlmostEqual( 1.789920e+7, p.E[0] )
            self.assertAlmostEqual( 2e+7, p.E[1] )
            self.assertAlmostEqual( 1.789920e+7, p.energies[0] )
            self.assertAlmostEqual( 2e+7, p.energies[1] )
            self.assertAlmostEqual( 1.0, p.P[0] )
            self.assertAlmostEqual( 1.0, p.P[1] )
            self.assertAlmostEqual( 1.0, p.probabilities[0] )
            self.assertAlmostEqual( 1.0, p.probabilities[1] )

            d = chunk.distribution

            self.assertEqual( True, isinstance( d, EvaporationSpectrum ) )

            self.assertEqual( 9, d.LF )
            self.assertEqual( 9, d.LAW )
            self.assertEqual( 4, d.NP )
            self.assertEqual( 1, d.NR )
            self.assertEqual( 1, len( d.interpolants ) )
            self.assertEqual( 1, len( d.boundaries ) )
            self.assertEqual( 2, d.interpolants[0] )
            self.assertEqual( 4, d.boundaries[0] )
            self.assertEqual( 4, len( d.E ) )
            self.assertEqual( 4, len( d.energies ) )
            self.assertEqual( 4, len( d.thetas ) )
            self.assertAlmostEqual( 1.789920e+7, d.E[0] )
            self.assertAlmostEqual( 1.8e+7, d.E[1] )
            self.assertAlmostEqual( 1.9e+7, d.E[2] )
            self.assertAlmostEqual( 2e+7, d.E[3] )
            self.assertAlmostEqual( 1.789920e+7, d.energies[0] )
            self.assertAlmostEqual( 1.8e+7, d.energies[1] )
            self.assertAlmostEqual( 1.9e+7, d.energies[2] )
            self.assertAlmostEqual( 2e+7, d.energies[3] )
            self.assertAlmostEqual( 1.0099e+5, d.thetas[0] )
            self.assertAlmostEqual( 1.0099e+5, d.thetas[1] )
            self.assertAlmostEqual( 1.1292e+5, d.thetas[2] )
            self.assertAlmostEqual( 1.6143e+5, d.thetas[3] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lf9, chunk.to_string( 9237, 5, 37 ) )

        def verify_chunk_lf11( self, chunk ) :

            # verify content
            self.assertEqual( -3e+7, chunk.U )
            self.assertEqual( -3e+7, chunk.energy_limit_constant )

            p = chunk.probability

            self.assertEqual( 11, p.LF )
            self.assertEqual( 11, p.LAW )

            self.assertEqual( 2, p.NP )
            self.assertEqual( 1, p.NR )
            self.assertEqual( 1, len( p.interpolants ) )
            self.assertEqual( 1, len( p.boundaries ) )
            self.assertEqual( 2, p.interpolants[0] )
            self.assertEqual( 2, p.boundaries[0] )
            self.assertEqual( 2, len( p.E ) )
            self.assertEqual( 2, len( p.energies ) )
            self.assertEqual( 2, len( p.P ) )
            self.assertEqual( 2, len( p.probabilities ) )
            self.assertAlmostEqual( 1e-5, p.E[0] )
            self.assertAlmostEqual( 3e+7, p.E[1] )
            self.assertAlmostEqual( 1e-5, p.energies[0] )
            self.assertAlmostEqual( 3e+7, p.energies[1] )
            self.assertAlmostEqual( 1., p.P[0] )
            self.assertAlmostEqual( 1., p.P[1] )
            self.assertAlmostEqual( 1., p.probabilities[0] )
            self.assertAlmostEqual( 1., p.probabilities[1] )

            d = chunk.distribution

            self.assertEqual( True, isinstance( d, WattSpectrum ) )

            self.assertEqual( 11, d.LF )
            self.assertEqual( 11, d.LAW )

            self.assertEqual( 3, d.a.NP )
            self.assertEqual( 1, d.a.NR )
            self.assertEqual( 1, len( d.a.interpolants ) )
            self.assertEqual( 1, len( d.a.boundaries ) )
            self.assertEqual( 2, d.a.interpolants[0] )
            self.assertEqual( 3, d.a.boundaries[0] )
            self.assertEqual( 3, len( d.a.E ) )
            self.assertEqual( 3, len( d.a.energies ) )
            self.assertAlmostEqual( 1e-5, d.a.E[0] )
            self.assertAlmostEqual( 1.5e+6, d.a.E[1] )
            self.assertAlmostEqual( 3e+7, d.a.E[2] )
            self.assertAlmostEqual( 1e-5, d.a.energies[0] )
            self.assertAlmostEqual( 1.5e+6, d.a.energies[1] )
            self.assertAlmostEqual( 3e+7, d.a.energies[2] )

            self.assertEqual( 5, d.b.NP )
            self.assertEqual( 1, d.b.NR )
            self.assertEqual( 1, len( d.b.interpolants ) )
            self.assertEqual( 1, len( d.b.boundaries ) )
            self.assertEqual( 2, d.b.interpolants[0] )
            self.assertEqual( 5, d.b.boundaries[0] )
            self.assertEqual( 5, len( d.b.E ) )
            self.assertEqual( 5, len( d.b.energies ) )
            self.assertAlmostEqual( 1e-5, d.b.E[0] )
            self.assertAlmostEqual( 1.5e+6, d.b.E[1] )
            self.assertAlmostEqual( 1e+7, d.b.E[2] )
            self.assertAlmostEqual( 1.22e+7, d.b.E[3] )
            self.assertAlmostEqual( 3e+7, d.b.E[4] )
            self.assertAlmostEqual( 1e-5, d.b.energies[0] )
            self.assertAlmostEqual( 1.5e+6, d.b.energies[1] )
            self.assertAlmostEqual( 1e+7, d.b.energies[2] )
            self.assertAlmostEqual( 1.22e+7, d.b.energies[3] )
            self.assertAlmostEqual( 3e+7, d.b.energies[4] )

            self.assertEqual( 10, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lf11, chunk.to_string( 9222, 5, 18 ) )

        def verify_chunk_lf12( self, chunk ) :

            # verify content
            self.assertEqual( 0.0, chunk.U )
            self.assertEqual( 0.0, chunk.energy_limit_constant )

            p = chunk.probability

            self.assertEqual( 12, p.LF )
            self.assertEqual( 12, p.LAW )

            self.assertEqual( 2, p.NP )
            self.assertEqual( 1, p.NR )
            self.assertEqual( 1, len( p.interpolants ) )
            self.assertEqual( 1, len( p.boundaries ) )
            self.assertEqual( 2, p.interpolants[0] )
            self.assertEqual( 2, p.boundaries[0] )
            self.assertEqual( 2, len( p.E ) )
            self.assertEqual( 2, len( p.energies ) )
            self.assertEqual( 2, len( p.P ) )
            self.assertEqual( 2, len( p.probabilities ) )
            self.assertAlmostEqual( 1e-5, p.E[0] )
            self.assertAlmostEqual( 3e+7, p.E[1] )
            self.assertAlmostEqual( 1e-5, p.energies[0] )
            self.assertAlmostEqual( 3e+7, p.energies[1] )
            self.assertAlmostEqual( 1., p.P[0] )
            self.assertAlmostEqual( 1., p.P[1] )
            self.assertAlmostEqual( 1., p.probabilities[0] )
            self.assertAlmostEqual( 1., p.probabilities[1] )

            d = chunk.distribution

            self.assertEqual( True, isinstance( d, MadlandNixSpectrum ) )

            self.assertEqual( 12, d.LF )
            self.assertEqual( 12, d.LAW )

            self.assertAlmostEqual( 1.029979e+6, d.EFL )
            self.assertAlmostEqual( 1.029979e+6, d.light_fragment_energy )
            self.assertAlmostEqual( 5.467297e+5, d.EFH )
            self.assertAlmostEqual( 5.467297e+5, d.heavy_fragment_energy )

            self.assertEqual( 4, d.NP )
            self.assertEqual( 1, d.NR )
            self.assertEqual( 1, len( d.interpolants ) )
            self.assertEqual( 1, len( d.boundaries ) )
            self.assertEqual( 5, d.interpolants[0] )
            self.assertEqual( 4, d.boundaries[0] )
            self.assertEqual( 4, len( d.E ) )
            self.assertEqual( 4, len( d.energies ) )
            self.assertEqual( 4, len( d.TM ) )
            self.assertEqual( 4, len( d.maximum_temperature_values ) )
            self.assertAlmostEqual( 1e-5, d.E[0] )
            self.assertAlmostEqual( 5.000001e+5, d.E[1] )
            self.assertAlmostEqual( 1.4e+7, d.E[2] )
            self.assertAlmostEqual( 3.0e+7, d.E[3] )
            self.assertAlmostEqual( 1e-5, d.energies[0] )
            self.assertAlmostEqual( 5.000001e+5, d.energies[1] )
            self.assertAlmostEqual( 1.4e+7, d.energies[2] )
            self.assertAlmostEqual( 3.0e+7, d.energies[3] )
            self.assertAlmostEqual( 1.092064e+6, d.TM[0] )
            self.assertAlmostEqual( 1.101483e+6, d.TM[1] )
            self.assertAlmostEqual( 1.129269e+6, d.TM[2] )
            self.assertAlmostEqual( 1.182884e+6, d.TM[3] )
            self.assertAlmostEqual( 1.092064e+6, d.maximum_temperature_values[0] )
            self.assertAlmostEqual( 1.101483e+6, d.maximum_temperature_values[1] )
            self.assertAlmostEqual( 1.129269e+6, d.maximum_temperature_values[2] )
            self.assertAlmostEqual( 1.182884e+6, d.maximum_temperature_values[3] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lf12, chunk.to_string( 9543, 5, 18 ) )

        # the data is given explicitly for lf=1
        chunk = PartialDistribution(
                  probability = Probability( 1, [ 2 ], [ 2 ],
                                             [ 1e-5, 3e+7 ],
                                             [ 1.0, 1.0 ] ),
                  spectrum = TabulatedSpectrum(
                                 [ 2 ], [ 4 ],
                                 [ OutgoingEnergyDistribution(
                                       1e-5, [ 3 ], [ 2 ],
                                       [ 0.0, 1e+5, 3e+7 ],
                                       [ 0.0, 1.757570e-9, 1.843350e-9 ] ),
                                   OutgoingEnergyDistribution(
                                       3e+7, [ 4 ], [ 2 ],
                                       [ 0.0, 10., 11., 3e+7 ],
                                       [ 0.0, 1.733405e-9,
                                         1.818010e-9, 1.898849e-9 ] ) ] ) )

        verify_chunk_lf1( self, chunk )

        # the data is read from a string for lf=1
        chunk = PartialDistribution.from_string( self.chunk_lf1, 9437, 5, 18 )

        verify_chunk_lf1( self, chunk )

        # the data is copied for lf=1
        copy = PartialDistribution( chunk )

        verify_chunk_lf1( self, copy )

        # the data is given explicitly for lf=5
        chunk = PartialDistribution(
                  probability = Probability( 5, [ 2 ], [ 2 ],
                                                    [ 1e-5, 3e+7 ],
                                                    [ 1.804944e-2, 1.804944e-2 ], -3e+7 ),
                  spectrum = GeneralEvaporationSpectrum(
                                 EffectiveTemperature( [ 2 ], [ 2 ],
                                                       [ 1e-5, 3e+7 ], [ 1.0, 1.0 ] ),
                                 DistributionFunction( [ 6 ], [ 1 ],
                                                       [ 0.0, 1e+4, 2e+4,
                                                         1.8e+6, 1.81e+6, 1.82e+6 ],
                                                       [ 1.533738e-7, 1.378483e-6,
                                                         1.550360e-6, 7.90779e-31,
                                                         0.0, 0.0 ] ) ) )

        verify_chunk_lf5( self, chunk )

        # the data is read from a string for lf=5
        chunk = PartialDistribution.from_string( self.chunk_lf5, 9443, 5, 455 )

        verify_chunk_lf5( self, chunk )

        # the data is copied for lf=5
        copy = PartialDistribution( chunk )

        verify_chunk_lf5( self, copy )

        # the data is given explicitly for lf=7
        chunk = PartialDistribution(
                  probability = Probability( 7, [ 2 ], [ 2 ],
                                            [ 1e-5, 3e+7 ],
                                            [ 1.0, 1.0 ], -3e+7 ),
                  spectrum = MaxwellianFissionSpectrum( [ 3 ], [ 2 ],
                                                        [ 1e-5, 5e+5, 3e+7 ],
                                                        [ 1.3652e+6, 1.3748e+6,
                                                          1.6912e+6 ] ) )

        verify_chunk_lf7( self, chunk )

        # the data is read from a string for lf=5
        chunk = PartialDistribution.from_string( self.chunk_lf7, 9455, 5, 18 )

        verify_chunk_lf7( self, chunk )

        # the data is copied for lf=5
        copy = PartialDistribution( chunk )

        verify_chunk_lf7( self, copy )

        # the data is given explicitly for lf=9
        chunk = PartialDistribution(
                  probability = Probability( 9, [ 2 ], [ 2 ],
                                             [ 1.789920e+7, 2e+7 ],
                                             [ 1.0, 1.0 ], 1.789920e+7 ),
                  spectrum = EvaporationSpectrum( [ 4 ], [ 2 ],
                                                  [ 1.78992e+7, 1.8e+7,
                                                    1.9e+7, 2e+7 ],
                                                  [ 1.0099e+5, 1.0099e+5,
                                                    1.1292e+5, 1.6143e+5 ] ) )

        verify_chunk_lf9( self, chunk )

        # the data is read from a string for lf=9
        chunk = PartialDistribution.from_string( self.chunk_lf9, 9237, 5, 37 )

        verify_chunk_lf9( self, chunk )

        # the data is copied for lf=9
        copy = PartialDistribution( chunk )

        verify_chunk_lf9( self, copy )

        # the data is given explicitly for lf=11
        chunk = PartialDistribution(
                  probability = Probability( 11, [ 2 ], [ 2 ],
                                                     [ 1e-5, 3e+7 ],
                                                     [ 1.0, 1.0 ], -3e+7 ),
                  spectrum = WattSpectrum( Parameter( [3], [2],
                                                      [ 1e-5, 1.5e+6, 3e+7 ],
                                                      [ 9.77e+5, 1e+6, 1.06e+6 ] ),
                                           Parameter( [5], [2],
                                                      [ 1e-5, 1.5e+6, 1e+7,
                                                        1.22e+7, 3e+7 ],
                                                      [ 2.546e-6, 2.546e-6, 2.474e-6,
                                                        2.612e-6, 2.62e-6 ] ) ) )

        verify_chunk_lf11( self, chunk )

        # the data is read from a string for lf=11
        chunk = PartialDistribution.from_string( self.chunk_lf11, 9222, 5, 18 )

        verify_chunk_lf11( self, chunk )

        # the data is copied for lf=11
        copy = PartialDistribution( chunk )

        verify_chunk_lf11( self, copy )

        # the data is given explicitly for lf=12
        chunk = PartialDistribution(
                  probability = Probability( 12, [ 2 ], [ 2 ],
                                             [ 1e-5, 3e+7 ],
                                             [ 1.0, 1.0 ] ),
                  spectrum = MadlandNixSpectrum( 1.029979e+6, 5.467297e+5, [ 4 ], [ 5 ],
                                                 [ 1e-5, 5.000001e+5, 1.4e+7, 3e+7 ],
                                                 [ 1.092064e+6, 1.101483e+6,
                                                   1.129269e+6, 1.182884e+6 ] ) )

        verify_chunk_lf12( self, chunk )

        # the data is read from a string for lf=12
        chunk = PartialDistribution.from_string( self.chunk_lf12, 9543, 5, 18 )

        verify_chunk_lf12( self, chunk )

        # the data is copied for lf=12
        copy = PartialDistribution( chunk )

        verify_chunk_lf12( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong lf between the probabilities and the actual spectrum
        with self.assertRaises( Exception ) :

            chunk = PartialDistribution(
                      probability = Probability( 1, [ 2 ], [ 2 ],
                                                [ 1e-5, 3e+7 ],
                                                [ 1.0, 1.0 ], -3e+7 ),
                      spectrum = MaxwellianFissionSpectrum( [ 3 ], [ 2 ],
                                                            [ 1e-5, 5e+5, 3e+7 ],
                                                            [ 1.3652e+6, 1.3748e+6,
                                                              1.6912e+6 ] ) )

        with self.assertRaises( Exception ) :

            chunk = PartialDistribution.from_string( self.invalid, 9437, 5, 18 )

if __name__ ==  '__main__' :

    unittest.main()
