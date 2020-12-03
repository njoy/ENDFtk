# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import SpinGroup
from ENDFtk.MF2.MT151 import ResonanceChannels
from ENDFtk.MF2.MT151 import ResonanceParameters

class Test_ENDFtk_MF2_MT151_SpinGroup( unittest.TestCase ) :
    """Unit test for the SpinGroup class."""

    chunk = ( ' 5.000000-1 0.000000+0          0          0         12          22625 2151     \n'
              ' 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02625 2151     \n'
              ' 2.000000+0 0.000000+0 5.000000-1 0.000000+0 5.437300-1 5.437300-12625 2151     \n'
              ' 0.000000+0 0.000000+0          0          2         12          22625 2151     \n'
              '-1.223300+6 1.000000+0 9.611086+5 0.000000+0 0.000000+0 0.000000+02625 2151     \n'
              ' 7.788000+3 1.455000+0 1.187354+3 0.000000+0 0.000000+0 0.000000+02625 2151     \n' )

    invalid_size = ( ' 0.000000+0 0.000000+0          0          2         23          42625 2151     \n'
                     '-1.223300+6 1.000000+0 9.611086+5 1.000000+0 2.000000+0 3.000000+02625 2151     \n'
                     ' 4.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02625 2151     \n'
                     ' 7.788000+3 1.455000+0 1.187354+3 5.000000+0 6.000000+0 7.000000+02625 2151     \n'
                     ' 8.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0           2625 2151     \n' )

    zero_size = ( ' 0.000000+0 0.000000+0          0          2          0          42625 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 0.5, chunk.AJ )
            self.assertAlmostEqual( 0.5, chunk.spin )
            self.assertAlmostEqual( 0., chunk.PJ )
            self.assertAlmostEqual( 0., chunk.parity )
            self.assertEqual( 2, chunk.NCH )
            self.assertEqual( 2, chunk.number_channels )
            self.assertEqual( 2, chunk.NRS )
            self.assertEqual( 2, chunk.number_resonances )

            channels = chunk.channels
            self.assertAlmostEqual( 0.5, channels.AJ )
            self.assertAlmostEqual( 0.5, channels.spin )
            self.assertAlmostEqual( 0., channels.PJ )
            self.assertAlmostEqual( 0., channels.parity )
            self.assertEqual( 0, channels.KBK )
            self.assertEqual( 0, channels.background_rmatrix_option )
            self.assertEqual( 0, channels.KPS )
            self.assertEqual( 0, channels.phase_shift_option )
            self.assertEqual( 2, channels.NCH )
            self.assertEqual( 2, channels.number_channels )

            self.assertEqual( 2, len( channels.PPI ) )
            self.assertEqual( 2, len( channels.particle_pair_numbers ) )
            self.assertEqual( 2, len( channels.L ) )
            self.assertEqual( 2, len( channels.orbital_momentum_values ) )
            self.assertEqual( 2, len( channels.SCH ) )
            self.assertEqual( 2, len( channels.channel_spin_values ) )
            self.assertEqual( 2, len( channels.BND ) )
            self.assertEqual( 2, len( channels.boundary_condition_values ) )
            self.assertEqual( 2, len( channels.APT ) )
            self.assertEqual( 2, len( channels.true_channel_radii ) )
            self.assertEqual( 2, len( channels.APE ) )
            self.assertEqual( 2, len( channels.effective_channel_radii ) )

            self.assertEqual( 1, channels.PPI[0] )
            self.assertEqual( 2, channels.PPI[1] )
            self.assertEqual( 1, channels.particle_pair_numbers[0] )
            self.assertEqual( 2, channels.particle_pair_numbers[1] )
            self.assertEqual( 0, channels.L[0] )
            self.assertEqual( 0, channels.L[1] )
            self.assertEqual( 0, channels.orbital_momentum_values[0] )
            self.assertEqual( 0, channels.orbital_momentum_values[1] )
            self.assertAlmostEqual( 0., channels.SCH[0] )
            self.assertAlmostEqual( .5, channels.SCH[1] )
            self.assertAlmostEqual( 0., channels.channel_spin_values[0] )
            self.assertAlmostEqual( .5, channels.channel_spin_values[1] )
            self.assertAlmostEqual( 0., channels.BND[0] )
            self.assertAlmostEqual( 0., channels.BND[1] )
            self.assertAlmostEqual( 0., channels.boundary_condition_values[0] )
            self.assertAlmostEqual( 0., channels.boundary_condition_values[1] )
            self.assertAlmostEqual( 0., channels.APT[0] )
            self.assertAlmostEqual( 5.437300e-1, channels.APT[1] )
            self.assertAlmostEqual( 0., channels.true_channel_radii[0] )
            self.assertAlmostEqual( 5.437300e-1, channels.true_channel_radii[1] )
            self.assertAlmostEqual( 0., channels.APE[0] )
            self.assertAlmostEqual( 5.437300e-1, channels.APE[1] )
            self.assertAlmostEqual( 0., channels.effective_channel_radii[0] )
            self.assertAlmostEqual( 5.437300e-1, channels.effective_channel_radii[1] )

            parameters = chunk.parameters
            self.assertEqual( 2, parameters.NRS )
            self.assertEqual( 2, parameters.number_resonances )
            self.assertEqual( 2, parameters.NX )
            self.assertEqual( 2, parameters.number_lines )

            self.assertEqual( 2, len( parameters.ER ) )
            self.assertEqual( 2, len( parameters.resonance_energies ) )
            self.assertEqual( 2, len( parameters.GAM ) )
            self.assertEqual( 2, len( parameters.resonance_parameters ) )

            self.assertAlmostEqual( -1.223300e+6, parameters.ER[0] )
            self.assertAlmostEqual(  7.788000e+3, parameters.ER[1] )
            self.assertAlmostEqual( -1.223300e+6, parameters.resonance_energies[0] )
            self.assertAlmostEqual(  7.788000e+3, parameters.resonance_energies[1] )
            self.assertEqual( 5, len( parameters.GAM[0] ) )
            self.assertEqual( 5, len( parameters.GAM[1] ) )
            self.assertAlmostEqual( 1., parameters.GAM[0][0] )
            self.assertAlmostEqual( 9.611086e+5, parameters.GAM[0][1] )
            self.assertAlmostEqual( 0., parameters.GAM[0][2] )
            self.assertAlmostEqual( 0., parameters.GAM[0][3] )
            self.assertAlmostEqual( 0., parameters.GAM[0][4] )
            self.assertAlmostEqual( 1.455, parameters.GAM[1][0] )
            self.assertAlmostEqual( 1.187354e+3, parameters.GAM[1][1] )
            self.assertAlmostEqual( 0., parameters.GAM[1][2] )
            self.assertAlmostEqual( 0., parameters.GAM[1][3] )
            self.assertAlmostEqual( 0., parameters.GAM[1][4] )
            self.assertEqual( 5, len( parameters.resonance_parameters[0] ) )
            self.assertEqual( 5, len( parameters.resonance_parameters[1] ) )
            self.assertAlmostEqual( 1., parameters.resonance_parameters[0][0] )
            self.assertAlmostEqual( 9.611086e+5, parameters.resonance_parameters[0][1] )
            self.assertAlmostEqual( 0., parameters.resonance_parameters[0][2] )
            self.assertAlmostEqual( 0., parameters.resonance_parameters[0][3] )
            self.assertAlmostEqual( 0., parameters.resonance_parameters[0][4] )
            self.assertAlmostEqual( 1.455, parameters.resonance_parameters[1][0] )
            self.assertAlmostEqual( 1.187354e+3, parameters.resonance_parameters[1][1] )
            self.assertAlmostEqual( 0., parameters.resonance_parameters[1][2] )
            self.assertAlmostEqual( 0., parameters.resonance_parameters[1][3] )
            self.assertAlmostEqual( 0., parameters.resonance_parameters[1][4] )

            self.assertEqual( 6, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 2625, 2, 151 ) )

        # the data is given explicitly
        chunk = SpinGroup(
                  channels = ResonanceChannels(
                               spin = 0.5, parity = 0., ppi = [ 1, 2 ],
                               l = [ 0, 0 ], s = [ 0., 0.5 ], b = [ 0., 0. ],
                               ape = [ 0.,  0.54373 ], apt = [ 0.,  0.54373 ] ),
                  parameters = ResonanceParameters(
                                 energies = [ -1.223300e+6, 7.788000e+3 ],
                                 parameters = [ [ 1., 9.611086e+5 ],
                                                [ 1.455, 1.187354e+3 ] ] ) )

        # verify_chunk( self, chunk )

        # the data is read from a string
        chunk = SpinGroup.from_string( self.chunk, 2625, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = SpinGroup( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
