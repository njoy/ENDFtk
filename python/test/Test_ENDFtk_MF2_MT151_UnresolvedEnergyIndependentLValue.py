# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import UnresolvedEnergyIndependentLValue

class Test_ENDFtk_MF2_MT151_UnresolvedEnergyIndependentLValue( unittest.TestCase ) :
    """Unit test for the UnresolvedEnergyIndependentLValue class."""

    chunk = ( ' 1.387090+2 0.000000+0          1          0         12          25655 2151     \n'
              ' 4.400000+3 5.000000-1 1.000000+0 5.280000-1 9.000000-2 0.000000+05655 2151     \n'
              ' 2.200000+3 1.500000+0 2.000000+0 2.640000-1 9.100000-2 0.000000+05655 2151     \n' )

    invalid = ( ' 1.387090+2 0.000000+0          1          0         12          15655 2151     \n'
                ' 4.400000+3 5.000000-1 1.000000+0 5.280000-1 9.000000-2 0.000000+05655 2151     \n'
                ' 2.200000+3 1.500000+0 2.000000+0 2.640000-1 9.100000-2 0.000000+05655 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 138.709, chunk.AWRI )
            self.assertAlmostEqual( 138.709, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.L )
            self.assertEqual( 1, chunk.orbital_momentum )

            self.assertEqual( 2, chunk.NJS )
            self.assertEqual( 2, chunk.number_spin_values )
            self.assertEqual( 2, len( chunk.AJ ) )
            self.assertEqual( 2, len( chunk.spin_values ) )
            self.assertEqual( 2, len( chunk.D ) )
            self.assertEqual( 2, len( chunk.average_level_spacings ) )
            self.assertEqual( 2, len( chunk.AMUN ) )
            self.assertEqual( 2, len( chunk.neutron_width_degrees_freedom ) )
            self.assertEqual( 2, len( chunk.AMUG ) )
            self.assertEqual( 2, len( chunk.gamma_width_degrees_freedom ) )
            self.assertEqual( 2, len( chunk.AMUF ) )
            self.assertEqual( 2, len( chunk.fission_width_degrees_freedom ) )
            self.assertEqual( 2, len( chunk.AMUX ) )
            self.assertEqual( 2, len( chunk.competitive_width_degrees_freedom ) )
            self.assertEqual( 2, len( chunk.GN ) )
            self.assertEqual( 2, len( chunk.average_neutron_widths ) )
            self.assertEqual( 2, len( chunk.GG ) )
            self.assertEqual( 2, len( chunk.average_gamma_widths ) )
            self.assertEqual( 2, len( chunk.GF ) )
            self.assertEqual( 2, len( chunk.average_fission_widths ) )
            self.assertEqual( 2, len( chunk.GX ) )
            self.assertEqual( 2, len( chunk.average_competitive_widths ) )
            #self.assertEqual( 2, len( chunk.jValues )

            self.assertAlmostEqual( 0.5, chunk.AJ[0] )
            self.assertAlmostEqual( 1.5, chunk.AJ[1] )
            self.assertAlmostEqual( 0.5, chunk.spin_values[0] )
            self.assertAlmostEqual( 1.5, chunk.spin_values[1] )
            self.assertEqual( 1, chunk.AMUN[0] )
            self.assertEqual( 2, chunk.AMUN[1] )
            self.assertEqual( 1, chunk.neutron_width_degrees_freedom[0] )
            self.assertEqual( 2, chunk.neutron_width_degrees_freedom[1] )
            self.assertEqual( 0, chunk.AMUG[0] )
            self.assertEqual( 0, chunk.AMUG[1] )
            self.assertEqual( 0, chunk.gamma_width_degrees_freedom[0] )
            self.assertEqual( 0, chunk.gamma_width_degrees_freedom[1] )
            self.assertEqual( 0, chunk.AMUF[0] )
            self.assertEqual( 0, chunk.AMUF[1] )
            self.assertEqual( 0, chunk.fission_width_degrees_freedom[0] )
            self.assertEqual( 0, chunk.fission_width_degrees_freedom[1] )
            self.assertEqual( 0, chunk.AMUX[0] )
            self.assertEqual( 0, chunk.AMUX[1] )
            self.assertEqual( 0, chunk.competitive_width_degrees_freedom[0] )
            self.assertEqual( 0, chunk.competitive_width_degrees_freedom[1] )
            self.assertAlmostEqual( 0.528, chunk.GN[0] )
            self.assertAlmostEqual( 0.264, chunk.GN[1] )
            self.assertAlmostEqual( 0.528, chunk.average_neutron_widths[0] )
            self.assertAlmostEqual( 0.264, chunk.average_neutron_widths[1] )
            self.assertAlmostEqual( 0.090, chunk.GG[0] )
            self.assertAlmostEqual( 0.091, chunk.GG[1] )
            self.assertAlmostEqual( 0.090, chunk.average_gamma_widths[0] )
            self.assertAlmostEqual( 0.091, chunk.average_gamma_widths[1] )
            self.assertAlmostEqual( 0., chunk.GF[0] )
            self.assertAlmostEqual( 0., chunk.GF[1] )
            self.assertAlmostEqual( 0., chunk.average_fission_widths[0] )
            self.assertAlmostEqual( 0., chunk.average_fission_widths[1] )
            self.assertAlmostEqual( 0., chunk.GX[0] )
            self.assertAlmostEqual( 0., chunk.GX[1] )
            self.assertAlmostEqual( 0., chunk.average_competitive_widths[0] )
            self.assertAlmostEqual( 0., chunk.average_competitive_widths[1] )

            # self.assertAlmostEqual( 0.5, chunk.jValues[0].AJ )
            # self.assertAlmostEqual( 1.5, chunk.jValues[1].AJ )
            # self.assertAlmostEqual( 0.5, chunk.jValues[0].spin )
            # self.assertAlmostEqual( 1.5, chunk.jValues[1].spin )
            # self.assertEqual( 1, chunk.jValues[0].AMUN )
            # self.assertEqual( 2, chunk.jValues[1].AMUN )
            # self.assertEqual( 1, chunk.jValues[0].neutron_width_degrees_freedom )
            # self.assertEqual( 2, chunk.jValues[1].neutron_width_degrees_freedom )
            # self.assertEqual( 0, chunk.jValues[0].AMUG )
            # self.assertEqual( 0, chunk.jValues[1].AMUG )
            # self.assertEqual( 0, chunk.jValues[0].gamma_width_degrees_freedom )
            # self.assertEqual( 0, chunk.jValues[1].gamma_width_degrees_freedom )
            # self.assertEqual( 0, chunk.jValues[0].AMUF )
            # self.assertEqual( 0, chunk.jValues[1].AMUF )
            # self.assertEqual( 0, chunk.jValues[0].fission_width_degrees_freedom )
            # self.assertEqual( 0, chunk.jValues[1].fission_width_degrees_freedom )
            # self.assertEqual( 0, chunk.jValues[0].AMUX )
            # self.assertEqual( 0, chunk.jValues[1].AMUX )
            # self.assertEqual( 0, chunk.jValues[0].competitive_width_degrees_freedom )
            # self.assertEqual( 0, chunk.jValues[1].competitive_width_degrees_freedom )
            # self.assertAlmostEqual( 0.528, chunk.jValues[0].GN )
            # self.assertAlmostEqual( 0.264, chunk.jValues[1].GN )
            # self.assertAlmostEqual( 0.528, chunk.jValues[0].averageNeutronWidth )
            # self.assertAlmostEqual( 0.264, chunk.jValues[1].averageNeutronWidth )
            # self.assertAlmostEqual( 0.090, chunk.jValues[0].GG )
            # self.assertAlmostEqual( 0.091, chunk.jValues[1].GG )
            # self.assertAlmostEqual( 0.090, chunk.jValues[0].averageGammaWidth )
            # self.assertAlmostEqual( 0.091, chunk.jValues[1].averageGammaWidth )
            # self.assertAlmostEqual( 0., chunk.jValues[0].GF )
            # self.assertAlmostEqual( 0., chunk.jValues[1].GF )
            # self.assertAlmostEqual( 0., chunk.jValues[0].averageFissionWidth )
            # self.assertAlmostEqual( 0., chunk.jValues[1].averageFissionWidth )
            # self.assertAlmostEqual( 0., chunk.jValues[0].GX )
            # self.assertAlmostEqual( 0., chunk.jValues[1].GX )
            # self.assertAlmostEqual( 0., chunk.jValues[0].averageCompetitiveWidth )
            # self.assertAlmostEqual( 0., chunk.jValues[1].averageCompetitiveWidth )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 5655, 2, 151 ) )

        # the data is given explicitly
        chunk = UnresolvedEnergyIndependentLValue(
                    awri = 1.387090e+2, l = 1,
                    d = [ 4400., 2200. ], spins = [ 0.5, 1.5 ], amun = [ 1, 2 ],
                    gn = [ 0.528, 0.264 ], gg = [ 0.09, 0.091 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = UnresolvedEnergyIndependentLValue.from_string( self.chunk, 5655, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = UnresolvedEnergyIndependentLValue( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # invalid TAB1
        with self.assertRaises( Exception ) :

            Section.from_string( self.invalid )

if __name__ == '__main__' :

    unittest.main()
