# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import UnresolvedEnergyDependentJValue

class Test_ENDFtk_MF2_MT151_UnresolvedEnergyDependentJValue( unittest.TestCase ) :
    """Unit test for the UnresolvedEnergyDependentJValue class."""

    chunk = ( ' 3.000000+0 0.000000+0          2          0         24          39228 2151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 1.000000+0 3.000000+0 2.000000+09228 2151     \n'
              ' 2.250000+3 1.058570+0 1.000000+0 9.567005-5 3.882094-2 2.893370-19228 2151     \n'
              ' 3.500000+3 1.055928+0 2.000000+0 9.510382-5 3.884319-2 2.893379-19228 2151     \n'
              ' 2.500000+4 1.011535+0 3.000000+0 8.847673-5 3.922727-2 2.893518-19228 2151     \n' )

    invalid = ( ' 3.000000+0 0.000000+0          2          0         20          49228 2151     \n'
                ' 0.000000+0 0.000000+0 0.000000+0 1.000000+0 3.000000+0 2.000000+09228 2151     \n'
                ' 2.250000+3 1.058570+0 1.000000+0 9.567005-5 3.882094-2 2.893370-19228 2151     \n'
                ' 3.500000+3 1.055928+0 2.000000+0 9.510382-5 3.884319-2 2.893379-19228 2151     \n'
                ' 2.500000+4 1.011535+0                                            9228 2151     \n' )

    invalid_njs = ' 3.000000+0 0.000000+0          2          0          6          09228 2151     \n'

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 3., chunk.AJ )
            self.assertAlmostEqual( 3., chunk.spin )

            self.assertEqual( 1, chunk.AMUN )
            self.assertEqual( 1, chunk.neutron_width_degrees_freedom )
            self.assertEqual( 3, chunk.AMUG )
            self.assertEqual( 3, chunk.gamma_width_degrees_freedom )
            self.assertEqual( 2, chunk.AMUF )
            self.assertEqual( 2, chunk.fission_width_degrees_freedom )
            self.assertEqual( 0, chunk.AMUX )
            self.assertEqual( 0, chunk.competitive_width_degrees_freedom )

            self.assertEqual( 2, chunk.INT )

            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 3, chunk.boundaries[0] )

            self.assertEqual( 3, chunk.NE )
            self.assertEqual( 3, len( chunk.ES ) )
            self.assertEqual( 3, len( chunk.energies ) )
            self.assertEqual( 3, len( chunk.D ) )
            self.assertEqual( 3, len( chunk.average_level_spacings ) )
            self.assertEqual( 3, len( chunk.GN ) )
            self.assertEqual( 3, len( chunk.average_neutron_widths ) )
            self.assertEqual( 3, len( chunk.GG ) )
            self.assertEqual( 3, len( chunk.average_gamma_widths ) )
            self.assertEqual( 3, len( chunk.GF ) )
            self.assertEqual( 3, len( chunk.average_fission_widths ) )
            self.assertEqual( 3, len( chunk.GX ) )
            self.assertEqual( 3, len( chunk.average_competitive_widths ) )

            self.assertAlmostEqual( 2.25e+3, chunk.ES[0] )
            self.assertAlmostEqual( 3.5e+3, chunk.ES[1] )
            self.assertAlmostEqual( 2.5e+4, chunk.ES[2] )
            self.assertAlmostEqual( 2.25e+3, chunk.energies[0] )
            self.assertAlmostEqual( 3.5e+3, chunk.energies[1] )
            self.assertAlmostEqual( 2.5e+4, chunk.energies[2] )
            self.assertAlmostEqual( 1.05857, chunk.D[0] )
            self.assertAlmostEqual( 1.055928, chunk.D[1] )
            self.assertAlmostEqual( 1.011535, chunk.D[2] )
            self.assertAlmostEqual( 1.05857, chunk.average_level_spacings[0] )
            self.assertAlmostEqual( 1.055928, chunk.average_level_spacings[1] )
            self.assertAlmostEqual( 1.011535, chunk.average_level_spacings[2] )
            self.assertAlmostEqual( 9.567005e-5, chunk.GN[0] )
            self.assertAlmostEqual( 9.510382e-5, chunk.GN[1] )
            self.assertAlmostEqual( 8.847673e-5, chunk.GN[2] )
            self.assertAlmostEqual( 9.567005e-5, chunk.average_neutron_widths[0] )
            self.assertAlmostEqual( 9.510382e-5, chunk.average_neutron_widths[1] )
            self.assertAlmostEqual( 8.847673e-5, chunk.average_neutron_widths[2] )
            self.assertAlmostEqual( 3.882094e-2, chunk.GG[0] )
            self.assertAlmostEqual( 3.884319e-2, chunk.GG[1] )
            self.assertAlmostEqual( 3.922727e-2, chunk.GG[2] )
            self.assertAlmostEqual( 3.882094e-2, chunk.average_gamma_widths[0] )
            self.assertAlmostEqual( 3.884319e-2, chunk.average_gamma_widths[1] )
            self.assertAlmostEqual( 3.922727e-2, chunk.average_gamma_widths[2] )
            self.assertAlmostEqual( 2.893370e-1, chunk.GF[0] )
            self.assertAlmostEqual( 2.893379e-1, chunk.GF[1] )
            self.assertAlmostEqual( 2.893518e-1, chunk.GF[2] )
            self.assertAlmostEqual( 2.893370e-1, chunk.average_fission_widths[0] )
            self.assertAlmostEqual( 2.893379e-1, chunk.average_fission_widths[1] )
            self.assertAlmostEqual( 2.893518e-1, chunk.average_fission_widths[2] )
            self.assertAlmostEqual( 1., chunk.GX[0] )
            self.assertAlmostEqual( 2., chunk.GX[1] )
            self.assertAlmostEqual( 3., chunk.GX[2] )
            self.assertAlmostEqual( 1., chunk.average_competitive_widths[0] )
            self.assertAlmostEqual( 2., chunk.average_competitive_widths[1] )
            self.assertAlmostEqual( 3., chunk.average_competitive_widths[2] )

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 2, 151 ) )

        # the data is given explicitly
        chunk = UnresolvedEnergyDependentJValue(
                    interpolation = 2, spin = 3., amux = 0, amun = 1,
                    amug = 3, amuf = 2, energies = [ 2.25e+3, 3.5e+3,  2.5e+4 ],
                    d = [ 1.05857, 1.055928, 1.011535 ], gx = [ 1., 2., 3. ],
                    gn = [ 9.567005e-5, 9.510382e-5, 8.847673e-5 ],
                    gg = [ 3.882094e-2, 3.884319e-2, 3.922727e-2 ],
                    gf = [ 2.893370e-1, 2.893379e-1, 2.893518e-1 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = UnresolvedEnergyDependentJValue.from_string( self.chunk, 9228, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = UnresolvedEnergyDependentJValue( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = UnresolvedEnergyDependentJValue(
                        interpolation = 2, spin = 3., amux = 0, amun = 1,
                        amug = 3, amuf = 2, energies = [ 2.25e+3, 3.5e+3,  2.5e+4 ],
                        d = [ 1.05857, 1.055928, 1.011535 ], gx = [ 1., 2., 3. ],
                        gn = [ 9.567005e-5, 9.510382e-5, 8.847673e-5 ],
                        gg = [ 3.882094e-2, 3.884319e-2, 3.922727e-2 ],
                        gf = [ 2.893370e-1, 2.893379e-1 ] )

        with self.assertRaises( Exception ) :

            chunk = UnresolvedEnergyDependentJValue(
                        interpolation = 2, spin = 3., amux = 0, amun = 1,
                        amug = 3, amuf = 2, energies = [], d = [], gx = [],
                        gn = [], gg = [], gf = [] )

        with self.assertRaises( Exception ) :

            Section.from_string( self.invalid, 9228, 2, 151 )

        with self.assertRaises( Exception ) :

            Section.from_string( self.no_fission, 9228, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
