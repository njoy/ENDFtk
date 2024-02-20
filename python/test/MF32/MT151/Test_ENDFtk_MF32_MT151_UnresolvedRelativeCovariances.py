# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import UnresolvedRelativeCovariances
from ENDFtk.MF32.MT151 import UnresolvedCovarianceMatrix
from ENDFtk.MF32.MT151 import UnresolvedLValue

class Test_ENDFtk_MF2_MT151_UnresolvedRelativeCovariances( unittest.TestCase ) :
    """Unit test for the UnresolvedRelativeCovariances class."""

    chunk = ( ' 1.500000+0 5.100000-1          0          0          2          0102832151     \n'
              ' 2.081350+1 0.000000+0          0          0         12          2102832151     \n'
              ' 4.737450+4 1.000000+0 1.439310+0 9.325340-1 0.000000+0 0.000000+0102832151     \n'
              ' 4.004950+4 2.000000+0 1.216770+0 3.312740-1 0.000000+0 0.000000+0102832151     \n'
              ' 2.081350+1 0.000000+0          1          0         24          4102832151     \n'
              ' 1.197338+5 0.000000+0 1.115620+1 8.083210-2 0.000000+0 0.000000+0102832151     \n'
              ' 4.737450+4 1.000000+0 3.543470+0 1.048490+0 0.000000+0 0.000000+0102832151     \n'
              ' 4.004950+4 2.000000+0 2.995580+0 3.577760-1 0.000000+0 0.000000+0102832151     \n'
              ' 4.784325+4 3.000000+0 4.457810+0 4.728190-1 0.000000+0 0.000000+0102832151     \n'
              ' 0.000000+0 0.000000+0          2          0         78         12102832151     \n'
              ' 1.000000-4 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102832151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102832151     \n'
              ' 1.000000-2 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102832151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 1.000000-4102832151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102832151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 1.000000-2 0.000000+0 0.000000+0102832151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102832151     \n'
              ' 1.000000-4 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0102832151     \n'
              ' 0.000000+0 0.000000+0 1.000000-2 0.000000+0 0.000000+0 0.000000+0102832151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 1.000000-4 0.000000+0 0.000000+0102832151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 1.000000-2 0.000000+0 0.000000+0102832151     \n'
              ' 0.000000+0 0.000000+0 1.000000-4 0.000000+0 0.000000+0 0.000000+0102832151     \n'
              ' 1.000000-2 0.000000+0 0.000000+0 1.000000-4 0.000000+0 1.000000-2102832151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.LRU )
            self.assertEqual( 2, chunk.type )
            self.assertEqual( 1, chunk.LRF )
            self.assertEqual( 1, chunk.representation )
            self.assertEqual( False, chunk.LFW )
            self.assertEqual( False, chunk.average_fission_width_flag )

            self.assertAlmostEqual( 1.5, chunk.SPI )
            self.assertAlmostEqual( 1.5, chunk.spin )
            self.assertAlmostEqual( 0.51, chunk.AP )
            self.assertAlmostEqual( 0.51, chunk.scattering_radius )

            self.assertEqual( 2, chunk.NLS )

            lvalue0 = chunk.l_values[0]
            self.assertAlmostEqual( 20.8135, lvalue0.AWRI )
            self.assertAlmostEqual( 20.8135, lvalue0.atomic_weight_ratio )
            self.assertEqual( 0, lvalue0.L )
            self.assertEqual( 0, lvalue0.orbital_momentum )

            self.assertEqual( 2, lvalue0.NJS )
            self.assertEqual( 2, lvalue0.number_spin_values )
            self.assertEqual( 2, len( lvalue0.AJ ) )
            self.assertEqual( 2, len( lvalue0.spin_values ) )
            self.assertEqual( 2, len( lvalue0.D ) )
            self.assertEqual( 2, len( lvalue0.average_level_spacings ) )
            self.assertEqual( 2, len( lvalue0.GNO ) )
            self.assertEqual( 2, len( lvalue0.average_neutron_widths ) )
            self.assertEqual( 2, len( lvalue0.GG ) )
            self.assertEqual( 2, len( lvalue0.average_gamma_widths ) )
            self.assertEqual( 2, len( lvalue0.GF ) )
            self.assertEqual( 2, len( lvalue0.average_fission_widths ) )
            self.assertEqual( 2, len( lvalue0.GX ) )
            self.assertEqual( 2, len( lvalue0.average_competitive_widths ) )
            # self.assertEqual( 2, len( lvalue0.j_values ) )

            self.assertAlmostEqual( 1., lvalue0.AJ[0] )
            self.assertAlmostEqual( 2., lvalue0.AJ[1] )
            self.assertAlmostEqual( 1., lvalue0.spin_values[0] )
            self.assertAlmostEqual( 2., lvalue0.spin_values[1] )
            self.assertAlmostEqual( 4.737450e+4, lvalue0.D[0] )
            self.assertAlmostEqual( 4.004950e+4, lvalue0.D[1] )
            self.assertAlmostEqual( 4.737450e+4, lvalue0.average_level_spacings[0] )
            self.assertAlmostEqual( 4.004950e+4, lvalue0.average_level_spacings[1] )
            self.assertAlmostEqual( 1.43931, lvalue0.GNO[0] )
            self.assertAlmostEqual( 1.21677, lvalue0.GNO[1] )
            self.assertAlmostEqual( 1.43931, lvalue0.average_neutron_widths[0] )
            self.assertAlmostEqual( 1.21677, lvalue0.average_neutron_widths[1] )
            self.assertAlmostEqual( 9.325340e-1, lvalue0.GG[0] )
            self.assertAlmostEqual( 3.312740e-1, lvalue0.GG[1] )
            self.assertAlmostEqual( 9.325340e-1, lvalue0.average_gamma_widths[0] )
            self.assertAlmostEqual( 3.312740e-1, lvalue0.average_gamma_widths[1] )
            self.assertAlmostEqual( 0., lvalue0.GF[0] )
            self.assertAlmostEqual( 0., lvalue0.GF[1] )
            self.assertAlmostEqual( 0., lvalue0.average_fission_widths[0] )
            self.assertAlmostEqual( 0., lvalue0.average_fission_widths[1] )
            self.assertAlmostEqual( 0., lvalue0.GX[0] )
            self.assertAlmostEqual( 0., lvalue0.GX[1] )
            self.assertAlmostEqual( 0., lvalue0.average_competitive_widths[0] )
            self.assertAlmostEqual( 0., lvalue0.average_competitive_widths[1] )

            # self.assertAlmostEqual( 1., lvalue0.jValues[0].AJ )
            # self.assertAlmostEqual( 2., lvalue0.jValues[1].AJ )
            # self.assertAlmostEqual( 1., lvalue0.jValues[0].spin )
            # self.assertAlmostEqual( 2., lvalue0.jValues[1].spin )
            # self.assertAlmostEqual( 4.737450e+4, lvalue0.jValues[0].D )
            # self.assertAlmostEqual( 4.004950e+4, lvalue0.jValues[1].D )
            # self.assertAlmostEqual( 4.737450e+4, lvalue0.jValues[0].average_level_spacing )
            # self.assertAlmostEqual( 4.004950e+4, lvalue0.jValues[1].average_level_spacing )
            # self.assertAlmostEqual( 1.43931, lvalue0.jValues[0].GNO )
            # self.assertAlmostEqual( 1.21677, lvalue0.jValues[1].GNO )
            # self.assertAlmostEqual( 1.43931, lvalue0.jValues[0].average_neutron_width )
            # self.assertAlmostEqual( 1.21677, lvalue0.jValues[1].average_neutron_width )
            # self.assertAlmostEqual( 9.325340e-1, lvalue0.jValues[0].GG )
            # self.assertAlmostEqual( 3.312740e-1, lvalue0.jValues[1].GG )
            # self.assertAlmostEqual( 9.325340e-1, lvalue0.jValues[0].average_gamma_width )
            # self.assertAlmostEqual( 3.312740e-1, lvalue0.jValues[1].average_gamma_width )
            # self.assertAlmostEqual( 0., lvalue0.jValues[0].GF )
            # self.assertAlmostEqual( 0., lvalue0.jValues[1].GF )
            # self.assertAlmostEqual( 0., lvalue0.jValues[0].average_fission_width )
            # self.assertAlmostEqual( 0., lvalue0.jValues[1].average_fission_width )
            # self.assertAlmostEqual( 0., lvalue0.jValues[0].GX )
            # self.assertAlmostEqual( 0., lvalue0.jValues[1].GX )
            # self.assertAlmostEqual( 0., lvalue0.jValues[0].average_competitive_width )
            # self.assertAlmostEqual( 0., lvalue0.jValues[1].average_competitive_width )

            lvalue1 = chunk.l_values[1]
            self.assertAlmostEqual( 20.8135, lvalue1.AWRI )
            self.assertAlmostEqual( 20.8135, lvalue1.atomic_weight_ratio )
            self.assertEqual( 1, lvalue1.L )
            self.assertEqual( 1, lvalue1.orbital_momentum )

            self.assertEqual( 4, lvalue1.NJS )
            self.assertEqual( 4, lvalue1.number_spin_values )
            self.assertEqual( 4, len( lvalue1.AJ ) )
            self.assertEqual( 4, len( lvalue1.spin_values ) )
            self.assertEqual( 4, len( lvalue1.D ) )
            self.assertEqual( 4, len( lvalue1.average_level_spacings ) )
            self.assertEqual( 4, len( lvalue1.GNO ) )
            self.assertEqual( 4, len( lvalue1.average_neutron_widths ) )
            self.assertEqual( 4, len( lvalue1.GG ) )
            self.assertEqual( 4, len( lvalue1.average_gamma_widths ) )
            self.assertEqual( 4, len( lvalue1.GF ) )
            self.assertEqual( 4, len( lvalue1.average_fission_widths ) )
            self.assertEqual( 4, len( lvalue1.GX ) )
            self.assertEqual( 4, len( lvalue1.average_competitive_widths ) )
            # self.assertEqual( 4, len( lvalue1.j_values ) )

            self.assertAlmostEqual( 0., lvalue1.AJ[0] )
            self.assertAlmostEqual( 1., lvalue1.AJ[1] )
            self.assertAlmostEqual( 2., lvalue1.AJ[2] )
            self.assertAlmostEqual( 3., lvalue1.AJ[3] )
            self.assertAlmostEqual( 0., lvalue1.spin_values[0] )
            self.assertAlmostEqual( 1., lvalue1.spin_values[1] )
            self.assertAlmostEqual( 2., lvalue1.spin_values[2] )
            self.assertAlmostEqual( 3., lvalue1.spin_values[3] )
            self.assertAlmostEqual( 1.197338e+5, lvalue1.D[0] )
            self.assertAlmostEqual( 4.737450e+4, lvalue1.D[1] )
            self.assertAlmostEqual( 4.004950e+4, lvalue1.D[2] )
            self.assertAlmostEqual( 4.784325e+4, lvalue1.D[3] )
            self.assertAlmostEqual( 1.197338e+5, lvalue1.average_level_spacings[0] )
            self.assertAlmostEqual( 4.737450e+4, lvalue1.average_level_spacings[1] )
            self.assertAlmostEqual( 4.004950e+4, lvalue1.average_level_spacings[2] )
            self.assertAlmostEqual( 4.784325e+4, lvalue1.average_level_spacings[3] )
            self.assertAlmostEqual( 1.115620e+1, lvalue1.GNO[0] )
            self.assertAlmostEqual( 3.543470e+0, lvalue1.GNO[1] )
            self.assertAlmostEqual( 2.995580e+0, lvalue1.GNO[2] )
            self.assertAlmostEqual( 4.457810e+0, lvalue1.GNO[3] )
            self.assertAlmostEqual( 1.115620e+1, lvalue1.average_neutron_widths[0] )
            self.assertAlmostEqual( 3.543470e+0, lvalue1.average_neutron_widths[1] )
            self.assertAlmostEqual( 2.995580e+0, lvalue1.average_neutron_widths[2] )
            self.assertAlmostEqual( 4.457810e+0, lvalue1.average_neutron_widths[3] )
            self.assertAlmostEqual( 8.083210e-2, lvalue1.GG[0] )
            self.assertAlmostEqual( 1.048490e+0, lvalue1.GG[1] )
            self.assertAlmostEqual( 3.577760e-1, lvalue1.GG[2] )
            self.assertAlmostEqual( 4.728190e-1, lvalue1.GG[3] )
            self.assertAlmostEqual( 8.083210e-2, lvalue1.average_gamma_widths[0] )
            self.assertAlmostEqual( 1.048490e+0, lvalue1.average_gamma_widths[1] )
            self.assertAlmostEqual( 3.577760e-1, lvalue1.average_gamma_widths[2] )
            self.assertAlmostEqual( 4.728190e-1, lvalue1.average_gamma_widths[3] )
            self.assertAlmostEqual( 0., lvalue1.GF[0] )
            self.assertAlmostEqual( 0., lvalue1.GF[1] )
            self.assertAlmostEqual( 0., lvalue1.GF[2] )
            self.assertAlmostEqual( 0., lvalue1.GF[3] )
            self.assertAlmostEqual( 0., lvalue1.average_fission_widths[0] )
            self.assertAlmostEqual( 0., lvalue1.average_fission_widths[1] )
            self.assertAlmostEqual( 0., lvalue1.average_fission_widths[2] )
            self.assertAlmostEqual( 0., lvalue1.average_fission_widths[3] )
            self.assertAlmostEqual( 0., lvalue1.GX[0] )
            self.assertAlmostEqual( 0., lvalue1.GX[1] )
            self.assertAlmostEqual( 0., lvalue1.GX[2] )
            self.assertAlmostEqual( 0., lvalue1.GX[3] )
            self.assertAlmostEqual( 0., lvalue1.average_competitive_widths[0] )
            self.assertAlmostEqual( 0., lvalue1.average_competitive_widths[1] )
            self.assertAlmostEqual( 0., lvalue1.average_competitive_widths[2] )
            self.assertAlmostEqual( 0., lvalue1.average_competitive_widths[3] )

            # self.assertAlmostEqual( 0., lvalue1.jValues[0].AJ )
            # self.assertAlmostEqual( 1., lvalue1.jValues[1].AJ )
            # self.assertAlmostEqual( 2., lvalue1.jValues[2].AJ )
            # self.assertAlmostEqual( 3., lvalue1.jValues[3].AJ )
            # self.assertAlmostEqual( 0., lvalue1.jValues[0].spin )
            # self.assertAlmostEqual( 1., lvalue1.jValues[1].spin )
            # self.assertAlmostEqual( 2., lvalue1.jValues[2].spin )
            # self.assertAlmostEqual( 3., lvalue1.jValues[3].spin )
            # self.assertAlmostEqual( 1.197338e+5, lvalue1.jValues[0].D )
            # self.assertAlmostEqual( 4.737450e+4, lvalue1.jValues[1].D )
            # self.assertAlmostEqual( 4.004950e+4, lvalue1.jValues[2].D )
            # self.assertAlmostEqual( 4.784325e+4, lvalue1.jValues[3].D )
            # self.assertAlmostEqual( 1.197338e+5, lvalue1.jValues[0].average_level_spacing )
            # self.assertAlmostEqual( 4.737450e+4, lvalue1.jValues[1].average_level_spacing )
            # self.assertAlmostEqual( 4.004950e+4, lvalue1.jValues[2].average_level_spacing )
            # self.assertAlmostEqual( 4.784325e+4, lvalue1.jValues[3].average_level_spacing )
            # self.assertAlmostEqual( 1.115620e+1, lvalue1.jValues[0].GNO )
            # self.assertAlmostEqual( 3.543470e+0, lvalue1.jValues[1].GNO )
            # self.assertAlmostEqual( 2.995580e+0, lvalue1.jValues[2].GNO )
            # self.assertAlmostEqual( 4.457810e+0, lvalue1.jValues[3].GNO )
            # self.assertAlmostEqual( 1.115620e+1, lvalue1.jValues[0].average_neutron_width )
            # self.assertAlmostEqual( 3.543470e+0, lvalue1.jValues[1].average_neutron_width )
            # self.assertAlmostEqual( 2.995580e+0, lvalue1.jValues[2].average_neutron_width )
            # self.assertAlmostEqual( 4.457810e+0, lvalue1.jValues[3].average_neutron_width )
            # self.assertAlmostEqual( 8.083210e-2, lvalue1.jValues[0].GG )
            # self.assertAlmostEqual( 1.048490e+0, lvalue1.jValues[1].GG )
            # self.assertAlmostEqual( 3.577760e-1, lvalue1.jValues[2].GG )
            # self.assertAlmostEqual( 4.728190e-1, lvalue1.jValues[3].GG )
            # self.assertAlmostEqual( 8.083210e-2, lvalue1.jValues[0].average_gamma_width )
            # self.assertAlmostEqual( 1.048490e+0, lvalue1.jValues[1].average_gamma_width )
            # self.assertAlmostEqual( 3.577760e-1, lvalue1.jValues[2].average_gamma_width )
            # self.assertAlmostEqual( 4.728190e-1, lvalue1.jValues[3].average_gamma_width )
            # self.assertAlmostEqual( 0., lvalue1.jValues[0].GF )
            # self.assertAlmostEqual( 0., lvalue1.jValues[1].GF )
            # self.assertAlmostEqual( 0., lvalue1.jValues[2].GF )
            # self.assertAlmostEqual( 0., lvalue1.jValues[3].GF )
            # self.assertAlmostEqual( 0., lvalue1.jValues[0].average_fission_width )
            # self.assertAlmostEqual( 0., lvalue1.jValues[1].average_fission_width )
            # self.assertAlmostEqual( 0., lvalue1.jValues[2].average_fission_width )
            # self.assertAlmostEqual( 0., lvalue1.jValues[3].average_fission_width )
            # self.assertAlmostEqual( 0., lvalue1.jValues[0].GX )
            # self.assertAlmostEqual( 0., lvalue1.jValues[1].GX )
            # self.assertAlmostEqual( 0., lvalue1.jValues[2].GX )
            # self.assertAlmostEqual( 0., lvalue1.jValues[3].GX )
            # self.assertAlmostEqual( 0., lvalue1.jValues[0].average_competitive_width )
            # self.assertAlmostEqual( 0., lvalue1.jValues[1].average_competitive_width )
            # self.assertAlmostEqual( 0., lvalue1.jValues[2].average_competitive_width )
            # self.assertAlmostEqual( 0., lvalue1.jValues[3].average_competitive_width )

            matrix = chunk.covariance_matrix
            self.assertEqual( 2, matrix.MPAR )
            self.assertEqual( 2, matrix.number_average_parameters )

            self.assertEqual( 12, matrix.NPAR )
            self.assertEqual( 12, matrix.covariance_matrix_order )

            self.assertEqual( 78, len( matrix.covariance_matrix ) )
            self.assertEqual( 78, matrix.NVS )
            self.assertEqual( 78, matrix.number_values )

            self.assertAlmostEqual( 1.000000e-4, matrix.covariance_matrix[ 0] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[ 1] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[ 2] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[ 3] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[ 4] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[ 5] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[ 6] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[ 7] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[ 8] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[ 9] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[10] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[11] )
            self.assertAlmostEqual( 1.000000e-2, matrix.covariance_matrix[12] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[13] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[14] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[15] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[16] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[17] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[18] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[19] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[20] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[21] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[22] )
            self.assertAlmostEqual( 1.000000e-4, matrix.covariance_matrix[23] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[24] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[25] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[26] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[27] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[28] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[29] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[30] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[31] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[32] )
            self.assertAlmostEqual( 1.000000e-2, matrix.covariance_matrix[33] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[34] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[35] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[36] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[37] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[38] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[39] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[40] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[41] )
            self.assertAlmostEqual( 1.000000e-4, matrix.covariance_matrix[42] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[43] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[44] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[45] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[46] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[47] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[48] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[49] )
            self.assertAlmostEqual( 1.000000e-2, matrix.covariance_matrix[50] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[51] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[52] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[53] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[54] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[55] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[56] )
            self.assertAlmostEqual( 1.000000e-4, matrix.covariance_matrix[57] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[58] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[59] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[60] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[61] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[62] )
            self.assertAlmostEqual( 1.000000e-2, matrix.covariance_matrix[63] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[64] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[65] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[66] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[67] )
            self.assertAlmostEqual( 1.000000e-4, matrix.covariance_matrix[68] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[69] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[70] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[71] )
            self.assertAlmostEqual( 1.000000e-2, matrix.covariance_matrix[72] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[73] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[74] )
            self.assertAlmostEqual( 1.000000e-4, matrix.covariance_matrix[75] )
            self.assertAlmostEqual( 0., matrix.covariance_matrix[76] )
            self.assertAlmostEqual( 1.000000e-2, matrix.covariance_matrix[77] )

            self.assertEqual( 23, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 1028, 32, 151 ) )

        # the data is given explicitly
        chunk = UnresolvedRelativeCovariances(
                    spin = 1.5, ap = 0.51,
                    lvalues =
                        [ UnresolvedLValue(
                              20.8135, 0,
                              [ 1., 2. ], [ 4.737450e+4, 4.004950e+4 ],
                              [ 1.43931, 1.21677 ], [ 9.325340e-1, 3.312740e-1 ],
                              [ 0., 0. ], [ 0., 0. ] ),
                          UnresolvedLValue(
                              20.8135, 1,
                              [ 0., 1., 2., 3. ],
                              [ 1.197338e+5, 4.737450e+4, 4.004950e+4, 4.784325e+4 ],
                              [ 1.115620e+1, 3.543470e+0, 2.995580e+0, 4.457810e+0 ],
                              [ 8.083210e-2, 1.048490e+0, 3.577760e-1, 4.728190e-1 ],
                              [ 0., 0., 0., 0. ], [ 0., 0., 0., 0. ] ) ],
                    matrix = UnresolvedCovarianceMatrix(
                                 2,
                                 [  1.000000e-4, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0,
                                    0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0,
                                    1.000000e-2, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0,
                                    0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 1.000000e-4,
                                    0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0,
                                    0.000000e+0, 0.000000e+0, 0.000000e+0, 1.000000e-2, 0.000000e+0, 0.000000e+0,
                                    0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0,
                                    1.000000e-4, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0, 0.000000e+0,
                                    0.000000e+0, 0.000000e+0, 1.000000e-2, 0.000000e+0, 0.000000e+0, 0.000000e+0,
                                    0.000000e+0, 0.000000e+0, 0.000000e+0, 1.000000e-4, 0.000000e+0, 0.000000e+0,
                                    0.000000e+0, 0.000000e+0, 0.000000e+0, 1.000000e-2, 0.000000e+0, 0.000000e+0,
                                    0.000000e+0, 0.000000e+0, 1.000000e-4, 0.000000e+0, 0.000000e+0, 0.000000e+0,
                                    1.000000e-2, 0.000000e+0, 0.000000e+0, 1.000000e-4, 0.000000e+0, 1.000000e-2 ] ) )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = UnresolvedRelativeCovariances.from_string( self.chunk, 1028, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = UnresolvedRelativeCovariances( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
