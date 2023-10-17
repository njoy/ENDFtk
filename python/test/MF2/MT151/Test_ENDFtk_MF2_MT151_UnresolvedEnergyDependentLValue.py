# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import UnresolvedEnergyDependentLValue
from ENDFtk.MF2.MT151 import UnresolvedEnergyDependentJValue

class Test_ENDFtk_MF2_MT151_UnresolvedEnergyDependentLValue( unittest.TestCase ) :
    """Unit test for the UnresolvedEnergyDependentLValue class."""

    chunk = ( ' 8.913540+1 0.000000+0          1          0          2          03843 2151     \n'
              ' 5.000000-1 0.000000+0          5          0         24          33843 2151     \n'
              ' 0.000000+0 0.000000+0 4.000000+0 3.000000+0 2.000000+0 1.000000+03843 2151     \n'
              ' 6.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n'
              ' 7.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n'
              ' 8.000000+3 1.240600+4 0.000000+0 6.723800+0 2.050000-1 0.000000+03843 2151     \n'
              ' 1.500000+0 0.000000+0          5          0         18          23843 2151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 1.000000+0 4.000000+0 2.000000+03843 2151     \n'
              ' 6.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+03843 2151     \n'
              ' 8.000000+3 6.202800+3 0.000000+0 3.361900+0 2.050000-1 0.000000+03843 2151     \n' )

    invalid = ( ' 2.379920+2 0.000000+0          1          0          0          03843 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 89.1354, chunk.AWRI )
            self.assertAlmostEqual( 89.1354, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.L )
            self.assertEqual( 1, chunk.orbital_momentum )
            self.assertEqual( 2, chunk.NJS )
            self.assertEqual( 2, chunk.number_spin_values )

            jvalue10 = chunk.j_values[0]
            self.assertAlmostEqual( 0.5, jvalue10.AJ )
            self.assertAlmostEqual( 0.5, jvalue10.spin )

            self.assertEqual( 3, jvalue10.AMUN )
            self.assertEqual( 3, jvalue10.neutron_width_degrees_freedom )
            self.assertEqual( 2, jvalue10.AMUG )
            self.assertEqual( 2, jvalue10.gamma_width_degrees_freedom )
            self.assertEqual( 1, jvalue10.AMUF )
            self.assertEqual( 1, jvalue10.fission_width_degrees_freedom )
            self.assertEqual( 4, jvalue10.AMUX )
            self.assertEqual( 4, jvalue10.competitive_width_degrees_freedom )

            self.assertEqual( 5, jvalue10.INT )

            self.assertEqual( 1, jvalue10.NR )
            self.assertEqual( 1, len( jvalue10.interpolants ) )
            self.assertEqual( 1, len( jvalue10.boundaries ) )
            self.assertEqual( 5, jvalue10.interpolants[0] )
            self.assertEqual( 3, jvalue10.boundaries[0] )

            self.assertEqual( 3, jvalue10.NE )
            self.assertEqual( 3, len( jvalue10.ES ) )
            self.assertEqual( 3, len( jvalue10.energies ) )
            self.assertEqual( 3, len( jvalue10.D ) )
            self.assertEqual( 3, len( jvalue10.average_level_spacings ) )
            self.assertEqual( 3, len( jvalue10.GN ) )
            self.assertEqual( 3, len( jvalue10.average_neutron_widths ) )
            self.assertEqual( 3, len( jvalue10.GG ) )
            self.assertEqual( 3, len( jvalue10.average_gamma_widths ) )
            self.assertEqual( 3, len( jvalue10.GF ) )
            self.assertEqual( 3, len( jvalue10.average_fission_widths ) )
            self.assertEqual( 3, len( jvalue10.GX ) )
            self.assertEqual( 3, len( jvalue10.average_competitive_widths ) )

            self.assertAlmostEqual( 6000., jvalue10.ES[0] )
            self.assertAlmostEqual( 7000., jvalue10.ES[1] )
            self.assertAlmostEqual( 8000., jvalue10.ES[2] )
            self.assertAlmostEqual( 6000., jvalue10.energies[0] )
            self.assertAlmostEqual( 7000., jvalue10.energies[1] )
            self.assertAlmostEqual( 8000., jvalue10.energies[2] )
            self.assertAlmostEqual( 12406., jvalue10.D[0] )
            self.assertAlmostEqual( 12406., jvalue10.D[1] )
            self.assertAlmostEqual( 12406., jvalue10.D[2] )
            self.assertAlmostEqual( 12406., jvalue10.average_level_spacings[0] )
            self.assertAlmostEqual( 12406., jvalue10.average_level_spacings[1] )
            self.assertAlmostEqual( 12406., jvalue10.average_level_spacings[2] )
            self.assertAlmostEqual( 6.7238, jvalue10.GN[0] )
            self.assertAlmostEqual( 6.7238, jvalue10.GN[1] )
            self.assertAlmostEqual( 6.7238, jvalue10.GN[2] )
            self.assertAlmostEqual( 6.7238, jvalue10.average_neutron_widths[0] )
            self.assertAlmostEqual( 6.7238, jvalue10.average_neutron_widths[1] )
            self.assertAlmostEqual( 6.7238, jvalue10.average_neutron_widths[2] )
            self.assertAlmostEqual( 0.205, jvalue10.GG[0] )
            self.assertAlmostEqual( 0.205, jvalue10.GG[1] )
            self.assertAlmostEqual( 0.205, jvalue10.GG[2] )
            self.assertAlmostEqual( 0.205, jvalue10.average_gamma_widths[0] )
            self.assertAlmostEqual( 0.205, jvalue10.average_gamma_widths[1] )
            self.assertAlmostEqual( 0.205, jvalue10.average_gamma_widths[2] )
            self.assertAlmostEqual( 0., jvalue10.GF[0] )
            self.assertAlmostEqual( 0., jvalue10.GF[1] )
            self.assertAlmostEqual( 0., jvalue10.GF[2] )
            self.assertAlmostEqual( 0., jvalue10.average_fission_widths[0] )
            self.assertAlmostEqual( 0., jvalue10.average_fission_widths[1] )
            self.assertAlmostEqual( 0., jvalue10.average_fission_widths[2] )
            self.assertAlmostEqual( 0., jvalue10.GX[0] )
            self.assertAlmostEqual( 0., jvalue10.GX[1] )
            self.assertAlmostEqual( 0., jvalue10.GX[2] )
            self.assertAlmostEqual( 0., jvalue10.average_competitive_widths[0] )
            self.assertAlmostEqual( 0., jvalue10.average_competitive_widths[1] )
            self.assertAlmostEqual( 0., jvalue10.average_competitive_widths[2] )

            jvalue11 = chunk.j_values[1]
            self.assertAlmostEqual( 1.5, jvalue11.AJ )
            self.assertAlmostEqual( 1.5, jvalue11.spin )

            self.assertEqual( 1, jvalue11.AMUN )
            self.assertEqual( 1, jvalue11.neutron_width_degrees_freedom )
            self.assertEqual( 4, jvalue11.AMUG )
            self.assertEqual( 4, jvalue11.gamma_width_degrees_freedom )
            self.assertEqual( 2, jvalue11.AMUF )
            self.assertEqual( 2, jvalue11.fission_width_degrees_freedom )
            self.assertEqual( 0, jvalue11.AMUX )
            self.assertEqual( 0, jvalue11.competitive_width_degrees_freedom )

            self.assertEqual( 5, jvalue11.INT )

            self.assertEqual( 1, jvalue11.NR )
            self.assertEqual( 1, len( jvalue11.interpolants ) )
            self.assertEqual( 1, len( jvalue11.boundaries ) )
            self.assertEqual( 5, jvalue11.interpolants[0] )
            self.assertEqual( 2, jvalue11.boundaries[0] )

            self.assertEqual( 2, jvalue11.NE )
            self.assertEqual( 2, len( jvalue11.ES ) )
            self.assertEqual( 2, len( jvalue11.energies ) )
            self.assertEqual( 2, len( jvalue11.D ) )
            self.assertEqual( 2, len( jvalue11.average_level_spacings ) )
            self.assertEqual( 2, len( jvalue11.GN ) )
            self.assertEqual( 2, len( jvalue11.average_neutron_widths ) )
            self.assertEqual( 2, len( jvalue11.GG ) )
            self.assertEqual( 2, len( jvalue11.average_gamma_widths ) )
            self.assertEqual( 2, len( jvalue11.GF ) )
            self.assertEqual( 2, len( jvalue11.average_fission_widths ) )
            self.assertEqual( 2, len( jvalue11.GX ) )
            self.assertEqual( 2, len( jvalue11.average_competitive_widths ) )

            self.assertAlmostEqual( 6000., jvalue11.ES[0] )
            self.assertAlmostEqual( 8000., jvalue11.ES[1] )
            self.assertAlmostEqual( 6000., jvalue11.energies[0] )
            self.assertAlmostEqual( 8000., jvalue11.energies[1] )
            self.assertAlmostEqual( 6202.8, jvalue11.D[0] )
            self.assertAlmostEqual( 6202.8, jvalue11.D[1] )
            self.assertAlmostEqual( 6202.8, jvalue11.average_level_spacings[0] )
            self.assertAlmostEqual( 6202.8, jvalue11.average_level_spacings[1] )
            self.assertAlmostEqual( 3.3619, jvalue11.GN[0] )
            self.assertAlmostEqual( 3.3619, jvalue11.GN[1] )
            self.assertAlmostEqual( 3.3619, jvalue11.average_neutron_widths[0] )
            self.assertAlmostEqual( 3.3619, jvalue11.average_neutron_widths[1] )
            self.assertAlmostEqual( 0.205, jvalue11.GG[0] )
            self.assertAlmostEqual( 0.205, jvalue11.GG[1] )
            self.assertAlmostEqual( 0.205, jvalue11.average_gamma_widths[0] )
            self.assertAlmostEqual( 0.205, jvalue11.average_gamma_widths[1] )
            self.assertAlmostEqual( 0., jvalue11.GF[0] )
            self.assertAlmostEqual( 0., jvalue11.GF[1] )
            self.assertAlmostEqual( 0., jvalue11.average_fission_widths[0] )
            self.assertAlmostEqual( 0., jvalue11.average_fission_widths[1] )
            self.assertAlmostEqual( 0., jvalue11.GX[0] )
            self.assertAlmostEqual( 0., jvalue11.GX[1] )
            self.assertAlmostEqual( 0., jvalue11.average_competitive_widths[0] )
            self.assertAlmostEqual( 0., jvalue11.average_competitive_widths[1] )

            self.assertEqual( 10, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 3843, 2, 151 ) )

        # the data is given explicitly
        chunk = UnresolvedEnergyDependentLValue(
                    awri = 89.13540, l = 1,
                    jvalues =
                        [ UnresolvedEnergyDependentJValue(
                              0.5, 3, 2, 1, 4, 5,
                              [ 6000., 7000., 8000. ], [ 12406., 12406., 12406. ],
                              [ 6.7238, 6.7238, 6.7238 ], [ 0.205, 0.205, 0.205 ],
                              [ 0., 0., 0. ], [ 0., 0., 0. ] ),
                          UnresolvedEnergyDependentJValue(
                              1.5, 1, 4, 2, 0, 5,
                              [ 6000., 8000. ], [ 6202.8, 6202.8 ],
                              [ 3.3619, 3.3619 ], [ 0.205, 0.205 ],
                              [ 0., 0. ], [ 0., 0. ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = UnresolvedEnergyDependentLValue.from_string( self.chunk, 3843, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = UnresolvedEnergyDependentLValue( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = UnresolvedEnergyDependentLValue( awri = 89.13540, l = 1, jvalues = [] )

        with self.assertRaises( Exception ) :

            chunk = UnresolvedEnergyDependentLValue.from_string( self.invalid, 3843, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
