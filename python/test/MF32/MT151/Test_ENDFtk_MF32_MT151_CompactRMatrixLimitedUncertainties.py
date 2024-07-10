# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151.LCOMP2 import ParticlePairs
from ENDFtk.MF32.MT151.LCOMP2 import ResonanceChannels
from ENDFtk.MF32.MT151.LCOMP2 import ResonanceParameters
from ENDFtk.MF32.MT151.LCOMP2 import SpinGroup
from ENDFtk.MF32.MT151 import CompactRMatrixLimitedUncertainties

class Test_ENDFtk_MF32_MT151_CompactRMatrixLimitedUncertainties( unittest.TestCase ) :
    """Unit test for the CompactRMatrixLimitedUncertainties class."""

    chunk = ( ' 0.000000+0 0.000000+0          2          2         24          4262532151     \n'
              ' 0.000000+0 5.446635+1 0.000000+0 2.600000+1 1.000000+0 0.000000+0262532151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 1.020000+2 0.000000+0 0.000000+0262532151     \n'
              ' 1.000000+0 5.347624+1 0.000000+0 2.600000+1 5.000000-1 0.000000+0262532151     \n'
              ' 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0 1.000000+0262532151     \n'
              ' 5.000000-1 0.000000+0          0          0         12          2262532151     \n'
              ' 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n'
              ' 2.000000+0 0.000000+0 5.000000-1 0.000000+0 5.437300-1 5.437300-1262532151     \n'
              ' 0.000000+0 0.000000+0          0          2         24          2262532151     \n'
              '-1.223300+6 1.000000+0 9.611086+5 0.000000+0 0.000000+0 0.000000+0262532151     \n'
              ' 1.000000+0 3.000000+0 4.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n'
              ' 7.788000+3 1.455000+0 1.187354+3 0.000000+0 0.000000+0 0.000000+0262532151     \n'
              ' 2.000000+0 5.000000+0 6.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n'
              '-5.000000-1 0.000000+0          0          0         12          2262532151     \n'
              ' 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n'
              ' 2.000000+0 1.000000+0 5.000000-1 0.000000+0 5.437300-1 5.437300-1262532151     \n'
              ' 0.000000+0 0.000000+0          0          2         24          2262532151     \n'
              ' 5.152000+4 3.600000-1 1.600200+1 0.000000+0 0.000000+0 0.000000+0262532151     \n'
              ' 7.000000+0 9.000000+0 1.000000+1 0.000000+0 0.000000+0 0.000000+0262532151     \n'
              ' 5.359000+4 1.500000+0 1.700000+1 0.000000+0 0.000000+0 0.000000+0262532151     \n'
              ' 8.000000+0 1.100000+1 1.200000+1 0.000000+0 0.000000+0 0.000000+0262532151     \n' )

    no_spingroups = ( ' 0.000000+0 0.000000+0          2          0         24          4262532151     \n'
                      ' 0.000000+0 5.446635+1 0.000000+0 2.600000+1 1.000000+0 0.000000+0262532151     \n'
                      ' 0.000000+0 0.000000+0 0.000000+0 1.020000+2 0.000000+0 0.000000+0262532151     \n'
                      ' 1.000000+0 5.347624+1 0.000000+0 2.600000+1 5.000000-1 0.000000+0262532151     \n'
                      ' 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0 1.000000+0262532151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content

            pairs = chunk.particle_pairs
            self.assertEqual( 2, pairs.NJSX )
            self.assertEqual( 2, pairs.number_spin_groups )

            self.assertEqual( 2, pairs.NPP )
            self.assertEqual( 2, pairs.number_particle_pairs )
            self.assertEqual( 2, len( pairs.MA ) )
            self.assertEqual( 2, len( pairs.mass_particle_A ) )
            self.assertEqual( 2, len( pairs.MB ) )
            self.assertEqual( 2, len( pairs.mass_particle_B ) )
            self.assertEqual( 2, len( pairs.ZA ) )
            self.assertEqual( 2, len( pairs.charge_particle_A ) )
            self.assertEqual( 2, len( pairs.ZB ) )
            self.assertEqual( 2, len( pairs.charge_particle_B ) )
            self.assertEqual( 2, len( pairs.IA ) )
            self.assertEqual( 2, len( pairs.spin_particle_A ) )
            self.assertEqual( 2, len( pairs.IB ) )
            self.assertEqual( 2, len( pairs.spin_particle_B ) )
            self.assertEqual( 2, len( pairs.PA ) )
            self.assertEqual( 2, len( pairs.parity_particle_A ) )
            self.assertEqual( 2, len( pairs.PB ) )
            self.assertEqual( 2, len( pairs.parity_particle_B ) )
            self.assertEqual( 2, len( pairs.Q ) )
            self.assertEqual( 2, len( pairs.PNT ) )
            self.assertEqual( 2, len( pairs.penetrability_flag ) )
            self.assertEqual( 2, len( pairs.SHF ) )
            self.assertEqual( 2, len( pairs.shift_factor_flag ) )
            self.assertEqual( 2, len( pairs.MT ) )

            self.assertAlmostEqual( 0., pairs.MA[0] )
            self.assertAlmostEqual( 1., pairs.MA[1] )
            self.assertAlmostEqual( 0., pairs.mass_particle_A[0] )
            self.assertAlmostEqual( 1., pairs.mass_particle_A[1] )
            self.assertAlmostEqual( 5.446635e+1, pairs.MB[0] )
            self.assertAlmostEqual( 5.347624e+1, pairs.MB[1] )
            self.assertAlmostEqual( 5.446635e+1, pairs.mass_particle_B[0] )
            self.assertAlmostEqual( 5.347624e+1, pairs.mass_particle_B[1] )
            self.assertAlmostEqual( 0., pairs.ZA[0] )
            self.assertAlmostEqual( 0., pairs.ZA[1] )
            self.assertAlmostEqual( 0., pairs.charge_particle_A[0] )
            self.assertAlmostEqual( 0., pairs.charge_particle_A[1] )
            self.assertAlmostEqual( 26., pairs.ZB[0] )
            self.assertAlmostEqual( 26., pairs.ZB[1] )
            self.assertAlmostEqual( 26., pairs.charge_particle_B[0] )
            self.assertAlmostEqual( 26., pairs.charge_particle_B[1] )
            self.assertAlmostEqual( 1., pairs.IA[0] )
            self.assertAlmostEqual( 0.5, pairs.IA[1] )
            self.assertAlmostEqual( 1., pairs.spin_particle_A[0] )
            self.assertAlmostEqual( 0.5, pairs.spin_particle_A[1] )
            self.assertAlmostEqual( 0., pairs.IB[0] )
            self.assertAlmostEqual( 0., pairs.IB[1] )
            self.assertAlmostEqual( 0., pairs.spin_particle_B[0] )
            self.assertAlmostEqual( 0., pairs.spin_particle_B[1] )
            self.assertAlmostEqual( 0., pairs.PA[0] )
            self.assertAlmostEqual( 0., pairs.PA[1] )
            self.assertAlmostEqual( 0., pairs.parity_particle_A[0] )
            self.assertAlmostEqual( 0., pairs.parity_particle_A[1] )
            self.assertAlmostEqual( 0., pairs.PB[0] )
            self.assertAlmostEqual( 1., pairs.PB[1] )
            self.assertAlmostEqual( 0., pairs.parity_particle_B[0] )
            self.assertAlmostEqual( 1., pairs.parity_particle_B[1] )
            self.assertAlmostEqual( 0., pairs.Q[0] )
            self.assertAlmostEqual( 0., pairs.Q[1] )
            self.assertEqual( 0, pairs.PNT[0] )
            self.assertEqual( 1, pairs.PNT[1] )
            self.assertEqual( 0, pairs.penetrability_flag[0] )
            self.assertEqual( 1, pairs.penetrability_flag[1] )
            self.assertEqual( 0, pairs.SHF[0] )
            self.assertEqual( 0, pairs.SHF[1] )
            self.assertEqual( 0, pairs.shift_factor_flag[0] )
            self.assertEqual( 0, pairs.shift_factor_flag[1] )
            self.assertEqual( 102, pairs.MT[0] )
            self.assertEqual( 2, pairs.MT[1] )

            self.assertEqual( 2, chunk.NJSX )
            self.assertEqual( 2, chunk.number_spin_groups )
            self.assertEqual( 2, len( chunk.spin_groups ) )

            group1 = chunk.spin_groups[0]
            self.assertAlmostEqual( 0.5, group1.AJ )
            self.assertAlmostEqual( 0.5, group1.spin )
            self.assertAlmostEqual( 0., group1.PJ )
            self.assertAlmostEqual( 0., group1.parity )
            self.assertEqual( 2, group1.NCH )
            self.assertEqual( 2, group1.number_channels )
            self.assertEqual( 2, group1.NRSA )
            self.assertEqual( 2, group1.number_resonances )

            channels1 = group1.channels
            self.assertAlmostEqual( 0.5, channels1.AJ )
            self.assertAlmostEqual( 0.5, channels1.spin )
            self.assertAlmostEqual( 0., channels1.PJ )
            self.assertAlmostEqual( 0., channels1.parity )
            self.assertEqual( 2, channels1.NCH )
            self.assertEqual( 2, channels1.number_channels )

            self.assertEqual( 2, len( channels1.PPI ) )
            self.assertEqual( 2, len( channels1.particle_pair_numbers ) )
            self.assertEqual( 2, len( channels1.L ) )
            self.assertEqual( 2, len( channels1.orbital_momentum_values ) )
            self.assertEqual( 2, len( channels1.SCH ) )
            self.assertEqual( 2, len( channels1.channel_spin_values ) )
            self.assertEqual( 2, len( channels1.BND ) )
            self.assertEqual( 2, len( channels1.boundary_condition_values ) )
            self.assertEqual( 2, len( channels1.APT ) )
            self.assertEqual( 2, len( channels1.true_channel_radii ) )
            self.assertEqual( 2, len( channels1.APE ) )
            self.assertEqual( 2, len( channels1.effective_channel_radii ) )

            self.assertEqual( 1, channels1.PPI[0] )
            self.assertEqual( 2, channels1.PPI[1] )
            self.assertEqual( 1, channels1.particle_pair_numbers[0] )
            self.assertEqual( 2, channels1.particle_pair_numbers[1] )
            self.assertEqual( 0, channels1.L[0] )
            self.assertEqual( 0, channels1.L[1] )
            self.assertAlmostEqual( 0., channels1.orbital_momentum_values[0] )
            self.assertAlmostEqual( 0., channels1.orbital_momentum_values[1] )
            self.assertAlmostEqual( 0., channels1.SCH[0] )
            self.assertAlmostEqual( .5, channels1.SCH[1] )
            self.assertAlmostEqual( 0., channels1.channel_spin_values[0] )
            self.assertAlmostEqual( .5, channels1.channel_spin_values[1] )
            self.assertAlmostEqual( 0., channels1.BND[0] )
            self.assertAlmostEqual( 0., channels1.BND[1] )
            self.assertAlmostEqual( 0., channels1.boundary_condition_values[0] )
            self.assertAlmostEqual( 0., channels1.boundary_condition_values[1] )
            self.assertAlmostEqual( 0., channels1.APT[0] )
            self.assertAlmostEqual( 5.437300e-1, channels1.APT[1] )
            self.assertAlmostEqual( 0., channels1.true_channel_radii[0] )
            self.assertAlmostEqual( 5.437300e-1, channels1.true_channel_radii[1] )
            self.assertAlmostEqual( 0., channels1.APE[0] )
            self.assertAlmostEqual( 5.437300e-1, channels1.APE[1] )
            self.assertAlmostEqual( 0., channels1.effective_channel_radii[0] )
            self.assertAlmostEqual( 5.437300e-1, channels1.effective_channel_radii[1] )

            parameters1 = group1.parameters
            self.assertEqual( 2, parameters1.NRSA )
            self.assertEqual( 2, parameters1.number_resonances )
            self.assertEqual( 2, parameters1.NX )
            self.assertEqual( 2, parameters1.number_lines )

            self.assertEqual( 2, len( parameters1.ER ) )
            self.assertEqual( 2, len( parameters1.resonance_energies ) )
            self.assertEqual( 2, len( parameters1.GAM ) )
            self.assertEqual( 2, len( parameters1.resonance_parameters ) )
            self.assertEqual( 2, len( parameters1.DER ) )
            self.assertEqual( 2, len( parameters1.resonance_energy_uncertainties ) )
            self.assertEqual( 2, len( parameters1.DGAM ) )
            self.assertEqual( 2, len( parameters1.resonance_parameter_uncertainties ) )

            self.assertAlmostEqual( -1.223300e+6, parameters1.ER[0] )
            self.assertAlmostEqual(  7.788000e+3, parameters1.ER[1] )
            self.assertAlmostEqual( -1.223300e+6, parameters1.resonance_energies[0] )
            self.assertAlmostEqual(  7.788000e+3, parameters1.resonance_energies[1] )
            self.assertEqual( 5, len( parameters1.GAM[0] ) )
            self.assertEqual( 5, len( parameters1.GAM[1] ) )
            self.assertAlmostEqual( 1., parameters1.GAM[0][0] )
            self.assertAlmostEqual( 9.611086e+5, parameters1.GAM[0][1] )
            self.assertAlmostEqual( 0., parameters1.GAM[0][2] )
            self.assertAlmostEqual( 0., parameters1.GAM[0][3] )
            self.assertAlmostEqual( 0., parameters1.GAM[0][4] )
            self.assertAlmostEqual( 1.455, parameters1.GAM[1][0] )
            self.assertAlmostEqual( 1.187354e+3, parameters1.GAM[1][1] )
            self.assertAlmostEqual( 0., parameters1.GAM[1][2] )
            self.assertAlmostEqual( 0., parameters1.GAM[1][3] )
            self.assertAlmostEqual( 0., parameters1.GAM[1][4] )
            self.assertEqual( 5, len( parameters1.resonance_parameters[0] ) )
            self.assertEqual( 5, len( parameters1.resonance_parameters[1] ) )
            self.assertAlmostEqual( 1., parameters1.resonance_parameters[0][0] )
            self.assertAlmostEqual( 9.611086e+5, parameters1.resonance_parameters[0][1] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[0][2] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[0][3] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[0][4] )
            self.assertAlmostEqual( 1.455, parameters1.resonance_parameters[1][0] )
            self.assertAlmostEqual( 1.187354e+3, parameters1.resonance_parameters[1][1] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[1][2] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[1][3] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[1][4] )

            self.assertAlmostEqual( 1., parameters1.DER[0] )
            self.assertAlmostEqual( 2., parameters1.DER[1] )
            self.assertAlmostEqual( 1., parameters1.resonance_energy_uncertainties[0] )
            self.assertAlmostEqual( 2., parameters1.resonance_energy_uncertainties[1] )
            self.assertEqual( 5, len( parameters1.DGAM[0] ) )
            self.assertEqual( 5, len( parameters1.DGAM[1] ) )
            self.assertAlmostEqual( 3., parameters1.DGAM[0][0] )
            self.assertAlmostEqual( 4., parameters1.DGAM[0][1] )
            self.assertAlmostEqual( 0., parameters1.DGAM[0][2] )
            self.assertAlmostEqual( 0., parameters1.DGAM[0][3] )
            self.assertAlmostEqual( 0., parameters1.DGAM[0][4] )
            self.assertAlmostEqual( 5., parameters1.DGAM[1][0] )
            self.assertAlmostEqual( 6., parameters1.DGAM[1][1] )
            self.assertAlmostEqual( 0., parameters1.DGAM[1][2] )
            self.assertAlmostEqual( 0., parameters1.DGAM[1][3] )
            self.assertAlmostEqual( 0., parameters1.DGAM[1][4] )
            self.assertEqual( 5, len( parameters1.resonance_parameter_uncertainties[0] ) )
            self.assertEqual( 5, len( parameters1.resonance_parameter_uncertainties[1] ) )
            self.assertAlmostEqual( 3., parameters1.resonance_parameter_uncertainties[0][0] )
            self.assertAlmostEqual( 4., parameters1.resonance_parameter_uncertainties[0][1] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[0][2] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[0][3] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[0][4] )
            self.assertAlmostEqual( 5., parameters1.resonance_parameter_uncertainties[1][0] )
            self.assertAlmostEqual( 6., parameters1.resonance_parameter_uncertainties[1][1] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[1][2] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[1][3] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[1][4] )

            group2 = chunk.spin_groups[1]
            self.assertAlmostEqual( -0.5, group2.AJ )
            self.assertAlmostEqual( -0.5, group2.spin )
            self.assertAlmostEqual( 0., group2.PJ )
            self.assertAlmostEqual( 0., group2.parity )
            self.assertEqual( 2, group2.NCH )
            self.assertEqual( 2, group2.number_channels )
            self.assertEqual( 2, group2.NRSA )
            self.assertEqual( 2, group2.number_resonances )

            channels2 = group2.channels
            self.assertAlmostEqual( -0.5, channels2.AJ )
            self.assertAlmostEqual( -0.5, channels2.spin )
            self.assertAlmostEqual( 0., channels2.PJ )
            self.assertAlmostEqual( 0., channels2.parity )
            self.assertEqual( 2, channels2.NCH )
            self.assertEqual( 2, channels2.number_channels )

            self.assertEqual( 2, len( channels2.PPI ) )
            self.assertEqual( 2, len( channels2.particle_pair_numbers ) )
            self.assertEqual( 2, len( channels2.L ) )
            self.assertEqual( 2, len( channels2.orbital_momentum_values ) )
            self.assertEqual( 2, len( channels2.SCH ) )
            self.assertEqual( 2, len( channels2.channel_spin_values ) )
            self.assertEqual( 2, len( channels2.BND ) )
            self.assertEqual( 2, len( channels2.boundary_condition_values ) )
            self.assertEqual( 2, len( channels2.APT ) )
            self.assertEqual( 2, len( channels2.true_channel_radii ) )
            self.assertEqual( 2, len( channels2.APE ) )
            self.assertEqual( 2, len( channels2.effective_channel_radii ) )

            self.assertEqual( 1, channels2.PPI[0] )
            self.assertEqual( 2, channels2.PPI[1] )
            self.assertEqual( 1, channels2.particle_pair_numbers[0] )
            self.assertEqual( 2, channels2.particle_pair_numbers[1] )
            self.assertEqual( 0, channels2.L[0] )
            self.assertEqual( 1, channels2.L[1] )
            self.assertEqual( 0, channels2.orbital_momentum_values[0] )
            self.assertEqual( 1, channels2.orbital_momentum_values[1] )
            self.assertAlmostEqual( 0., channels2.SCH[0] )
            self.assertAlmostEqual( .5, channels2.SCH[1] )
            self.assertAlmostEqual( 0., channels2.channel_spin_values[0] )
            self.assertAlmostEqual( .5, channels2.channel_spin_values[1] )
            self.assertAlmostEqual( 0., channels2.BND[0] )
            self.assertAlmostEqual( 0., channels2.BND[1] )
            self.assertAlmostEqual( 0., channels2.boundary_condition_values[0] )
            self.assertAlmostEqual( 0., channels2.boundary_condition_values[1] )
            self.assertAlmostEqual( 0., channels2.APT[0] )
            self.assertAlmostEqual( 5.437300e-1, channels2.APT[1] )
            self.assertAlmostEqual( 0., channels2.true_channel_radii[0] )
            self.assertAlmostEqual( 5.437300e-1, channels2.true_channel_radii[1] )
            self.assertAlmostEqual( 0., channels2.APE[0] )
            self.assertAlmostEqual( 5.437300e-1, channels2.APE[1] )
            self.assertAlmostEqual( 0., channels2.effective_channel_radii[0] )
            self.assertAlmostEqual( 5.437300e-1, channels2.effective_channel_radii[1] )

            parameters2 = group2.parameters
            self.assertEqual( 2, parameters2.NRSA )
            self.assertEqual( 2, parameters2.number_resonances )
            self.assertEqual( 2, parameters2.NX )
            self.assertEqual( 2, parameters2.number_lines )

            self.assertEqual( 2, len( parameters2.ER ) )
            self.assertEqual( 2, len( parameters2.resonance_energies ) )
            self.assertEqual( 2, len( parameters2.GAM ) )
            self.assertEqual( 2, len( parameters2.resonance_parameters ) )
            self.assertEqual( 2, len( parameters2.DER ) )
            self.assertEqual( 2, len( parameters2.resonance_energy_uncertainties ) )
            self.assertEqual( 2, len( parameters2.DGAM ) )
            self.assertEqual( 2, len( parameters2.resonance_parameter_uncertainties ) )

            self.assertAlmostEqual( 5.152000e+4, parameters2.ER[0] )
            self.assertAlmostEqual( 5.359000e+4, parameters2.ER[1] )
            self.assertAlmostEqual( 5.152000e+4, parameters2.resonance_energies[0] )
            self.assertAlmostEqual( 5.359000e+4, parameters2.resonance_energies[1] )
            self.assertEqual( 5, len( parameters2.GAM[0] ) )
            self.assertEqual( 5, len( parameters2.GAM[1] ) )
            self.assertAlmostEqual( .36, parameters2.GAM[0][0] )
            self.assertAlmostEqual( 16.002, parameters2.GAM[0][1] )
            self.assertAlmostEqual( 0., parameters2.GAM[0][2] )
            self.assertAlmostEqual( 0., parameters2.GAM[0][3] )
            self.assertAlmostEqual( 0., parameters2.GAM[0][4] )
            self.assertAlmostEqual( 1.5, parameters2.GAM[1][0] )
            self.assertAlmostEqual( 17., parameters2.GAM[1][1] )
            self.assertAlmostEqual( 0., parameters2.GAM[1][2] )
            self.assertAlmostEqual( 0., parameters2.GAM[1][3] )
            self.assertAlmostEqual( 0., parameters2.GAM[1][4] )
            self.assertAlmostEqual( 5, len( parameters2.resonance_parameters[0] ) )
            self.assertAlmostEqual( 5, len( parameters2.resonance_parameters[1] ) )
            self.assertAlmostEqual( .36, parameters2.resonance_parameters[0][0] )
            self.assertAlmostEqual( 16.002, parameters2.resonance_parameters[0][1] )
            self.assertAlmostEqual( 0., parameters2.resonance_parameters[0][2] )
            self.assertAlmostEqual( 0., parameters2.resonance_parameters[0][3] )
            self.assertAlmostEqual( 0., parameters2.resonance_parameters[0][4] )
            self.assertAlmostEqual( 1.5, parameters2.resonance_parameters[1][0] )
            self.assertAlmostEqual( 17., parameters2.resonance_parameters[1][1] )
            self.assertAlmostEqual( 0., parameters2.resonance_parameters[1][2] )
            self.assertAlmostEqual( 0., parameters2.resonance_parameters[1][3] )
            self.assertAlmostEqual( 0., parameters2.resonance_parameters[1][4] )

            self.assertAlmostEqual(  7., parameters2.DER[0] )
            self.assertAlmostEqual(  8., parameters2.DER[1] )
            self.assertAlmostEqual(  7., parameters2.resonance_energy_uncertainties[0] )
            self.assertAlmostEqual(  8., parameters2.resonance_energy_uncertainties[1] )
            self.assertEqual(  5, len( parameters2.DGAM[0] ) )
            self.assertEqual(  5, len( parameters2.DGAM[1] ) )
            self.assertAlmostEqual(  9., parameters2.DGAM[0][0] )
            self.assertAlmostEqual( 10., parameters2.DGAM[0][1] )
            self.assertAlmostEqual(  0., parameters2.DGAM[0][2] )
            self.assertAlmostEqual(  0., parameters2.DGAM[0][3] )
            self.assertAlmostEqual(  0., parameters2.DGAM[0][4] )
            self.assertAlmostEqual( 11., parameters2.DGAM[1][0] )
            self.assertAlmostEqual( 12., parameters2.DGAM[1][1] )
            self.assertAlmostEqual(  0., parameters2.DGAM[1][2] )
            self.assertAlmostEqual(  0., parameters2.DGAM[1][3] )
            self.assertAlmostEqual(  0., parameters2.DGAM[1][4] )
            self.assertAlmostEqual(  5, len( parameters2.resonance_parameter_uncertainties[0] ) )
            self.assertAlmostEqual(  5, len( parameters2.resonance_parameter_uncertainties[1] ) )
            self.assertAlmostEqual(  9., parameters2.resonance_parameter_uncertainties[0][0] )
            self.assertAlmostEqual( 10., parameters2.resonance_parameter_uncertainties[0][1] )
            self.assertAlmostEqual(  0., parameters2.resonance_parameter_uncertainties[0][2] )
            self.assertAlmostEqual(  0., parameters2.resonance_parameter_uncertainties[0][3] )
            self.assertAlmostEqual(  0., parameters2.resonance_parameter_uncertainties[0][4] )
            self.assertAlmostEqual( 11., parameters2.resonance_parameter_uncertainties[1][0] )
            self.assertAlmostEqual( 12., parameters2.resonance_parameter_uncertainties[1][1] )
            self.assertAlmostEqual(  0., parameters2.resonance_parameter_uncertainties[1][2] )
            self.assertAlmostEqual(  0., parameters2.resonance_parameter_uncertainties[1][3] )
            self.assertAlmostEqual(  0., parameters2.resonance_parameter_uncertainties[1][4] )

            self.assertEqual( 21, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 2625, 32, 151 ) )

        # the data is given explicitly
        chunk = CompactRMatrixLimitedUncertainties(
                    pairs = ParticlePairs(
                                2,
                                [ 0., 1. ], [ 5.446635e+1, 5.347624e+1 ],
                                [ 0., 0. ], [ 26., 26. ],
                                [ 1., 0.5 ], [ 0., 0. ],
                                [ 0., 0. ], [ 0., 1. ],
                                [ 0., 0. ], [ 0, 1 ],
                                [ 0, 0 ], [ 102, 2 ] ),
                    groups = [ SpinGroup(
                                   ResonanceChannels(
                                       0.5, 0., [ 1, 2 ], [ 0, 0 ], [ 0., 0.5 ], [ 0., 0. ],
                                       [ 0., 0.54373 ], [ 0., 0.54373 ] ),
                                   ResonanceParameters(
                                       [ -1.223300e+6, 7.788000e+3 ],
                                       [ [ 1., 9.611086e+5 ], [ 1.455, 1.187354e+3 ] ],
                                       [ 1., 2. ],
                                       [ [ 3., 4. ], [ 5., 6. ] ] ) ),
                               SpinGroup(
                                   ResonanceChannels(
                                       -0.5, 0., [ 1, 2 ], [ 0, 1 ], [ 0., 0.5 ], [ 0., 0. ],
                                       [ 0., 0.54373 ], [ 0., 0.54373 ] ),
                                   ResonanceParameters(
                                       [ 5.152000e+4, 5.359000e+4 ],
                                       [ [ .36, 16.002 ], [ 1.5, 17. ] ],
                                       [ 7., 8. ],
                                       [ [ 9., 10. ], [ 11., 12. ] ] ) ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = CompactRMatrixLimitedUncertainties.from_string( self.chunk, 2625, 32, 151, 2 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = CompactRMatrixLimitedUncertainties( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # no spin groups
        with self.assertRaises( Exception ) :

            chunk = CompactRMatrixLimitedUncertainties(
                        pairs = ParticlePairs(
                                    2,
                                    [ 0., 1. ], [ 5.446635e+1, 5.347624e+1 ],
                                    [ 0., 0. ], [ 26., 26. ],
                                    [ 1., 0.5 ], [ 0., 0. ],
                                    [ 0., 0. ], [ 0., 1. ],
                                    [ 0., 0. ], [ 0, 1 ],
                                    [ 0, 0 ], [ 102, 2 ] ),
                        groups = [] )

        # string without spin groups
        with self.assertRaises( Exception ) :

            chunk = CompactRMatrixLimitedUncertainties.from_string( self.no_spingroups,
                                                                    2625, 32, 151 )

if __name__ == '__main__' :

    unittest.main()
