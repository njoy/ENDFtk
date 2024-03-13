# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF28 import Section
from ENDFtk.MF28 import SubshellData
from ENDFtk.tree import Tape

class Test_ENDFtk_MF28_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 1.000000+3 9.992414-1          0          0          2          0 10028533     \n'
              ' 1.000000+0 0.000000+0          0          0         18          2 10028533     \n'
              ' 1.156100+4 2.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 10028533     \n'
              ' 3.000000+0 2.000000+0 9.506600+4 7.500000-1 0.000000+0 0.000000+0 10028533     \n'
              ' 4.000000+0 3.000000+0 9.892800+4 2.500000-1 0.000000+0 0.000000+0 10028533     \n'
              ' 2.000000+0 0.000000+0          0          0         12          1 10028533     \n'
              ' 2.000000+3 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 10028533     \n'
              ' 1.000000+0 0.000000+0 1.000000+3 1.000000+0 0.000000+0 0.000000+0 10028533     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                   10028  0     \n'
    valid_FEND = '                                                                   100 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                   10028  1     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 533, chunk.MT )
            self.assertEqual( 533, chunk.section_number )
            self.assertEqual( 1000, chunk.ZA )
            self.assertEqual( 1000, chunk.target_identifier )
            self.assertEqual( 0.9992414, chunk.AWR )
            self.assertEqual( 0.9992414, chunk.atomic_weight_ratio )

            shell = chunk.subshells[0]
            self.assertEqual( 1, shell.SUBI )
            self.assertEqual( 1, shell.subshell_designator )
            self.assertEqual( 2, shell.NTR )
            self.assertEqual( 2, shell.number_transitions )
            self.assertEqual( 1.156100e+4, shell.EBI )
            self.assertEqual( 1.156100e+4, shell.subshell_binding_energy )
            self.assertEqual( 2, shell.ELN )
            self.assertEqual( 2, shell.number_subshell_electrons )
            self.assertEqual( 2, len( shell.SUBJ ) )
            self.assertEqual( 2, len( shell.SUBK ) )
            self.assertEqual( 2, len( shell.ETR ) )
            self.assertEqual( 2, len( shell.FTR ) )
            self.assertEqual( 3, shell.SUBJ[0] )
            self.assertEqual( 4, shell.SUBJ[1] )
            self.assertEqual( 2, shell.SUBK[0] )
            self.assertEqual( 3, shell.SUBK[1] )
            self.assertEqual( 9.5066e+4, shell.ETR[0] )
            self.assertEqual( 9.8928e+4, shell.ETR[1] )
            self.assertEqual( 0.75, shell.FTR[0] )
            self.assertEqual( 0.25, shell.FTR[1] )

            shell = chunk.subshells[1]
            self.assertEqual( 2, shell.SUBI )
            self.assertEqual( 2, shell.subshell_designator )
            self.assertEqual( 1, shell.NTR )
            self.assertEqual( 1, shell.number_transitions )
            self.assertEqual( 2000., shell.EBI )
            self.assertEqual( 2000., shell.subshell_binding_energy )
            self.assertEqual( 1, shell.ELN )
            self.assertEqual( 1, shell.number_subshell_electrons )
            self.assertEqual( 1, len( shell.SUBJ ) )
            self.assertEqual( 1, len( shell.SUBK ) )
            self.assertEqual( 1, len( shell.ETR ) )
            self.assertEqual( 1, len( shell.FTR ) )
            self.assertEqual( 1, shell.SUBJ[0] )
            self.assertEqual( 0, shell.SUBK[0] )
            self.assertEqual( 1000., shell.ETR[0] )
            self.assertEqual( 1., shell.FTR[0] )

            self.assertEqual( 8, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 100, 28 ) )

        # the data is given explicitly
        chunk = Section( mt = 533, zaid = 1000, awr = 0.9992414,
                         subshells =
                             [ SubshellData( 1, 1.1561e+4, 2, [ 3, 4 ], [ 2, 3 ],
                                             [ 9.5066e+4, 9.8928e+4 ], [ 0.75, 0.25 ] ),
                               SubshellData( 2, 2000., 1, [ 1 ], [ 0 ], [ 1000. ], [ 1. ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 100 ).file( 28 ).section( 533 ).parse()

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
