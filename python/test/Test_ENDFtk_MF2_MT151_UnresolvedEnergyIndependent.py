# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import UnresolvedEnergyIndependent
from ENDFtk.MF2.MT151 import UnresolvedEnergyIndependentLValue

class Test_ENDFtk_MF2_MT151_UnresolvedEnergyIndependent( unittest.TestCase ) :
    """Unit test for the UnresolvedEnergyIndependent class."""

    chunk = ( ' 0.000000+0 6.233000-1          0          0          3          05655 2151     \n'
              ' 1.387090+2 0.000000+0          0          0          6          15655 2151     \n'
              ' 4.400000+3 5.000000-1 1.000000+0 4.400000-1 5.000000-2 0.000000+05655 2151     \n'
              ' 1.387090+2 0.000000+0          1          0         12          25655 2151     \n'
              ' 4.400000+3 5.000000-1 1.000000+0 5.280000-1 9.000000-2 0.000000+05655 2151     \n'
              ' 2.200000+3 1.500000+0 1.000000+0 2.640000-1 9.100000-2 0.000000+05655 2151     \n'
              ' 1.387090+2 0.000000+0          2          0         12          25655 2151     \n'
              ' 2.200000+3 1.500000+0 1.000000+0 3.300000-2 5.000000-2 0.000000+05655 2151     \n'
              ' 1.466670+3 2.500000+0 1.000000+0 2.200000-2 5.100000-2 0.000000+05655 2151     \n' )

    invalid = ( ' 0.000000+0 6.233000-1          0          0          0          05655 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.LRU )
            self.assertEqual( 2, chunk.type )
            self.assertEqual( 1, chunk.LRF )
            self.assertEqual( 1, chunk.representation )
            self.assertEqual( False, chunk.LFW )
            self.assertEqual( False, chunk.average_fission_width_flag )

            self.assertAlmostEqual( 0.0, chunk.SPI )
            self.assertAlmostEqual( 0.0, chunk.spin )
            self.assertAlmostEqual( 0.6233, chunk.AP )
            self.assertAlmostEqual( 0.6233, chunk.scattering_radius )
            self.assertEqual( False, chunk.LSSF )
            self.assertEqual( False, chunk.self_shielding_only )

            self.assertEqual( 3, chunk.NLS )

            lvalue0 = chunk.l_values[0]
            self.assertAlmostEqual( 138.709, lvalue0.AWRI )
            self.assertAlmostEqual( 138.709, lvalue0.atomic_weight_ratio )
            self.assertEqual( 0, lvalue0.L )
            self.assertEqual( 0, lvalue0.orbital_momentum )

            self.assertEqual( 1, lvalue0.NJS )
            self.assertEqual( 1, lvalue0.number_spin_values )
            self.assertEqual( 1, len( lvalue0.AJ ) )
            self.assertEqual( 1, len( lvalue0.spin_values ) )
            self.assertEqual( 1, len( lvalue0.D ) )
            self.assertEqual( 1, len( lvalue0.average_level_spacings ) )
            self.assertEqual( 1, len( lvalue0.AMUN ) )
            self.assertEqual( 1, len( lvalue0.neutron_width_degrees_freedom ) )
            self.assertEqual( 1, len( lvalue0.AMUG ) )
            self.assertEqual( 1, len( lvalue0.gamma_width_degrees_freedom ) )
            self.assertEqual( 1, len( lvalue0.AMUF ) )
            self.assertEqual( 1, len( lvalue0.fission_width_degrees_freedom ) )
            self.assertEqual( 1, len( lvalue0.AMUX ) )
            self.assertEqual( 1, len( lvalue0.competitive_width_degrees_freedom ) )
            self.assertEqual( 1, len( lvalue0.GN ) )
            self.assertEqual( 1, len( lvalue0.average_neutron_widths ) )
            self.assertEqual( 1, len( lvalue0.GG ) )
            self.assertEqual( 1, len( lvalue0.average_gamma_widths ) )
            self.assertEqual( 1, len( lvalue0.GF ) )
            self.assertEqual( 1, len( lvalue0.average_fission_widths ) )
            self.assertEqual( 1, len( lvalue0.GX ) )
            self.assertEqual( 1, len( lvalue0.average_competitive_widths ) )
            # self.assertEqual( 1, len( lvalue0.j_values ) )

            self.assertAlmostEqual( 0.5, lvalue0.AJ[0] )
            self.assertAlmostEqual( 0.5, lvalue0.spin_values[0] )
            self.assertAlmostEqual( 4400., lvalue0.D[0] )
            self.assertAlmostEqual( 4400., lvalue0.average_level_spacings[0] )
            self.assertEqual( 1, lvalue0.AMUN[0] )
            self.assertEqual( 1, lvalue0.neutron_width_degrees_freedom[0] )
            self.assertEqual( 0, lvalue0.AMUG[0] )
            self.assertEqual( 0, lvalue0.gamma_width_degrees_freedom[0] )
            self.assertEqual( 0, lvalue0.AMUF[0] )
            self.assertEqual( 0, lvalue0.fission_width_degrees_freedom[0] )
            self.assertEqual( 0, lvalue0.AMUX[0] )
            self.assertEqual( 0, lvalue0.competitive_width_degrees_freedom[0] )
            self.assertAlmostEqual( 0.44, lvalue0.GN[0] )
            self.assertAlmostEqual( 0.44, lvalue0.average_neutron_widths[0] )
            self.assertAlmostEqual( 0.05, lvalue0.GG[0] )
            self.assertAlmostEqual( 0.05, lvalue0.average_gamma_widths[0] )
            self.assertAlmostEqual( 0., lvalue0.GF[0] )
            self.assertAlmostEqual( 0., lvalue0.average_fission_widths[0] )
            self.assertAlmostEqual( 0., lvalue0.GX[0] )
            self.assertAlmostEqual( 0., lvalue0.average_competitive_widths[0] )

            # self.assertAlmostEqual( 0.5, lvalue0.j_values[0].AJ )
            # self.assertAlmostEqual( 0.5, lvalue0.j_values[0].spin )
            # self.assertAlmostEqual( 4400., lvalue0.j_values[0].D )
            # self.assertAlmostEqual( 4400., lvalue0.j_values[0].average_level_spacing )
            # self.assertEqual( 1, lvalue0.j_values[0].AMUN )
            # self.assertEqual( 1, lvalue0.j_values[0].neutron_width_degrees_freedom )
            # self.assertEqual( 0, lvalue0.j_values[0].AMUG )
            # self.assertEqual( 0, lvalue0.j_values[0].gamma_width_degrees_freedom )
            # self.assertEqual( 0, lvalue0.j_values[0].AMUF )
            # self.assertEqual( 0, lvalue0.j_values[0].fission_width_degrees_freedom )
            # self.assertEqual( 0, lvalue0.j_values[0].AMUX )
            # self.assertEqual( 0, lvalue0.j_values[0].competitive_width_degrees_freedom )
            # self.assertAlmostEqual( 0.44, lvalue0.j_values[0].GN )
            # self.assertAlmostEqual( 0.44, lvalue0.j_values[0].average_neutron_width )
            # self.assertAlmostEqual( 0.05, lvalue0.j_values[0].GG )
            # self.assertAlmostEqual( 0.05, lvalue0.j_values[0].average_gamma_width )
            # self.assertEqual( 0., lvalue0.j_values[0].GF )
            # self.assertEqual( 0., lvalue0.j_values[0].average_fission_width )
            # self.assertEqual( 0., lvalue0.j_values[0].GX )
            # self.assertEqual( 0., lvalue0.j_values[0].average_competitive_width )

            lvalue1 = chunk.l_values[1]
            self.assertAlmostEqual( 138.709, lvalue1.AWRI )
            self.assertAlmostEqual( 138.709, lvalue1.atomic_weight_ratio )
            self.assertEqual( 1, lvalue1.L )
            self.assertEqual( 1, lvalue1.orbital_momentum )

            self.assertEqual( 2, lvalue1.NJS )
            self.assertEqual( 2, lvalue1.number_spin_values )
            self.assertEqual( 2, len( lvalue1.AJ ) )
            self.assertEqual( 2, len( lvalue1.spin_values ) )
            self.assertEqual( 2, len( lvalue1.D ) )
            self.assertEqual( 2, len( lvalue1.average_level_spacings ) )
            self.assertEqual( 2, len( lvalue1.AMUN ) )
            self.assertEqual( 2, len( lvalue1.neutron_width_degrees_freedom ) )
            self.assertEqual( 2, len( lvalue1.AMUG ) )
            self.assertEqual( 2, len( lvalue1.gamma_width_degrees_freedom ) )
            self.assertEqual( 2, len( lvalue1.AMUF ) )
            self.assertEqual( 2, len( lvalue1.fission_width_degrees_freedom ) )
            self.assertEqual( 2, len( lvalue1.AMUX ) )
            self.assertEqual( 2, len( lvalue1.competitive_width_degrees_freedom ) )
            self.assertEqual( 2, len( lvalue1.GN ) )
            self.assertEqual( 2, len( lvalue1.average_neutron_widths ) )
            self.assertEqual( 2, len( lvalue1.GG ) )
            self.assertEqual( 2, len( lvalue1.average_gamma_widths ) )
            self.assertEqual( 2, len( lvalue1.GF ) )
            self.assertEqual( 2, len( lvalue1.average_fission_widths ) )
            self.assertEqual( 2, len( lvalue1.GX ) )
            self.assertEqual( 2, len( lvalue1.average_competitive_widths ) )
            # self.assertEqual( 2, len( lvalue1.j_values ) )

            self.assertAlmostEqual( 0.5, lvalue1.AJ[0] )
            self.assertAlmostEqual( 1.5, lvalue1.AJ[1] )
            self.assertAlmostEqual( 0.5, lvalue1.spin_values[0] )
            self.assertAlmostEqual( 1.5, lvalue1.spin_values[1] )
            self.assertAlmostEqual( 4400., lvalue1.D[0] )
            self.assertAlmostEqual( 2200., lvalue1.D[1] )
            self.assertAlmostEqual( 4400., lvalue1.average_level_spacings[0] )
            self.assertAlmostEqual( 2200., lvalue1.average_level_spacings[1] )
            self.assertEqual( 1, lvalue1.AMUN[0] )
            self.assertEqual( 1, lvalue1.AMUN[1] )
            self.assertEqual( 1, lvalue1.neutron_width_degrees_freedom[0] )
            self.assertEqual( 1, lvalue1.neutron_width_degrees_freedom[1] )
            self.assertEqual( 0, lvalue1.AMUG[0] )
            self.assertEqual( 0, lvalue1.AMUG[1] )
            self.assertEqual( 0, lvalue1.gamma_width_degrees_freedom[0] )
            self.assertEqual( 0, lvalue1.gamma_width_degrees_freedom[1] )
            self.assertEqual( 0, lvalue1.AMUF[0] )
            self.assertEqual( 0, lvalue1.AMUF[1] )
            self.assertEqual( 0, lvalue1.fission_width_degrees_freedom[0] )
            self.assertEqual( 0, lvalue1.fission_width_degrees_freedom[1] )
            self.assertEqual( 0, lvalue1.AMUX[0] )
            self.assertEqual( 0, lvalue1.AMUX[1] )
            self.assertEqual( 0, lvalue1.competitive_width_degrees_freedom[0] )
            self.assertEqual( 0, lvalue1.competitive_width_degrees_freedom[1] )
            self.assertAlmostEqual( 0.528, lvalue1.GN[0] )
            self.assertAlmostEqual( 0.264, lvalue1.GN[1] )
            self.assertAlmostEqual( 0.528, lvalue1.average_neutron_widths[0] )
            self.assertAlmostEqual( 0.264, lvalue1.average_neutron_widths[1] )
            self.assertAlmostEqual( 0.090, lvalue1.GG[0] )
            self.assertAlmostEqual( 0.091, lvalue1.GG[1] )
            self.assertAlmostEqual( 0.090, lvalue1.average_gamma_widths[0] )
            self.assertAlmostEqual( 0.091, lvalue1.average_gamma_widths[1] )
            self.assertAlmostEqual( 0., lvalue1.GF[0] )
            self.assertAlmostEqual( 0., lvalue1.GF[1] )
            self.assertAlmostEqual( 0., lvalue1.average_fission_widths[0] )
            self.assertAlmostEqual( 0., lvalue1.average_fission_widths[1] )
            self.assertAlmostEqual( 0., lvalue1.GX[0] )
            self.assertAlmostEqual( 0., lvalue1.GX[1] )
            self.assertAlmostEqual( 0., lvalue1.average_competitive_widths[0] )
            self.assertAlmostEqual( 0., lvalue1.average_competitive_widths[1] )

            # self.assertAlmostEqual( 0.5, lvalue1.j_values[0].AJ )
            # self.assertAlmostEqual( 1.5, lvalue1.j_values[1].AJ )
            # self.assertAlmostEqual( 0.5, lvalue1.j_values[0].spin )
            # self.assertAlmostEqual( 1.5, lvalue1.j_values[1].spin )
            # self.assertAlmostEqual( 4400., lvalue1.j_values[0].D )
            # self.assertAlmostEqual( 2200., lvalue1.j_values[1].D )
            # self.assertAlmostEqual( 4400., lvalue1.j_values[0].average_level_spacing )
            # self.assertAlmostEqual( 2200., lvalue1.j_values[1].average_level_spacing )
            # self.assertEqual( 1, lvalue1.j_values[0].AMUN )
            # self.assertEqual( 1, lvalue1.j_values[1].AMUN )
            # self.assertEqual( 1, lvalue1.j_values[0].neutron_width_degrees_freedom )
            # self.assertEqual( 1, lvalue1.j_values[1].neutron_width_degrees_freedom )
            # self.assertEqual( 0, lvalue1.j_values[0].AMUG )
            # self.assertEqual( 0, lvalue1.j_values[1].AMUG )
            # self.assertEqual( 0, lvalue1.j_values[0].gamma_width_degrees_freedom )
            # self.assertEqual( 0, lvalue1.j_values[1].gamma_width_degrees_freedom )
            # self.assertEqual( 0, lvalue1.j_values[0].AMUF )
            # self.assertEqual( 0, lvalue1.j_values[1].AMUF )
            # self.assertEqual( 0, lvalue1.j_values[0].fission_width_degrees_freedom )
            # self.assertEqual( 0, lvalue1.j_values[1].fission_width_degrees_freedom )
            # self.assertEqual( 0, lvalue1.j_values[0].AMUX )
            # self.assertEqual( 0, lvalue1.j_values[1].AMUX )
            # self.assertEqual( 0, lvalue1.j_values[0].competitive_width_degrees_freedom )
            # self.assertEqual( 0, lvalue1.j_values[1].competitive_width_degrees_freedom )
            # self.assertAlmostEqual( 0.528, lvalue1.j_values[0].GN )
            # self.assertAlmostEqual( 0.264, lvalue1.j_values[1].GN )
            # self.assertAlmostEqual( 0.528, lvalue1.j_values[0].average_neutron_width )
            # self.assertAlmostEqual( 0.264, lvalue1.j_values[1].average_neutron_width )
            # self.assertAlmostEqual( 0.090, lvalue1.j_values[0].GG )
            # self.assertAlmostEqual( 0.091, lvalue1.j_values[1].GG )
            # self.assertAlmostEqual( 0.090, lvalue1.j_values[0].average_gamma_width )
            # self.assertAlmostEqual( 0.091, lvalue1.j_values[1].average_gamma_width )
            # self.assertEqual( 0., lvalue1.j_values[0].GF )
            # self.assertEqual( 0., lvalue1.j_values[1].GF )
            # self.assertEqual( 0., lvalue1.j_values[0].average_fission_width )
            # self.assertEqual( 0., lvalue1.j_values[1].average_fission_width )
            # self.assertEqual( 0., lvalue1.j_values[0].GX )
            # self.assertEqual( 0., lvalue1.j_values[1].GX )
            # self.assertEqual( 0., lvalue1.j_values[0].average_competitive_width )
            # self.assertEqual( 0., lvalue1.j_values[1].average_competitive_width )

            lvalue2 = chunk.l_values[2]
            self.assertAlmostEqual( 138.709, lvalue2.AWRI )
            self.assertAlmostEqual( 138.709, lvalue2.atomic_weight_ratio )
            self.assertEqual( 2, lvalue2.L )
            self.assertEqual( 2, lvalue2.orbital_momentum )

            self.assertEqual( 2, lvalue2.NJS )
            self.assertEqual( 2, lvalue2.number_spin_values )
            self.assertEqual( 2, len( lvalue2.AJ ) )
            self.assertEqual( 2, len( lvalue2.spin_values ) )
            self.assertEqual( 2, len( lvalue2.D ) )
            self.assertEqual( 2, len( lvalue2.average_level_spacings ) )
            self.assertEqual( 2, len( lvalue2.AMUN ) )
            self.assertEqual( 2, len( lvalue2.neutron_width_degrees_freedom ) )
            self.assertEqual( 2, len( lvalue2.AMUG ) )
            self.assertEqual( 2, len( lvalue2.gamma_width_degrees_freedom ) )
            self.assertEqual( 2, len( lvalue2.AMUF ) )
            self.assertEqual( 2, len( lvalue2.fission_width_degrees_freedom ) )
            self.assertEqual( 2, len( lvalue2.AMUX ) )
            self.assertEqual( 2, len( lvalue2.competitive_width_degrees_freedom ) )
            self.assertEqual( 2, len( lvalue2.GN ) )
            self.assertEqual( 2, len( lvalue2.average_neutron_widths ) )
            self.assertEqual( 2, len( lvalue2.GG ) )
            self.assertEqual( 2, len( lvalue2.average_gamma_widths ) )
            self.assertEqual( 2, len( lvalue2.GF ) )
            self.assertEqual( 2, len( lvalue2.average_fission_widths ) )
            self.assertEqual( 2, len( lvalue2.GX ) )
            self.assertEqual( 2, len( lvalue2.average_competitive_widths ) )
            # self.assertEqual( 2, len( lvalue2.j_values ) )

            self.assertAlmostEqual( 1.5, lvalue2.AJ[0] )
            self.assertAlmostEqual( 2.5, lvalue2.AJ[1] )
            self.assertAlmostEqual( 1.5, lvalue2.spin_values[0] )
            self.assertAlmostEqual( 2.5, lvalue2.spin_values[1] )
            self.assertAlmostEqual( 2200., lvalue2.D[0] )
            self.assertAlmostEqual( 1466.67, lvalue2.D[1] )
            self.assertAlmostEqual( 2200., lvalue2.average_level_spacings[0] )
            self.assertAlmostEqual( 1466.67, lvalue2.average_level_spacings[1] )
            self.assertEqual( 1, lvalue2.AMUN[0] )
            self.assertEqual( 1, lvalue2.AMUN[1] )
            self.assertEqual( 1, lvalue2.neutron_width_degrees_freedom[0] )
            self.assertEqual( 1, lvalue2.neutron_width_degrees_freedom[1] )
            self.assertEqual( 0, lvalue2.AMUG[0] )
            self.assertEqual( 0, lvalue2.AMUG[1] )
            self.assertEqual( 0, lvalue2.gamma_width_degrees_freedom[0] )
            self.assertEqual( 0, lvalue2.gamma_width_degrees_freedom[1] )
            self.assertEqual( 0, lvalue2.AMUF[0] )
            self.assertEqual( 0, lvalue2.AMUF[1] )
            self.assertEqual( 0, lvalue2.fission_width_degrees_freedom[0] )
            self.assertEqual( 0, lvalue2.fission_width_degrees_freedom[1] )
            self.assertEqual( 0, lvalue2.AMUX[0] )
            self.assertEqual( 0, lvalue2.AMUX[1] )
            self.assertEqual( 0, lvalue2.competitive_width_degrees_freedom[0] )
            self.assertEqual( 0, lvalue2.competitive_width_degrees_freedom[1] )
            self.assertAlmostEqual( 0.033, lvalue2.GN[0] )
            self.assertAlmostEqual( 0.022, lvalue2.GN[1] )
            self.assertAlmostEqual( 0.033, lvalue2.average_neutron_widths[0] )
            self.assertAlmostEqual( 0.022, lvalue2.average_neutron_widths[1] )
            self.assertAlmostEqual( 0.050, lvalue2.GG[0] )
            self.assertAlmostEqual( 0.051, lvalue2.GG[1] )
            self.assertAlmostEqual( 0.050, lvalue2.average_gamma_widths[0] )
            self.assertAlmostEqual( 0.051, lvalue2.average_gamma_widths[1] )
            self.assertAlmostEqual( 0., lvalue2.GF[0] )
            self.assertAlmostEqual( 0., lvalue2.GF[1] )
            self.assertAlmostEqual( 0., lvalue2.average_fission_widths[0] )
            self.assertAlmostEqual( 0., lvalue2.average_fission_widths[1] )
            self.assertAlmostEqual( 0., lvalue2.GX[0] )
            self.assertAlmostEqual( 0., lvalue2.GX[1] )
            self.assertAlmostEqual( 0., lvalue2.average_competitive_widths[0] )
            self.assertAlmostEqual( 0., lvalue2.average_competitive_widths[1] )

            # self.assertAlmostEqual( 1.5, lvalue2.j_values[0].AJ )
            # self.assertAlmostEqual( 2.5, lvalue2.j_values[1].AJ )
            # self.assertAlmostEqual( 1.5, lvalue2.j_values[0].spin )
            # self.assertAlmostEqual( 2.5, lvalue2.j_values[1].spin )
            # self.assertAlmostEqual( 2200., lvalue2.j_values[0].D )
            # self.assertAlmostEqual( 1466.67, lvalue2.j_values[1].D )
            # self.assertAlmostEqual( 2200., lvalue2.j_values[0].average_level_spacing )
            # self.assertAlmostEqual( 1466.67, lvalue2.j_values[1].average_level_spacing )
            # self.assertEqual( 1, lvalue2.j_values[0].AMUN )
            # self.assertEqual( 1, lvalue2.j_values[1].AMUN )
            # self.assertEqual( 1, lvalue2.j_values[0].neutron_width_degrees_freedom )
            # self.assertEqual( 1, lvalue2.j_values[1].neutron_width_degrees_freedom )
            # self.assertEqual( 0, lvalue2.j_values[0].AMUG )
            # self.assertEqual( 0, lvalue2.j_values[1].AMUG )
            # self.assertEqual( 0, lvalue2.j_values[0].gamma_width_degrees_freedom )
            # self.assertEqual( 0, lvalue2.j_values[1].gamma_width_degrees_freedom )
            # self.assertEqual( 0, lvalue2.j_values[0].AMUF )
            # self.assertEqual( 0, lvalue2.j_values[1].AMUF )
            # self.assertEqual( 0, lvalue2.j_values[0].fission_width_degrees_freedom )
            # self.assertEqual( 0, lvalue2.j_values[1].fission_width_degrees_freedom )
            # self.assertEqual( 0, lvalue2.j_values[0].AMUX )
            # self.assertEqual( 0, lvalue2.j_values[1].AMUX )
            # self.assertEqual( 0, lvalue2.j_values[0].competitive_width_degrees_freedom )
            # self.assertEqual( 0, lvalue2.j_values[1].competitive_width_degrees_freedom )
            # self.assertAlmostEqual( 0.033, lvalue2.j_values[0].GN )
            # self.assertAlmostEqual( 0.022, lvalue2.j_values[1].GN )
            # self.assertAlmostEqual( 0.033, lvalue2.j_values[0].average_neutron_width )
            # self.assertAlmostEqual( 0.022, lvalue2.j_values[1].average_neutron_width )
            # self.assertAlmostEqual( 0.050, lvalue2.j_values[0].GG )
            # self.assertAlmostEqual( 0.051, lvalue2.j_values[1].GG )
            # self.assertAlmostEqual( 0.050, lvalue2.j_values[0].average_gamma_width )
            # self.assertAlmostEqual( 0.051, lvalue2.j_values[1].average_gamma_width )
            # self.assertAlmostEqual( 0., lvalue2.j_values[0].GF )
            # self.assertAlmostEqual( 0., lvalue2.j_values[1].GF )
            # self.assertAlmostEqual( 0., lvalue2.j_values[0].average_fission_width )
            # self.assertAlmostEqual( 0., lvalue2.j_values[1].average_fission_width )
            # self.assertAlmostEqual( 0., lvalue2.j_values[0].GX )
            # self.assertAlmostEqual( 0., lvalue2.j_values[1].GX )
            # self.assertAlmostEqual( 0., lvalue2.j_values[0].average_competitive_width )
            # self.assertAlmostEqual( 0., lvalue2.j_values[1].average_competitive_width )

            self.assertEqual( 9, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 5655, 2, 151 ) )

        # the data is given explicitly
        chunk = UnresolvedEnergyIndependent(
                    spin = 0.0, ap = 0.6233, lssf = False,
                    lvalues = [ UnresolvedEnergyIndependentLValue(
                                  138.709, 0, [ 0.5 ], [ 4400. ], [ 1 ], [ 0.44 ], [ 0.05 ] ),
                                UnresolvedEnergyIndependentLValue(
                                  138.709, 1, [ 0.5, 1.5 ], [ 4400., 2200. ], [ 1, 1 ],
                                  [ 0.528, 0.264 ], [ 0.09, 0.091 ] ),
                                UnresolvedEnergyIndependentLValue(
                                  138.709, 2, [ 1.5, 2.5 ], [ 2200., 1466.67 ],
                                  [ 1, 1 ], [ 0.033, 0.022 ], [ 0.05, 0.051 ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = UnresolvedEnergyIndependent.from_string( self.chunk, 5655, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = UnresolvedEnergyIndependent( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = UnresolvedEnergyIndependent( spin = 0.0, ap = 0.6233, lssf = False, lvalues = [] )

        with self.assertRaises( Exception ) :

            chunk = UnresolvedEnergyIndependent.from_string( self.invalid, 5655, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
