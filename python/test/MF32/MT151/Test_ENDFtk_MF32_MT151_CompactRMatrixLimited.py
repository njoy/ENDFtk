# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151.LCOMP2 import ParticlePairs
from ENDFtk.MF32.MT151.LCOMP2 import ResonanceChannels
from ENDFtk.MF32.MT151.LCOMP2 import ResonanceParameters
from ENDFtk.MF32.MT151.LCOMP2 import SpinGroup
from ENDFtk.MF32.MT151 import CompactCorrelationMatrix
from ENDFtk.MF32.MT151 import CompactRMatrixLimitedUncertainties
from ENDFtk.MF32.MT151 import CompactRMatrixLimited

class Test_ENDFtk_MF32_MT151_CompactRMatrixLimitedUncertainties( unittest.TestCase ) :
    """Unit test for the CompactRMatrixLimitedUncertainties class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          2          1          0293132151     \n'
              ' 0.000000+0 0.000000+0          2          1         24          4293132151     \n'
              ' 0.000000+0 6.537000+1 0.000000+0 0.000000+0 1.000000+0 0.000000+0293132151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 1.020000+2 0.000000+0 0.000000+0293132151     \n'
              ' 1.000000+0 6.437000+1 0.000000+0 0.000000+0 5.000000-1-1.500000+0293132151     \n'
              ' 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0 0.000000+0293132151     \n'
              '-1.000000+0 0.000000+0          0          0         12          2293132151     \n'
              ' 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0293132151     \n'
              ' 2.000000+0 0.000000+0 1.000000+0 0.000000+0 6.700000-1 6.700000-1293132151     \n'
              ' 0.000000+0 0.000000+0          0          4         48          4293132151     \n'
              '-1.535904+3 3.950000-1 2.943392+2 0.000000+0 0.000000+0 0.000000+0293132151     \n'
              ' 1.377556+1 8.403206-6 1.026766-3 0.000000+0 0.000000+0 0.000000+0293132151     \n'
              ' 1.363096+3 3.950000-1 2.778162-2 0.000000+0 0.000000+0 0.000000+0293132151     \n'
              ' 4.389417+0 2.802750-3 1.169698-4 0.000000+0 0.000000+0 0.000000+0293132151     \n'
              ' 2.648648+3 3.950000-1 2.358290-3 0.000000+0 0.000000+0 0.000000+0293132151     \n'
              ' 1.889408+1 4.333117-3 2.987095-5 0.000000+0 0.000000+0 0.000000+0293132151     \n'
              ' 3.585385+3 3.950000-1 5.706056-2 0.000000+0 0.000000+0 0.000000+0293132151     \n'
              ' 6.799781+0 4.163289-2 3.271682-4 0.000000+0 0.000000+0 0.000000+0293132151     \n'
              ' 0.000000+0 0.000000+0          2         12          6          0293132151     \n'
              '    2    1 -79                                                    293132151     \n'
              '    3    1 -94 66                                                 293132151     \n'
              '    5    1   1 -2  0 -2                                           293132151     \n'
              '    6    3  -1  2-59                                              293132151     \n'
              '    8    1  -1  2  1  0  0  0 -5                                  293132151     \n'
              '    9    1  -1  1  0  0  0  0 -6 16                               293132151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LRU )
            self.assertEqual( 1, chunk.type )
            self.assertEqual( 7, chunk.LRF )
            self.assertEqual( 7, chunk.representation )
            self.assertEqual( False, chunk.LFW )
            self.assertEqual( False, chunk.average_fission_width_flag )
            self.assertEqual( 2, chunk.LCOMP )
            self.assertEqual( 2, chunk.covariance_representation )

            self.assertEqual( False, chunk.IFG )
            self.assertEqual( False, chunk.reduced_widths )
            self.assertEqual( 1, chunk.NJS )
            self.assertEqual( 1, chunk.number_spin_groups )

            self.assertEqual( None, chunk.DAP )
            self.assertEqual( None, chunk.scattering_radius_uncertainty )

            pairs = chunk.uncertainties.particle_pairs
            self.assertEqual( 1, pairs.NJSX )
            self.assertEqual( 1, pairs.number_spin_groups )

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
            self.assertAlmostEqual( 65.37, pairs.MB[0] )
            self.assertAlmostEqual( 64.37, pairs.MB[1] )
            self.assertAlmostEqual( 65.37, pairs.mass_particle_B[0] )
            self.assertAlmostEqual( 64.37, pairs.mass_particle_B[1] )
            self.assertAlmostEqual( 0., pairs.ZA[0] )
            self.assertAlmostEqual( 0., pairs.ZA[1] )
            self.assertAlmostEqual( 0., pairs.charge_particle_A[0] )
            self.assertAlmostEqual( 0., pairs.charge_particle_A[1] )
            self.assertAlmostEqual( 0., pairs.ZB[0] )
            self.assertAlmostEqual( 0., pairs.ZB[1] )
            self.assertAlmostEqual( 0., pairs.charge_particle_B[0] )
            self.assertAlmostEqual( 0., pairs.charge_particle_B[1] )
            self.assertAlmostEqual( 1., pairs.IA[0] )
            self.assertAlmostEqual( 0.5, pairs.IA[1] )
            self.assertAlmostEqual( 1., pairs.spin_particle_A[0] )
            self.assertAlmostEqual( 0.5, pairs.spin_particle_A[1] )
            self.assertAlmostEqual( 0., pairs.IB[0] )
            self.assertAlmostEqual( -1.5, pairs.IB[1] )
            self.assertAlmostEqual( 0., pairs.spin_particle_B[0] )
            self.assertAlmostEqual( -1.5, pairs.spin_particle_B[1] )
            self.assertAlmostEqual( 0., pairs.PA[0] )
            self.assertAlmostEqual( 0., pairs.PA[1] )
            self.assertAlmostEqual( 0., pairs.parity_particle_A[0] )
            self.assertAlmostEqual( 0., pairs.parity_particle_A[1] )
            self.assertAlmostEqual( 0., pairs.PB[0] )
            self.assertAlmostEqual( 0., pairs.PB[1] )
            self.assertAlmostEqual( 0., pairs.parity_particle_B[0] )
            self.assertAlmostEqual( 0., pairs.parity_particle_B[1] )
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

            self.assertEqual( 1, chunk.uncertainties.NJSX )
            self.assertEqual( 1, chunk.uncertainties.number_spin_groups )
            self.assertEqual( 1, len( chunk.uncertainties.spin_groups ) )

            group1 = chunk.uncertainties.spin_groups[0]
            self.assertAlmostEqual( -1, group1.AJ )
            self.assertAlmostEqual( -1, group1.spin )
            self.assertAlmostEqual( 0., group1.PJ )
            self.assertAlmostEqual( 0., group1.parity )
            self.assertEqual( 2, group1.NCH )
            self.assertEqual( 2, group1.number_channels )
            self.assertEqual( 4, group1.NRSA )
            self.assertEqual( 4, group1.number_resonances )

            channels1 = group1.channels
            self.assertAlmostEqual( -1., channels1.AJ )
            self.assertAlmostEqual( -1., channels1.spin )
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
            self.assertAlmostEqual( 1., channels1.SCH[1] )
            self.assertAlmostEqual( 0., channels1.channel_spin_values[0] )
            self.assertAlmostEqual( 1., channels1.channel_spin_values[1] )
            self.assertAlmostEqual( 0., channels1.BND[0] )
            self.assertAlmostEqual( 0., channels1.BND[1] )
            self.assertAlmostEqual( 0., channels1.boundary_condition_values[0] )
            self.assertAlmostEqual( 0., channels1.boundary_condition_values[1] )
            self.assertAlmostEqual( 0., channels1.APT[0] )
            self.assertAlmostEqual( 0.67, channels1.APT[1] )
            self.assertAlmostEqual( 0., channels1.true_channel_radii[0] )
            self.assertAlmostEqual( 0.67, channels1.true_channel_radii[1] )
            self.assertAlmostEqual( 0., channels1.APE[0] )
            self.assertAlmostEqual( 0.67, channels1.APE[1] )
            self.assertAlmostEqual( 0., channels1.effective_channel_radii[0] )
            self.assertAlmostEqual( 0.67, channels1.effective_channel_radii[1] )

            parameters1 = group1.parameters
            self.assertEqual( 4, parameters1.NRSA )
            self.assertEqual( 4, parameters1.number_resonances )
            self.assertEqual( 4, parameters1.NX )
            self.assertEqual( 4, parameters1.number_lines )

            self.assertEqual( 4, len( parameters1.ER ) )
            self.assertEqual( 4, len( parameters1.resonance_energies ) )
            self.assertEqual( 4, len( parameters1.GAM ) )
            self.assertEqual( 4, len( parameters1.resonance_parameters ) )
            self.assertEqual( 4, len( parameters1.DER ) )
            self.assertEqual( 4, len( parameters1.resonance_energy_uncertainties ) )
            self.assertEqual( 4, len( parameters1.DGAM ) )
            self.assertEqual( 4, len( parameters1.resonance_parameter_uncertainties ) )

            self.assertAlmostEqual( -1.535904e+3, parameters1.ER[0] )
            self.assertAlmostEqual(  1.363096e+3, parameters1.ER[1] )
            self.assertAlmostEqual(  2.648648e+3, parameters1.ER[2] )
            self.assertAlmostEqual(  3.585385e+3, parameters1.ER[3] )
            self.assertAlmostEqual( -1.535904e+3, parameters1.resonance_energies[0] )
            self.assertAlmostEqual(  1.363096e+3, parameters1.resonance_energies[1] )
            self.assertAlmostEqual(  2.648648e+3, parameters1.resonance_energies[2] )
            self.assertAlmostEqual(  3.585385e+3, parameters1.resonance_energies[3] )
            self.assertEqual( 5, len( parameters1.GAM[0] ) )
            self.assertEqual( 5, len( parameters1.GAM[1] ) )
            self.assertEqual( 5, len( parameters1.GAM[2] ) )
            self.assertEqual( 5, len( parameters1.GAM[3] ) )
            self.assertAlmostEqual( 3.950000e-1, parameters1.GAM[0][0] )
            self.assertAlmostEqual( 2.943392e+2, parameters1.GAM[0][1] )
            self.assertAlmostEqual( 0., parameters1.GAM[0][2] )
            self.assertAlmostEqual( 0., parameters1.GAM[0][3] )
            self.assertAlmostEqual( 0., parameters1.GAM[0][4] )
            self.assertAlmostEqual( 3.950000e-1, parameters1.GAM[1][0] )
            self.assertAlmostEqual( 2.778162e-2, parameters1.GAM[1][1] )
            self.assertAlmostEqual( 0., parameters1.GAM[1][2] )
            self.assertAlmostEqual( 0., parameters1.GAM[1][3] )
            self.assertAlmostEqual( 0., parameters1.GAM[1][4] )
            self.assertAlmostEqual( 3.950000e-1, parameters1.GAM[2][0] )
            self.assertAlmostEqual( 2.358290e-3, parameters1.GAM[2][1] )
            self.assertAlmostEqual( 0., parameters1.GAM[2][2] )
            self.assertAlmostEqual( 0., parameters1.GAM[2][3] )
            self.assertAlmostEqual( 0., parameters1.GAM[2][4] )
            self.assertAlmostEqual( 3.950000e-1, parameters1.GAM[3][0] )
            self.assertAlmostEqual( 5.706056e-2, parameters1.GAM[3][1] )
            self.assertAlmostEqual( 0., parameters1.GAM[3][2] )
            self.assertAlmostEqual( 0., parameters1.GAM[3][3] )
            self.assertAlmostEqual( 0., parameters1.GAM[3][4] )
            self.assertEqual( 5, len( parameters1.resonance_parameters[0] ) )
            self.assertEqual( 5, len( parameters1.resonance_parameters[1] ) )
            self.assertEqual( 5, len( parameters1.resonance_parameters[2] ) )
            self.assertEqual( 5, len( parameters1.resonance_parameters[3] ) )
            self.assertAlmostEqual( 3.950000e-1, parameters1.resonance_parameters[0][0] )
            self.assertAlmostEqual( 2.943392e+2, parameters1.resonance_parameters[0][1] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[0][2] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[0][3] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[0][4] )
            self.assertAlmostEqual( 3.950000e-1, parameters1.resonance_parameters[1][0] )
            self.assertAlmostEqual( 2.778162e-2, parameters1.resonance_parameters[1][1] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[1][2] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[1][3] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[1][4] )
            self.assertAlmostEqual( 3.950000e-1, parameters1.resonance_parameters[2][0] )
            self.assertAlmostEqual( 2.358290e-3, parameters1.resonance_parameters[2][1] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[2][2] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[2][3] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[2][4] )
            self.assertAlmostEqual( 3.950000e-1, parameters1.resonance_parameters[3][0] )
            self.assertAlmostEqual( 5.706056e-2, parameters1.resonance_parameters[3][1] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[3][2] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[3][3] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameters[3][4] )

            self.assertAlmostEqual( 1.377556e+1, parameters1.DER[0] )
            self.assertAlmostEqual( 4.389417e+0, parameters1.DER[1] )
            self.assertAlmostEqual( 1.889408e+1, parameters1.DER[2] )
            self.assertAlmostEqual( 6.799781e+0, parameters1.DER[3] )
            self.assertAlmostEqual( 1.377556e+1, parameters1.resonance_energy_uncertainties[0] )
            self.assertAlmostEqual( 4.389417e+0, parameters1.resonance_energy_uncertainties[1] )
            self.assertAlmostEqual( 1.889408e+1, parameters1.resonance_energy_uncertainties[2] )
            self.assertAlmostEqual( 6.799781e+0, parameters1.resonance_energy_uncertainties[3] )
            self.assertEqual( 5, len( parameters1.DGAM[0] ) )
            self.assertEqual( 5, len( parameters1.DGAM[1] ) )
            self.assertEqual( 5, len( parameters1.DGAM[2] ) )
            self.assertEqual( 5, len( parameters1.DGAM[3] ) )
            self.assertAlmostEqual( 8.403206e-6, parameters1.DGAM[0][0] )
            self.assertAlmostEqual( 1.026766e-3, parameters1.DGAM[0][1] )
            self.assertAlmostEqual( 0., parameters1.DGAM[0][2] )
            self.assertAlmostEqual( 0., parameters1.DGAM[0][3] )
            self.assertAlmostEqual( 0., parameters1.DGAM[0][4] )
            self.assertAlmostEqual( 2.802750e-3, parameters1.DGAM[1][0] )
            self.assertAlmostEqual( 1.169698e-4, parameters1.DGAM[1][1] )
            self.assertAlmostEqual( 0., parameters1.DGAM[1][2] )
            self.assertAlmostEqual( 0., parameters1.DGAM[1][3] )
            self.assertAlmostEqual( 0., parameters1.DGAM[1][4] )
            self.assertAlmostEqual( 4.333117e-3, parameters1.DGAM[2][0] )
            self.assertAlmostEqual( 2.987095e-5, parameters1.DGAM[2][1] )
            self.assertAlmostEqual( 0., parameters1.DGAM[2][2] )
            self.assertAlmostEqual( 0., parameters1.DGAM[2][3] )
            self.assertAlmostEqual( 0., parameters1.DGAM[2][4] )
            self.assertAlmostEqual( 4.163289e-2, parameters1.DGAM[3][0] )
            self.assertAlmostEqual( 3.271682e-4, parameters1.DGAM[3][1] )
            self.assertAlmostEqual( 0., parameters1.DGAM[3][2] )
            self.assertAlmostEqual( 0., parameters1.DGAM[3][3] )
            self.assertAlmostEqual( 0., parameters1.DGAM[3][4] )
            self.assertEqual( 5, len( parameters1.resonance_parameter_uncertainties[0] ) )
            self.assertEqual( 5, len( parameters1.resonance_parameter_uncertainties[1] ) )
            self.assertEqual( 5, len( parameters1.resonance_parameter_uncertainties[2] ) )
            self.assertEqual( 5, len( parameters1.resonance_parameter_uncertainties[3] ) )
            self.assertAlmostEqual( 8.403206e-6, parameters1.resonance_parameter_uncertainties[0][0] )
            self.assertAlmostEqual( 1.026766e-3, parameters1.resonance_parameter_uncertainties[0][1] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[0][2] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[0][3] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[0][4] )
            self.assertAlmostEqual( 2.802750e-3, parameters1.resonance_parameter_uncertainties[1][0] )
            self.assertAlmostEqual( 1.169698e-4, parameters1.resonance_parameter_uncertainties[1][1] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[1][2] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[1][3] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[1][4] )
            self.assertAlmostEqual( 4.333117e-3, parameters1.resonance_parameter_uncertainties[2][0] )
            self.assertAlmostEqual( 2.987095e-5, parameters1.resonance_parameter_uncertainties[2][1] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[2][2] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[2][3] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[2][4] )
            self.assertAlmostEqual( 4.163289e-2, parameters1.resonance_parameter_uncertainties[3][0] )
            self.assertAlmostEqual( 3.271682e-4, parameters1.resonance_parameter_uncertainties[3][1] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[3][2] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[3][3] )
            self.assertAlmostEqual( 0., parameters1.resonance_parameter_uncertainties[3][4] )

            self.assertEqual( 2, chunk.correlation_matrix.NDIGIT )
            self.assertEqual( 2, chunk.correlation_matrix.number_digits )
            self.assertEqual( 12, chunk.correlation_matrix.NNN )
            self.assertEqual( 12, chunk.correlation_matrix.order )
            self.assertEqual( 17, len( chunk.correlation_matrix.I ) )
            self.assertEqual( 17, len( chunk.correlation_matrix.J ) )
            self.assertEqual( 17, len( chunk.correlation_matrix.correlations ) )

            self.assertEqual( 2, chunk.correlation_matrix.I[0] )
            self.assertEqual( 3, chunk.correlation_matrix.I[1] )
            self.assertEqual( 3, chunk.correlation_matrix.I[2] )
            self.assertEqual( 5, chunk.correlation_matrix.I[3] )
            self.assertEqual( 5, chunk.correlation_matrix.I[4] )
            self.assertEqual( 5, chunk.correlation_matrix.I[5] )
            self.assertEqual( 6, chunk.correlation_matrix.I[6] )
            self.assertEqual( 6, chunk.correlation_matrix.I[7] )
            self.assertEqual( 6, chunk.correlation_matrix.I[8] )
            self.assertEqual( 8, chunk.correlation_matrix.I[9] )
            self.assertEqual( 8, chunk.correlation_matrix.I[10] )
            self.assertEqual( 8, chunk.correlation_matrix.I[11] )
            self.assertEqual( 8, chunk.correlation_matrix.I[12] )
            self.assertEqual( 9, chunk.correlation_matrix.I[13] )
            self.assertEqual( 9, chunk.correlation_matrix.I[14] )
            self.assertEqual( 9, chunk.correlation_matrix.I[15] )
            self.assertEqual( 9, chunk.correlation_matrix.I[16] )

            self.assertEqual( 1, chunk.correlation_matrix.J[0] )
            self.assertEqual( 1, chunk.correlation_matrix.J[1] )
            self.assertEqual( 2, chunk.correlation_matrix.J[2] )
            self.assertEqual( 1, chunk.correlation_matrix.J[3] )
            self.assertEqual( 2, chunk.correlation_matrix.J[4] )
            self.assertEqual( 4, chunk.correlation_matrix.J[5] )
            self.assertEqual( 3, chunk.correlation_matrix.J[6] )
            self.assertEqual( 4, chunk.correlation_matrix.J[7] )
            self.assertEqual( 5, chunk.correlation_matrix.J[8] )
            self.assertEqual( 1, chunk.correlation_matrix.J[9] )
            self.assertEqual( 2, chunk.correlation_matrix.J[10] )
            self.assertEqual( 3, chunk.correlation_matrix.J[11] )
            self.assertEqual( 7, chunk.correlation_matrix.J[12] )
            self.assertEqual( 1, chunk.correlation_matrix.J[13] )
            self.assertEqual( 2, chunk.correlation_matrix.J[14] )
            self.assertEqual( 7, chunk.correlation_matrix.J[15] )
            self.assertEqual( 8, chunk.correlation_matrix.J[16] )

            self.assertAlmostEqual( -795e-3, chunk.correlation_matrix.correlations[0] )
            self.assertAlmostEqual( -945e-3, chunk.correlation_matrix.correlations[1] )
            self.assertAlmostEqual(  665e-3, chunk.correlation_matrix.correlations[2] )
            self.assertAlmostEqual(   15e-3, chunk.correlation_matrix.correlations[3] )
            self.assertAlmostEqual(  -25e-3, chunk.correlation_matrix.correlations[4] )
            self.assertAlmostEqual(  -25e-3, chunk.correlation_matrix.correlations[5] )
            self.assertAlmostEqual(  -15e-3, chunk.correlation_matrix.correlations[6] )
            self.assertAlmostEqual(   25e-3, chunk.correlation_matrix.correlations[7] )
            self.assertAlmostEqual( -595e-3, chunk.correlation_matrix.correlations[8] )
            self.assertAlmostEqual(  -15e-3, chunk.correlation_matrix.correlations[9] )
            self.assertAlmostEqual(   25e-3, chunk.correlation_matrix.correlations[10] )
            self.assertAlmostEqual(   15e-3, chunk.correlation_matrix.correlations[11] )
            self.assertAlmostEqual(  -55e-3, chunk.correlation_matrix.correlations[12] )
            self.assertAlmostEqual(  -15e-3, chunk.correlation_matrix.correlations[13] )
            self.assertAlmostEqual(   15e-3, chunk.correlation_matrix.correlations[14] )
            self.assertAlmostEqual(  -65e-3, chunk.correlation_matrix.correlations[15] )
            self.assertAlmostEqual(  165e-3, chunk.correlation_matrix.correlations[16] )

            self.assertEqual( 25, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 2931, 32, 151 ) )

        # the data is given explicitly
        chunk = CompactRMatrixLimited(
                    ifg = False,
                    parameters = CompactRMatrixLimitedUncertainties(
                                   ParticlePairs(
                                     1,
                                     [ 0., 1. ], [ 65.37, 64.37 ], [ 0., 0. ], [ 0., 0. ],
                                     [ 1., 0.5 ], [ 0., -1.5 ], [ 0., 0. ], [ 0., 0. ],
                                     [ 0., 0. ], [ 0, 1 ], [ 0, 0 ], [ 102, 2 ] ),
                                   [ SpinGroup(
                                       ResonanceChannels(
                                           -1., 0.,
                                           [ 1, 2 ], [ 0, 0 ], [ 0., 1. ],
                                           [ 0., 0. ], [ 0., 0.67 ] ),
                                       ResonanceParameters(
                                           [ -1.535904e+3, 1.363096e+3,
                                              2.648648e+3, 3.585385e+3 ],
                                           [ [ 3.950000e-1, 2.943392e+2 ],
                                             [ 3.950000e-1, 2.778162e-2 ],
                                             [ 3.950000e-1, 2.358290e-3 ],
                                             [ 3.950000e-1, 5.706056e-2 ] ],
                                           [ 1.377556e+1, 4.389417e+0,
                                             1.889408e+1, 6.799781e+0 ],
                                           [ [ 8.403206e-6, 1.026766e-3 ],
                                             [ 2.802750e-3, 1.169698e-4 ],
                                             [ 4.333117e-3, 2.987095e-5 ],
                                             [ 4.163289e-2, 3.271682e-4 ] ] ) ) ] ),
                    matrix = CompactCorrelationMatrix(
                               12,
                               [ 2, 3, 3, 5, 5, 5, 6, 6, 6, 8,
                                 8, 8, 8, 9, 9, 9, 9 ],
                               [ 1, 1, 2, 1, 2, 4, 3, 4, 5, 1,
                                 2, 3, 7, 1, 2, 7, 8 ],
                               [ -795e-3, -945e-3, 665e-3, 15e-3, -25e-3, -25e-3, -15e-3,
                                   25e-3, -595e-3, -15e-3, 25e-3, 15e-3, -55e-3, -15e-3,
                                   15e-3, -65e-3, 165e-3 ], 2 ) )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = CompactRMatrixLimited.from_string( self.chunk, 2931, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = CompactRMatrixLimited( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
