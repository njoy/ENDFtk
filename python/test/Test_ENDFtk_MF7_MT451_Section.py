# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF7.MT451 import Section
from ENDFtk.MF7.MT451 import ElementInformation
from ENDFtk.tree import Tape

class Test_ENDFtk_MF7_MT451_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 1.220000+2 1.500000+1          1          0          0          0  22 7451     \n'
              ' 0.000000+0 0.000000+0          2          0         18          3  22 7451     \n'
              ' 8.016000+3 0.000000+0 9.976200-1 1.585751+1 3.744801+0 0.000000+0  22 7451     \n'
              ' 8.017000+3 0.000000+0 3.800000-4 1.685310+1 3.642671+0 0.000000+0  22 7451     \n'
              ' 8.018000+3 0.000000+0 2.000000-3 1.784450+1 3.846775+0 0.000000+0  22 7451     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                    22 7  0     \n'
    valid_FEND = '                                                                    22 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                    22 7451     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 451, chunk.MT )
            self.assertEqual( 451, chunk.section_number )

            self.assertAlmostEqual( 122., chunk.ZA )
            self.assertAlmostEqual( 15., chunk.AWR )
            self.assertAlmostEqual( 15., chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.NA )
            self.assertEqual( 1, chunk.number_elements )

            self.assertEqual( 2, chunk.elements[0].NAS )
            self.assertEqual( 2, chunk.elements[0].number_atoms )
            self.assertEqual( 3, chunk.elements[0].NI )
            self.assertEqual( 3, chunk.elements[0].number_isotopes )

            self.assertEqual( 3, len( chunk.elements[0].ZAI ) )
            self.assertEqual( 3, len( chunk.elements[0].isotope_identifiers ) )
            self.assertEqual( 3, len( chunk.elements[0].LISI ) )
            self.assertEqual( 3, len( chunk.elements[0].isomeric_states ) )
            self.assertEqual( 3, len( chunk.elements[0].AFI ) )
            self.assertEqual( 3, len( chunk.elements[0].abundances ) )
            self.assertEqual( 3, len( chunk.elements[0].AWRI ) )
            self.assertEqual( 3, len( chunk.elements[0].atomic_weight_ratios ) )
            self.assertEqual( 3, len( chunk.elements[0].SFI ) )
            self.assertEqual( 3, len( chunk.elements[0].free_scattering_cross_sections ) )
            self.assertEqual( 8016, chunk.elements[0].ZAI[0] )
            self.assertEqual( 8017, chunk.elements[0].ZAI[1] )
            self.assertEqual( 8018, chunk.elements[0].ZAI[2] )
            self.assertEqual( 8016, chunk.elements[0].isotope_identifiers[0] )
            self.assertEqual( 8017, chunk.elements[0].isotope_identifiers[1] )
            self.assertEqual( 8018, chunk.elements[0].isotope_identifiers[2] )
            self.assertEqual( 0, chunk.elements[0].LISI[0] )
            self.assertEqual( 0, chunk.elements[0].LISI[1] )
            self.assertEqual( 0, chunk.elements[0].LISI[2] )
            self.assertEqual( 0, chunk.elements[0].isomeric_states[0] )
            self.assertEqual( 0, chunk.elements[0].isomeric_states[1] )
            self.assertEqual( 0, chunk.elements[0].isomeric_states[2] )
            self.assertAlmostEqual( 9.976200e-1, chunk.elements[0].AFI[0] )
            self.assertAlmostEqual( 3.800000e-4, chunk.elements[0].AFI[1] )
            self.assertAlmostEqual( 2.000000e-3, chunk.elements[0].AFI[2] )
            self.assertAlmostEqual( 9.976200e-1, chunk.elements[0].abundances[0] )
            self.assertAlmostEqual( 3.800000e-4, chunk.elements[0].abundances[1] )
            self.assertAlmostEqual( 2.000000e-3, chunk.elements[0].abundances[2] )
            self.assertAlmostEqual( 15.85751, chunk.elements[0].AWRI[0] )
            self.assertAlmostEqual( 16.85310, chunk.elements[0].AWRI[1] )
            self.assertAlmostEqual( 17.84450, chunk.elements[0].AWRI[2] )
            self.assertAlmostEqual( 15.85751, chunk.elements[0].atomic_weight_ratios[0] )
            self.assertAlmostEqual( 16.85310, chunk.elements[0].atomic_weight_ratios[1] )
            self.assertAlmostEqual( 17.84450, chunk.elements[0].atomic_weight_ratios[2] )
            self.assertAlmostEqual( 3.744801, chunk.elements[0].SFI[0] )
            self.assertAlmostEqual( 3.642671, chunk.elements[0].SFI[1] )
            self.assertAlmostEqual( 3.846775, chunk.elements[0].SFI[2] )
            self.assertAlmostEqual( 3.744801, chunk.elements[0].free_scattering_cross_sections[0] )
            self.assertAlmostEqual( 3.642671, chunk.elements[0].free_scattering_cross_sections[1] )
            self.assertAlmostEqual( 3.846775, chunk.elements[0].free_scattering_cross_sections[2] )

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND, chunk.to_string( 22, 7 ) )

        # the data is given explicitly
        chunk = Section( zaid = 122., awr = 15.,
                         element = ElementInformation(
                                     2,
                                     [ 8016, 8017, 8018 ], [ 0, 0, 0 ],
                                     [ .99762, 3.8e-4, 2e-3 ],
                                     [ 15.85751, 16.8531, 17.8445 ],
                                     [ 3.744801, 3.642671, 3.846775 ] ) )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 22 ).file( 7 ).section( 451 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk( self, copy )


    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
