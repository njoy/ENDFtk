"""
MF34 - covariances for angular distributions
"""
import ENDFtk
from __future__ import annotations
import typing
__all__: list[str] = ['File', 'LegendreBlock', 'ReactionBlock', 'Section']
class File:
    """
    MF34 file - covariances for angular distributions
    """
    @staticmethod
    def from_string(file: str) -> File:
        """
        Read the file from a string
        
        An exception is raised if something goes wrong while reading the
        file
        
        Arguments:
            file    the string representing the file
        """
    def MT(self, mt: int) -> Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    @typing.overload
    def __init__(self, sections: list[Section]) -> None:
        """
        Initialise the file
        
        Arguments:
            self       the file
            sections   the sections to be put into the file
        """
    @typing.overload
    def __init__(self, file: File) -> None:
        """
        Initialise the file with another file
        
        Arguments:
            self    the file
            file    the file to be copied
        """
    def has_MT(self, mt: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def has_section(self, mt: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def section(self, mt: int) -> Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    def to_string(self, mat: int) -> str:
        """
        The string representation of the file
        
        Arguments:
            self    the file
            mat     the MAT number to be used
        """
    def to_tree(self, mat: int) -> ...:
        """
        Return the ENDF tree representation of the file
        
        Arguments:
            self    the file
            mat     the MAT number to be used
        """
    @property
    def MF(self) -> int:
        """
        The MF number of the file
        """
    @property
    def MTs(self) -> ...:
        """
        The sections defined in the file
        """
    @property
    def file_number(self) -> int:
        """
        The MF number of the file
        """
    @property
    def sections(self) -> ...:
        """
        The sections defined in the file
        """
class LegendreBlock:
    """
    MF34 section - a subsection of an MF34 section
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> LegendreBlock:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, order: int, order1: int, lct: int, data: list[ENDFtk.CovariancePairs | ENDFtk.SquareMatrix | ENDFtk.RectangularMatrix]) -> None:
        """
        Initialise the component
        
        Arguments:
            self           the component
            order          the first Legendre order
            order1         the second Legendre order
            lct            the reference frame
            data           the NI-type data blocks
        """
    @typing.overload
    def __init__(self, component: LegendreBlock) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def L(self) -> int:
        """
        the first Legendre order
        """
    @property
    def L1(self) -> int:
        """
        the second Legendre order
        """
    @property
    def LCT(self) -> int:
        """
        the reference frame
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NI(self) -> int:
        """
        the number of NI-type data blocks
        """
    @property
    def data(self) -> ...:
        """
        the NI-type subsubsections
        """
    @property
    def first_legendre_order(self) -> int:
        """
        the first Legendre order
        """
    @property
    def number_data_blocks(self) -> int:
        """
        the number of NI-type data blocks
        """
    @property
    def reference_frame(self) -> int:
        """
        the reference frame
        """
    @property
    def second_legendre_order(self) -> int:
        """
        the second Legendre order
        """
class ReactionBlock:
    """
    MF34 section - a subsection of an MF34 section
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ReactionBlock:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, mt: int, mt1: int, nl: int, nl1: int, lblocks: list[...]) -> None:
        """
        Initialise the component
        
        Arguments:
            self           the component
            mt             the section number
            mt1            the section number of the second cross section
            nl             the number of Legendre orders for the first cross section
            nl1            the number of Legendre orders for the second cross section
            lblocks        the Legendre blocks
        """
    @typing.overload
    def __init__(self, component: ReactionBlock) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def MAT1(self) -> int:
        """
        the material number for the second cross section (must be 0)
        """
    @property
    def MT1(self) -> int:
        """
        the section number for the second cross section
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NL(self) -> int:
        """
        the number of Legendre orders of the first cross section
        """
    @property
    def NL1(self) -> int:
        """
        the number of Legendre orders of the second cross section
        """
    @property
    def NSS(self) -> int:
        """
        the number of subsubsections (Legendre blocks)
        """
    @property
    def first_number_legendre(self) -> int:
        """
        the number of Legendre orders of the first cross section
        """
    @property
    def legendre_blocks(self) -> ...:
        """
        the Legendre blocks
        """
    @property
    def number_legendre_blocks(self) -> int:
        """
        the number of subsubsections (Legendre blocks)
        """
    @property
    def second_material_number(self) -> int:
        """
        the material number for the second cross section (must be 0)
        """
    @property
    def second_number_legendre(self) -> int:
        """
        the number of Legendre orders of the second cross section
        """
    @property
    def second_section_number(self) -> int:
        """
        the section number for the second cross section
        """
class Section:
    """
    MF34 section - covariances for angular distributions
    """
    @staticmethod
    def from_string(section: str) -> Section:
        """
        Read the section from a string
        
        An exception is raised if something goes wrong while reading the
        section
        
        Arguments:
            section    the string representing the section
        """
    @typing.overload
    def __init__(self, mt: int, zaid: int, awr: float, ltt: int, reactions: list[ReactionBlock]) -> None:
        """
        Initialise the section
        
        Arguments:
            self        the section
            mt          the MT number
            zaid        the ZA  identifier
            awr         the atomic mass ratio
            ltt         the representation
            reactions   the reactions (subsections) (at least 1)
        """
    @typing.overload
    def __init__(self, section: Section) -> None:
        """
        Initialise the section with another section
        
        Arguments:
            self       the section
            section    the section to be copied
        """
    def to_string(self, mat: int, mf: int) -> str:
        """
        Return the string representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
            mf      the MF number to be used
        """
    def to_tree(self, mat: int) -> ...:
        """
        Return the ENDF tree representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def LTT(self) -> int:
        """
        the covariance representation
        """
    @property
    def MT(self) -> int:
        """
        The MT number of the section
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this section
        """
    @property
    def NMT1(self) -> int:
        """
        the number of reaction blocks (subsections)
        """
    @property
    def ZA(self) -> int:
        """
        The ZA identifier for the section
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def number_reactions(self) -> int:
        """
        the number of reaction blocks (subsections)
        """
    @property
    def reactions(self) -> ...:
        """
        the reactions (subsections) defined in this section
        """
    @property
    def representation(self) -> int:
        """
        the covariance representation
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def target_identifier(self) -> int:
        """
        The ZA identifier for the section
        """
