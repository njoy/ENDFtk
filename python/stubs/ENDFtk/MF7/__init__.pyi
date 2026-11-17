"""
MF7 - thermal neutron scattering law data
"""
from __future__ import annotations
import typing
from . import MT2
from . import MT4
from . import MT451
__all__: list[str] = ['File', 'MT2', 'MT4', 'MT451']
class File:
    """
    MF7 file - thermal neutron scattering law data
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
    def MT(self, mt: int) -> MT2.Section | MT4.Section | MT451.Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    @typing.overload
    def __init__(self, elastic: MT2.Section) -> None:
        """
        Initialise the file with elastic thermal scattering data
        
        Arguments:
            self      the file
            elastic   the elastic thermal scattering data (MT2)
        """
    @typing.overload
    def __init__(self, inelastic: MT4.Section) -> None:
        """
        Initialise the file with inelastic thermal scattering data
        
        Arguments:
            self        the file
            inelastic   the inelastic thermal scattering data (MT4)
        """
    @typing.overload
    def __init__(self, elastic: MT2.Section, inelastic: MT4.Section) -> None:
        """
        Initialise the file with elastic and inelastic thermal scattering data
        
        Arguments:
            self        the file
            elastic     the elastic thermal scattering data (MT2)
            inelastic   the inelastic thermal scattering data (MT4)
        """
    @typing.overload
    def __init__(self, sections: list[MT2.Section | MT4.Section | MT451.Section]) -> None:
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
    def section(self, mt: int) -> MT2.Section | MT4.Section | MT451.Section:
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
