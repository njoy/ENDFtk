# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF7.MT451 import ElementInformation

class Test_ENDFtk_MF7_MT451_ElementInformation( unittest.TestCase ) :
    """Unit test for the ElementInformation class."""

    chunk = ( ' 0.000000+0 0.000000+0          2          0         18          3  22 7451     \n'
              ' 8.016000+3 0.000000+0 9.976200-1 1.585751+1 3.744801+0 0.000000+0  22 7451     \n'
              ' 8.017000+3 0.000000+0 3.800000-4 1.685310+1 3.642671+0 0.000000+0  22 7451     \n'
              ' 8.018000+3 0.000000+0 2.000000-3 1.784450+1 3.846775+0 0.000000+0  22 7451     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          2          0         17          3  22 7451     \n'
                ' 8.016000+3 0.000000+0 9.976200-1 1.585751+1 3.744801+0 0.000000+0  22 7451     \n'
                ' 8.017000+3 0.000000+0 3.800000-4 1.685310+1 3.642671+0 0.000000+0  22 7451     \n'
                ' 8.018000+3 0.000000+0 2.000000-3 1.784450+1 3.846775+0             22 7451     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.NAS )
            self.assertEqual( 2, chunk.number_atoms )
            self.assertEqual( 3, chunk.NI )
            self.assertEqual( 3, chunk.number_isotopes )

            self.assertEqual( 3, len( chunk.ZAI ) )
            self.assertEqual( 3, len( chunk.isotope_identifiers ) )
            self.assertEqual( 3, len( chunk.LISI ) )
            self.assertEqual( 3, len( chunk.isomeric_states ) )
            self.assertEqual( 3, len( chunk.AFI ) )
            self.assertEqual( 3, len( chunk.abundances ) )
            self.assertEqual( 3, len( chunk.AWRI ) )
            self.assertEqual( 3, len( chunk.atomic_weight_ratios ) )
            self.assertEqual( 3, len( chunk.SFI ) )
            self.assertEqual( 3, len( chunk.free_scattering_cross_sections ) )
            self.assertEqual( 8016, chunk.ZAI[0] )
            self.assertEqual( 8017, chunk.ZAI[1] )
            self.assertEqual( 8018, chunk.ZAI[2] )
            self.assertEqual( 8016, chunk.isotope_identifiers[0] )
            self.assertEqual( 8017, chunk.isotope_identifiers[1] )
            self.assertEqual( 8018, chunk.isotope_identifiers[2] )
            self.assertEqual( 0, chunk.LISI[0] )
            self.assertEqual( 0, chunk.LISI[1] )
            self.assertEqual( 0, chunk.LISI[2] )
            self.assertEqual( 0, chunk.isomeric_states[0] )
            self.assertEqual( 0, chunk.isomeric_states[1] )
            self.assertEqual( 0, chunk.isomeric_states[2] )
            self.assertAlmostEqual( 9.976200e-1, chunk.AFI[0] )
            self.assertAlmostEqual( 3.800000e-4, chunk.AFI[1] )
            self.assertAlmostEqual( 2.000000e-3, chunk.AFI[2] )
            self.assertAlmostEqual( 9.976200e-1, chunk.abundances[0] )
            self.assertAlmostEqual( 3.800000e-4, chunk.abundances[1] )
            self.assertAlmostEqual( 2.000000e-3, chunk.abundances[2] )
            self.assertAlmostEqual( 15.85751, chunk.AWRI[0] )
            self.assertAlmostEqual( 16.85310, chunk.AWRI[1] )
            self.assertAlmostEqual( 17.84450, chunk.AWRI[2] )
            self.assertAlmostEqual( 15.85751, chunk.atomic_weight_ratios[0] )
            self.assertAlmostEqual( 16.85310, chunk.atomic_weight_ratios[1] )
            self.assertAlmostEqual( 17.84450, chunk.atomic_weight_ratios[2] )
            self.assertAlmostEqual( 3.744801, chunk.SFI[0] )
            self.assertAlmostEqual( 3.642671, chunk.SFI[1] )
            self.assertAlmostEqual( 3.846775, chunk.SFI[2] )
            self.assertAlmostEqual( 3.744801, chunk.free_scattering_cross_sections[0] )
            self.assertAlmostEqual( 3.642671, chunk.free_scattering_cross_sections[1] )
            self.assertAlmostEqual( 3.846775, chunk.free_scattering_cross_sections[2] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 22, 7, 451 ) )

        # the data is given explicitly
        chunk = ElementInformation( atoms = 2,
                                    identifiers = [ 8016, 8017, 8018 ],
                                    states = [ 0, 0, 0 ],
                                    abundances = [ .99762, 3.8e-4, 2e-3 ],
                                    weights = [ 15.85751, 16.8531, 17.8445 ],
                                    xs = [ 3.744801, 3.642671, 3.846775 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ElementInformation.from_string( self.chunk, 22, 7, 451 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ElementInformation( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = ElementInformation.from_string( self.invalid, 9228, 8, 454 )

if __name__ == '__main__' :

    unittest.main()
