"""
tree - ENDF tree components
"""
import ENDFtk
import ENDFtk.MF1
import ENDFtk.MF1.MT451
import ENDFtk.MF1.MT452
import ENDFtk.MF1.MT455
import ENDFtk.MF1.MT456
import ENDFtk.MF1.MT458
import ENDFtk.MF1.MT460
import ENDFtk.MF10
import ENDFtk.MF12
import ENDFtk.MF13
import ENDFtk.MF14
import ENDFtk.MF15
import ENDFtk.MF16
import ENDFtk.MF2
import ENDFtk.MF2.MT151
import ENDFtk.MF2.MT152
import ENDFtk.MF23
import ENDFtk.MF26
import ENDFtk.MF27
import ENDFtk.MF28
import ENDFtk.MF3
import ENDFtk.MF31
import ENDFtk.MF32
import ENDFtk.MF32.MT151
import ENDFtk.MF33
import ENDFtk.MF34
import ENDFtk.MF35
import ENDFtk.MF4
import ENDFtk.MF40
import ENDFtk.MF5
import ENDFtk.MF5.MT18
import ENDFtk.MF5.MT455
import ENDFtk.MF6
import ENDFtk.MF7
import ENDFtk.MF7.MT2
import ENDFtk.MF7.MT4
import ENDFtk.MF7.MT451
import ENDFtk.MF8
import ENDFtk.MF8.MT454
import ENDFtk.MF8.MT457
import ENDFtk.MF8.MT459
import ENDFtk.MF9
from __future__ import annotations
import typing
__all__: list[str] = ['File', 'GFile', 'GMaterial', 'GSection', 'GTape', 'Material', 'Section', 'Tape']
class File:
    """
    ENDF tree file
    """
    def MT(self, mt: int) -> Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the ENDF tree file
            mt      the MT number of the section to be returned
        """
    @typing.overload
    def __init__(self, mat: int, mf: int) -> None:
        """
        Initialise an empty file with its MAT and MF number
        
        Arguments:
            self    the file
            mat     the MAT number of the file
            mf      the MF number of the file
        """
    @typing.overload
    def __init__(self, file: File) -> None:
        """
        Initialise the file with another file
        
        Arguments:
            self    the file
            file    the file to be copied
        """
    def clean(self) -> None:
        """
        Clean up the file
        
        This function removes the sequence numbers from the file.
        """
    def has_MT(self, arg0: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def has_section(self, arg0: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    @typing.overload
    def insert(self, section: Section) -> None:
        """
        Insert the section in the file
        
        This function inserts the section in the ENDF file tree only if a
        section with that MT number is not present yet.
        
        An exception will be thrown if the MAT and MF number of the section do
        not match the MAT and MF number of the file, and when a section with the
        same MT number is already present.
        
        Arguments:
            self      the ENDF tree file
            section   the section to be inserted
        """
    @typing.overload
    def insert(self, section: ENDFtk.MF1.MT451.Section | ENDFtk.MF1.MT452.Section | ENDFtk.MF1.MT455.Section | ENDFtk.MF1.MT456.Section | ENDFtk.MF1.MT458.Section | ENDFtk.MF1.MT460.Section | ENDFtk.MF2.MT151.Section | ENDFtk.MF2.MT152.Section | ENDFtk.MF3.Section | ENDFtk.MF4.Section | ENDFtk.MF5.Section | ENDFtk.MF6.Section | ENDFtk.MF7.MT2.Section | ENDFtk.MF7.MT4.Section | ENDFtk.MF7.MT451.Section | ENDFtk.MF8.MT454.Section | ENDFtk.MF8.MT457.Section | ENDFtk.MF8.MT459.Section | ENDFtk.MF9.Section | ENDFtk.MF10.Section | ENDFtk.MF12.Section | ENDFtk.MF13.Section | ENDFtk.MF14.Section | ENDFtk.MF15.Section | ENDFtk.MF23.Section | ENDFtk.MF26.Section | ENDFtk.MF27.Section | ENDFtk.MF28.Section | ENDFtk.MF31.Section | ENDFtk.MF32.MT151.Section | ENDFtk.MF33.Section | ENDFtk.MF34.Section | ENDFtk.MF35.Section | ENDFtk.MF40.Section) -> None:
        """
        Insert the section in the file
        
        This function inserts the section in the ENDF file tree only if a
        section with that MT number is not present yet.
        
        An exception will be thrown if the MAT and MF number of the section do
        not match the MAT and MF number of the file, and when a section with the
        same MT number is already present.
        
        Arguments:
            self      the ENDF tree file
            section   the section to be inserted
        """
    @typing.overload
    def insert_or_replace(self, section: Section) -> None:
        """
        Insert or replace the section in the file
        
        This function inserts or replaces the section in the ENDF file tree.
        
        An exception will be thrown if the MAT and MF number of the section do
        not match the MAT and MF number of the file.
        
        Arguments:
            self      the ENDF tree file
            section   the section to be inserted or replaced
        """
    @typing.overload
    def insert_or_replace(self, section: ENDFtk.MF1.MT451.Section | ENDFtk.MF1.MT452.Section | ENDFtk.MF1.MT455.Section | ENDFtk.MF1.MT456.Section | ENDFtk.MF1.MT458.Section | ENDFtk.MF1.MT460.Section | ENDFtk.MF2.MT151.Section | ENDFtk.MF2.MT152.Section | ENDFtk.MF3.Section | ENDFtk.MF4.Section | ENDFtk.MF5.Section | ENDFtk.MF6.Section | ENDFtk.MF7.MT2.Section | ENDFtk.MF7.MT4.Section | ENDFtk.MF7.MT451.Section | ENDFtk.MF8.MT454.Section | ENDFtk.MF8.MT457.Section | ENDFtk.MF8.MT459.Section | ENDFtk.MF9.Section | ENDFtk.MF10.Section | ENDFtk.MF12.Section | ENDFtk.MF13.Section | ENDFtk.MF14.Section | ENDFtk.MF15.Section | ENDFtk.MF23.Section | ENDFtk.MF26.Section | ENDFtk.MF27.Section | ENDFtk.MF28.Section | ENDFtk.MF31.Section | ENDFtk.MF32.MT151.Section | ENDFtk.MF33.Section | ENDFtk.MF34.Section | ENDFtk.MF35.Section | ENDFtk.MF40.Section) -> None:
        """
        Insert or replace the section in the file
        
        This function inserts or replaces the section in the ENDF file tree.
        
        An exception will be thrown if the MAT and MF number of the section do
        not match the MAT and MF number of the file.
        
        Arguments:
            self      the ENDF tree file
            section   the section to be inserted or replaced
        """
    def parse(self) -> ENDFtk.MF1.File | ENDFtk.MF2.File | ENDFtk.MF3.File | ENDFtk.MF4.File | ENDFtk.MF5.File | ENDFtk.MF6.File | ENDFtk.MF7.File | ENDFtk.MF8.File | ENDFtk.MF9.File | ENDFtk.MF10.File | ENDFtk.MF12.File | ENDFtk.MF13.File | ENDFtk.MF14.File | ENDFtk.MF15.File | ENDFtk.MF23.File | ENDFtk.MF26.File | ENDFtk.MF27.File | ENDFtk.MF28.File | ENDFtk.MF31.File | ENDFtk.MF32.File | ENDFtk.MF33.File | ENDFtk.MF34.File | ENDFtk.MF35.File | ENDFtk.MF40.File:
        """
        Parse the file
        """
    def remove(self, mt: int) -> None:
        """
        Remove the section in the file if it is present
        
        Arguments:
            self    the ENDF tree file
            mt      the mt number of the section to be removed
        """
    def section(self, mt: int) -> Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the ENDF tree file
            mt      the MT number of the section to be returned
        """
    @property
    def MAT(self) -> int:
        """
        The MAT number of the file
        """
    @property
    def MF(self) -> int:
        """
        The MF number of the file
        """
    @property
    def content(self) -> str:
        """
        The content of the file
        """
    @property
    def file_number(self) -> int:
        """
        The MF number of the file
        """
    @property
    def material_number(self) -> int:
        """
        The MAT number of the file
        """
    @property
    def section_numbers(self) -> ...:
        """
        All section numbers in the file
        """
    @property
    def sections(self) -> ...:
        """
        All sections in the file
        """
class GFile:
    """
    GENDF tree file
    """
    def MT(self, mt: int) -> GSection:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the ENDF tree file
            mt      the MT number of the section to be returned
        """
    @typing.overload
    def __init__(self, mat: int, mf: int) -> None:
        """
        Initialise an empty file with its MAT and MF number
        
        Arguments:
            self    the file
            mat     the MAT number of the file
            mf      the MF number of the file
        """
    @typing.overload
    def __init__(self, file: GFile) -> None:
        """
        Initialise the file with another file
        
        Arguments:
            self    the file
            file    the file to be copied
        """
    def clean(self) -> None:
        """
        Clean up the file
        
        This function removes the sequence numbers from the file.
        """
    def has_MT(self, arg0: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def has_section(self, arg0: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def section(self, mt: int) -> GSection:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the ENDF tree file
            mt      the MT number of the section to be returned
        """
    @property
    def MAT(self) -> int:
        """
        The MAT number of the file
        """
    @property
    def MF(self) -> int:
        """
        The MF number of the file
        """
    @property
    def content(self) -> str:
        """
        The content of the file
        """
    @property
    def file_number(self) -> int:
        """
        The MF number of the file
        """
    @property
    def material_number(self) -> int:
        """
        The MAT number of the file
        """
    @property
    def section_numbers(self) -> ...:
        """
        All section numbers in the file
        """
    @property
    def sections(self) -> ...:
        """
        All sections in the file
        """
class GMaterial:
    """
    GENDF tree material
    """
    def MF(self, mf: int) -> GFile:
        """
        Return the file with the requested MF number
        
        Arguments:
            self    the ENDF tree material
            mf      the MF number of the file to be returned
        """
    def MFMT(self, mf: int, mt: int) -> GSection:
        """
            mt      the Mt number of the section to be returned
        """
    @typing.overload
    def __init__(self, mat: int) -> None:
        """
        Initialise an empty material with its MAT number
        
        Arguments:
            self    the file
            mat     the MAT number of the material
        """
    @typing.overload
    def __init__(self, material: GMaterial) -> None:
        """
        Initialise the material with another material
        
        Arguments:
            self        the material
            material    the material to be copied
        """
    def clean(self) -> None:
        """
        Clean up the material
        
        This function removes the sequence numbers from the material.
        """
    def file(self, mf: int) -> GFile:
        """
        Return the file with the requested MF number
        
        Arguments:
            self    the ENDF tree material
            mf      the MF number of the file to be returned
        """
    def has_MF(self, arg0: int) -> bool:
        """
        Return whether or not the material has a file with the given MF number
        
        Arguments:
            self    the material
            mf      the MF number of the file
        """
    def has_MF_MT(self, arg0: int, arg1: int) -> bool:
        """
        Return whether or not the material has a section with the given MF and MT number
        
        Arguments:
            self    the material
            mf      the MF number of the section
            mt      the MT number of the section
        """
    def has_file(self, arg0: int) -> bool:
        """
        Return whether or not the material has a file with the given MF number
        
        Arguments:
            self    the material
            mf      the MF number of the file
        """
    def has_section(self, arg0: int, arg1: int) -> bool:
        """
        Return whether or not the material has a file with the given MF number
        
        Arguments:
            self    the material
            mf      the MF number of the section
            mt      the MT number of the section
        """
    def section(self, mf: int, mt: int) -> GSection:
        """
            mt      the Mt number of the section to be returned
        """
    @property
    def MAT(self) -> int:
        """
        The MAT number of the material
        """
    @property
    def content(self) -> str:
        """
        The content of the material
        """
    @property
    def file_numbers(self) -> ...:
        """
        All file numbers in the material
        """
    @property
    def files(self) -> ...:
        """
        All files in the material
        """
    @property
    def material_number(self) -> int:
        """
        The MAT number of the material
        """
class GSection:
    """
    GENDF tree section
    """
    def __init__(self, section: GSection) -> None:
        """
        Initialise the section with another section
        
        Arguments:
            self       the section
            section    the section to be copied
        """
    def clean(self) -> None:
        """
        Clean up the section
        
        This function removes the sequence numbers from the section.
        """
    def parse(self) -> ENDFtk.MF1.MT451.GSection | ENDFtk.MF3.GSection | ENDFtk.MF5.MT18.GSection | ENDFtk.MF5.MT455.GSection | ENDFtk.MF6.GSection | ENDFtk.MF16.GSection:
        """
        Parse the section
        """
    @property
    def MAT(self) -> int:
        """
        The MAT number of the section
        """
    @property
    def MF(self) -> int:
        """
        The MF number of the section
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
    def content(self) -> str:
        """
        The content of the section
        """
    @property
    def file_number(self) -> int:
        """
        The MF number of the section
        """
    @property
    def material_number(self) -> int:
        """
        The MAT number of the section
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
class GTape:
    """
    GENDF tape
    """
    @staticmethod
    def from_file(filename: str) -> GTape:
        """
        Read a tape from a file
        
        An exception is raised if something goes wrong while reading the
        tape
        
        Arguments:
            filename    the file name and path
        """
    @staticmethod
    def from_string(string: str) -> GTape:
        """
        Read a tape from a string
        
        An exception is raised if something goes wrong while reading the
        tape
        
        Arguments:
            string    the content of the tape
        """
    def MAT(self, mat: int) -> GMaterial | ... | ...:
        """
        Return the material(s) with the requested MAT number
        
        This function returns either a single material (if only a single material
        is present) or a sequence of materials (if more than one material is
        present) since a tape can contain multiple instances of the same material
        (e.g. at different temperatures).
        
        Arguments:
            self    the tape
            mat     the MAT number of the material to be returned
        """
    @typing.overload
    def __init__(self, id: ENDFtk.TapeIdentification) -> None:
        """
        Initialise the tape
        
        Arguments:
            self   the tape
            id     the tape identifier
        """
    @typing.overload
    def __init__(self, content: str) -> None:
        """
        Initialise the tape
        
        Arguments:
            self       the tape
            content    the content of the tape
        """
    @typing.overload
    def __init__(self, tape: GTape) -> None:
        """
        Initialise the tape
        
        Arguments:
            self    the tape
            tape    the tape to be copied
        """
    def clean(self) -> None:
        """
        Clean up the tape
        
        This function removes the sequence numbers from the tape.
        """
    def has_MAT(self, arg0: int) -> bool:
        """
        Return whether or not the tape has a material with the given MAT number
        
        Arguments:
            self    the tape
            mat     the MAT number of the material
        """
    def has_material(self, arg0: int) -> bool:
        """
        Return whether or not the tape has a material with the given MAT number
        
        Arguments:
            self    the tape
            mat     the MAT number of the material
        """
    def material(self, mat: int) -> GMaterial | ... | ...:
        """
        Return the material(s) with the requested MAT number
        
        This function returns either a single material (if only a single material
        is present) or a sequence of materials (if more than one material is
        present) since a tape can contain multiple instances of the same material
        (e.g. at different temperatures).
        
        Arguments:
            self    the tape
            mat     the MAT number of the material to be returned
        """
    def to_file(self, filename: str) -> None:
        """
        Write the tape to a file
        
        Arguments:
            self        the tape
            filename    the file name and path
        """
    @property
    def TPID(self) -> ENDFtk.TapeIdentification:
        """
        The tape identification (the first line in the file)
        """
    @property
    def content(self) -> str:
        """
        The content of the tape
        """
    @property
    def material_numbers(self) -> list[int]:
        """
        All unique material numbers in the tape
        """
    @property
    def materials(self) -> ...:
        """
        All materials in the tape
        """
    @property
    def tape_id(self) -> ENDFtk.TapeIdentification:
        """
        The tape identification (the first line in the file)
        """
class Material:
    """
    ENDF tree material
    """
    def MF(self, mf: int) -> File:
        """
        Return the file with the requested MF number
        
        Arguments:
            self    the ENDF tree material
            mf      the MF number of the file to be returned
        """
    def MFMT(self, mf: int, mt: int) -> Section:
        """
            mt      the Mt number of the section to be returned
        """
    @typing.overload
    def __init__(self, mat: int) -> None:
        """
        Initialise an empty material with its MAT number
        
        Arguments:
            self    the file
            mat     the MAT number of the material
        """
    @typing.overload
    def __init__(self, material: Material) -> None:
        """
        Initialise the material with another material
        
        Arguments:
            self        the material
            material    the material to be copied
        """
    def clean(self) -> None:
        """
        Clean up the material
        
        This function removes the sequence numbers from the material.
        """
    def file(self, mf: int) -> File:
        """
        Return the file with the requested MF number
        
        Arguments:
            self    the ENDF tree material
            mf      the MF number of the file to be returned
        """
    def has_MF(self, arg0: int) -> bool:
        """
        Return whether or not the material has a file with the given MF number
        
        Arguments:
            self    the material
            mf      the MF number of the file
        """
    def has_MF_MT(self, arg0: int, arg1: int) -> bool:
        """
        Return whether or not the material has a section with the given MF and MT number
        
        Arguments:
            self    the material
            mf      the MF number of the section
            mt      the MT number of the section
        """
    def has_file(self, arg0: int) -> bool:
        """
        Return whether or not the material has a file with the given MF number
        
        Arguments:
            self    the material
            mf      the MF number of the file
        """
    def has_section(self, arg0: int, arg1: int) -> bool:
        """
        Return whether or not the material has a file with the given MF number
        
        Arguments:
            self    the material
            mf      the MF number of the section
            mt      the MT number of the section
        """
    @typing.overload
    def insert(self, section: Section) -> None:
        """
        Insert the section in the material
        
        This function inserts the section in the ENDF material tree only if a
        section with that MT number is not present yet. If the file the section is
        to be added to is missing, it is added.
        
        An exception will be thrown if the MAT number of the section does
        not match the MAT number of the file, and when a section with the
        same MT number is already present.
        
        Arguments:
            self      the ENDF tree material
            section   the section to be inserted
        """
    @typing.overload
    def insert(self, section: ENDFtk.MF1.MT451.Section | ENDFtk.MF1.MT452.Section | ENDFtk.MF1.MT455.Section | ENDFtk.MF1.MT456.Section | ENDFtk.MF1.MT458.Section | ENDFtk.MF1.MT460.Section | ENDFtk.MF2.MT151.Section | ENDFtk.MF2.MT152.Section | ENDFtk.MF3.Section | ENDFtk.MF4.Section | ENDFtk.MF5.Section | ENDFtk.MF6.Section | ENDFtk.MF7.MT2.Section | ENDFtk.MF7.MT4.Section | ENDFtk.MF7.MT451.Section | ENDFtk.MF8.MT454.Section | ENDFtk.MF8.MT457.Section | ENDFtk.MF8.MT459.Section | ENDFtk.MF9.Section | ENDFtk.MF10.Section | ENDFtk.MF12.Section | ENDFtk.MF13.Section | ENDFtk.MF14.Section | ENDFtk.MF15.Section | ENDFtk.MF23.Section | ENDFtk.MF26.Section | ENDFtk.MF27.Section | ENDFtk.MF28.Section | ENDFtk.MF31.Section | ENDFtk.MF32.MT151.Section | ENDFtk.MF33.Section | ENDFtk.MF34.Section | ENDFtk.MF35.Section | ENDFtk.MF40.Section) -> None:
        """
        Insert the section in the material
        
        This function inserts the section in the ENDF material tree only if a
        section with that MT number is not present yet. If the file the section is
        to be added to is missing, it is added.
        
        An exception will be thrown if the MAT number of the section does
        not match the MAT number of the file, and when a section with the
        same MT number is already present.
        
        Arguments:
            self      the ENDF tree material
            section   the section to be inserted
        """
    @typing.overload
    def insert(self, file: File) -> None:
        """
        Insert the file in the material
        
        This function inserts the file in the ENDF material tree only if a
        file with that MF number is not present yet.
        
        An exception will be thrown if the MAT number of the file does
        not match the MAT number of the file, and when a file with the
        same MF number is already present.
        
        Arguments:
            self   the ENDF tree material
            file   the file to be inserted
        """
    @typing.overload
    def insert(self, file: ENDFtk.MF1.File | ENDFtk.MF2.File | ENDFtk.MF3.File | ENDFtk.MF4.File | ENDFtk.MF5.File | ENDFtk.MF6.File | ENDFtk.MF7.File | ENDFtk.MF8.File | ENDFtk.MF9.File | ENDFtk.MF10.File | ENDFtk.MF12.File | ENDFtk.MF13.File | ENDFtk.MF14.File | ENDFtk.MF15.File | ENDFtk.MF23.File | ENDFtk.MF26.File | ENDFtk.MF27.File | ENDFtk.MF28.File | ENDFtk.MF31.File | ENDFtk.MF32.File | ENDFtk.MF33.File | ENDFtk.MF34.File | ENDFtk.MF35.File | ENDFtk.MF40.File) -> None:
        """
        Insert the file in the material
        
        This function inserts the file in the ENDF material tree only if a
        file with that MF number is not present yet.
        
        An exception will be thrown if the MAT number of the file does
        not match the MAT number of the file, and when a file with the
        same MF number is already present.
        
        Arguments:
            self   the ENDF tree material
            file   the file to be inserted
        """
    @typing.overload
    def insert_or_replace(self, section: Section) -> None:
        """
        Insert or replace the section in the material
        
        This function inserts or replaces the section in the ENDF material tree.
        
        An exception will be thrown if the MAT number of the section does
        not match the MAT number of the material.
        
        Arguments:
            self      the ENDF tree material
            section   the section to be inserted or replaced
        """
    @typing.overload
    def insert_or_replace(self, section: ENDFtk.MF1.MT451.Section | ENDFtk.MF1.MT452.Section | ENDFtk.MF1.MT455.Section | ENDFtk.MF1.MT456.Section | ENDFtk.MF1.MT458.Section | ENDFtk.MF1.MT460.Section | ENDFtk.MF2.MT151.Section | ENDFtk.MF2.MT152.Section | ENDFtk.MF3.Section | ENDFtk.MF4.Section | ENDFtk.MF5.Section | ENDFtk.MF6.Section | ENDFtk.MF7.MT2.Section | ENDFtk.MF7.MT4.Section | ENDFtk.MF7.MT451.Section | ENDFtk.MF8.MT454.Section | ENDFtk.MF8.MT457.Section | ENDFtk.MF8.MT459.Section | ENDFtk.MF9.Section | ENDFtk.MF10.Section | ENDFtk.MF12.Section | ENDFtk.MF13.Section | ENDFtk.MF14.Section | ENDFtk.MF15.Section | ENDFtk.MF23.Section | ENDFtk.MF26.Section | ENDFtk.MF27.Section | ENDFtk.MF28.Section | ENDFtk.MF31.Section | ENDFtk.MF32.MT151.Section | ENDFtk.MF33.Section | ENDFtk.MF34.Section | ENDFtk.MF35.Section | ENDFtk.MF40.Section) -> None:
        """
        Insert or replace the section in the material
        
        This function inserts or replaces the section in the ENDF material tree.
        
        An exception will be thrown if the MAT number of the section does
        not match the MAT number of the material.
        
        Arguments:
            self      the ENDF tree material
            section   the section to be inserted or replaced
        """
    @typing.overload
    def insert_or_replace(self, file: File) -> None:
        """
        Insert or replace the file in the material
        
        This function inserts or replaces the file in the ENDF material tree. This
        does not merge sections if the file is already present: the old file is
        removed prior to inserting the new file.
        
        An exception will be thrown if the MAT number of the file does
        not match the MAT number of the file.
        
        Arguments:
            self   the ENDF tree material
            file   the file to be inserted or replaced
        """
    @typing.overload
    def insert_or_replace(self, file: ENDFtk.MF1.File | ENDFtk.MF2.File | ENDFtk.MF3.File | ENDFtk.MF4.File | ENDFtk.MF5.File | ENDFtk.MF6.File | ENDFtk.MF7.File | ENDFtk.MF8.File | ENDFtk.MF9.File | ENDFtk.MF10.File | ENDFtk.MF12.File | ENDFtk.MF13.File | ENDFtk.MF14.File | ENDFtk.MF15.File | ENDFtk.MF23.File | ENDFtk.MF26.File | ENDFtk.MF27.File | ENDFtk.MF28.File | ENDFtk.MF31.File | ENDFtk.MF32.File | ENDFtk.MF33.File | ENDFtk.MF34.File | ENDFtk.MF35.File | ENDFtk.MF40.File) -> None:
        """
        Insert or replace the file in the material
        
        This function inserts or replaces the file in the ENDF material tree. This
        does not merge sections if the file is already present: the old file is
        removed prior to inserting the new file.
        
        An exception will be thrown if the MAT number of the file does
        not match the MAT number of the file.
        
        Arguments:
            self   the ENDF tree material
            file   the file to be inserted or replaced
        """
    def parse(self) -> ENDFtk.Material:
        """
        Parse the material
        """
    @typing.overload
    def remove(self, mf: int) -> None:
        """
        Remove the file in the material if it is present
        
        Arguments:
            self    the ENDF tree file
            mf      the mf number of the file to be removed
        """
    @typing.overload
    def remove(self, mf: int, mt: int) -> None:
        """
        Remove the section in the material if it is present
        
        Arguments:
            self    the ENDF tree file
            mf      the mf number of the section to be removed
            mt      the mt number of the section to be removed
        """
    def section(self, mf: int, mt: int) -> Section:
        """
            mt      the Mt number of the section to be returned
        """
    def update_directory(self, copy_mod: bool = False) -> None:
        """
        Update the MF1 MT451 directory for the given material
        
        An exception will be thrown if the MF1 MT451 section is not present, or if
        there was an issue parsing it.
        
        Arguments:
            self       the ENDF tree material
            copy_mod   copy mod numbers if available (default is False)
        """
    @property
    def MAT(self) -> int:
        """
        The MAT number of the material
        """
    @property
    def content(self) -> str:
        """
        The content of the material
        """
    @property
    def file_numbers(self) -> ...:
        """
        All file numbers in the material
        """
    @property
    def files(self) -> ...:
        """
        All files in the material
        """
    @property
    def material_number(self) -> int:
        """
        The MAT number of the material
        """
class Section:
    """
    ENDF tree section
    """
    def __init__(self, section: Section) -> None:
        """
        Initialise the section with another section
        
        Arguments:
            self       the section
            section    the section to be copied
        """
    def clean(self) -> None:
        """
        Clean up the section
        
        This function removes the sequence numbers from the section.
        """
    def parse(self) -> ENDFtk.MF1.MT451.Section | ENDFtk.MF1.MT452.Section | ENDFtk.MF1.MT455.Section | ENDFtk.MF1.MT456.Section | ENDFtk.MF1.MT458.Section | ENDFtk.MF1.MT460.Section | ENDFtk.MF2.MT151.Section | ENDFtk.MF2.MT152.Section | ENDFtk.MF3.Section | ENDFtk.MF4.Section | ENDFtk.MF5.Section | ENDFtk.MF6.Section | ENDFtk.MF7.MT2.Section | ENDFtk.MF7.MT4.Section | ENDFtk.MF7.MT451.Section | ENDFtk.MF8.MT454.Section | ENDFtk.MF8.MT457.Section | ENDFtk.MF8.MT459.Section | ENDFtk.MF9.Section | ENDFtk.MF10.Section | ENDFtk.MF12.Section | ENDFtk.MF13.Section | ENDFtk.MF14.Section | ENDFtk.MF15.Section | ENDFtk.MF23.Section | ENDFtk.MF26.Section | ENDFtk.MF27.Section | ENDFtk.MF28.Section | ENDFtk.MF31.Section | ENDFtk.MF32.MT151.Section | ENDFtk.MF33.Section | ENDFtk.MF34.Section | ENDFtk.MF35.Section | ENDFtk.MF40.Section:
        """
        Parse the section
        """
    @property
    def MAT(self) -> int:
        """
        The MAT number of the section
        """
    @property
    def MF(self) -> int:
        """
        The MF number of the section
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
    def content(self) -> str:
        """
        The content of the section
        """
    @property
    def file_number(self) -> int:
        """
        The MF number of the section
        """
    @property
    def material_number(self) -> int:
        """
        The MAT number of the section
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
class Tape:
    """
    ENDF tape
    """
    @staticmethod
    def from_file(filename: str) -> Tape:
        """
        Read a tape from a file
        
        An exception is raised if something goes wrong while reading the
        tape
        
        Arguments:
            filename    the file name and path
        """
    @staticmethod
    def from_string(string: str) -> Tape:
        """
        Read a tape from a string
        
        An exception is raised if something goes wrong while reading the
        tape
        
        Arguments:
            string    the content of the tape
        """
    def MAT(self, mat: int) -> Material | ... | ...:
        """
        Return the material(s) with the requested MAT number
        
        This function returns either a single material (if only a single material
        is present) or a sequence of materials (if more than one material is
        present) since a tape can contain multiple instances of the same material
        (e.g. at different temperatures).
        
        Arguments:
            self    the tape
            mat     the MAT number of the material to be returned
        """
    @typing.overload
    def __init__(self, id: ENDFtk.TapeIdentification) -> None:
        """
        Initialise the tape
        
        Arguments:
            self   the tape
            id     the tape identifier
        """
    @typing.overload
    def __init__(self, content: str) -> None:
        """
        Initialise the tape
        
        Arguments:
            self       the tape
            content    the content of the tape
        """
    @typing.overload
    def __init__(self, tape: Tape) -> None:
        """
        Initialise the tape
        
        Arguments:
            self    the tape
            tape    the tape to be copied
        """
    def clean(self) -> None:
        """
        Clean up the tape
        
        This function removes the sequence numbers from the tape.
        """
    def has_MAT(self, arg0: int) -> bool:
        """
        Return whether or not the tape has a material with the given MAT number
        
        Arguments:
            self    the tape
            mat     the MAT number of the material
        """
    def has_material(self, arg0: int) -> bool:
        """
        Return whether or not the tape has a material with the given MAT number
        
        Arguments:
            self    the tape
            mat     the MAT number of the material
        """
    @typing.overload
    def insert(self, material: Material) -> None:
        """
        Insert the material in the tape
        
        This function inserts the material in the ENDF tape tree. If one or more
        materials are already present, the new material is inserted after the
        materials that are already there.
        
        Arguments:
            self       the tape
            material   the material to be inserted
        """
    @typing.overload
    def insert(self, material: ENDFtk.Material) -> None:
        """
        Insert the material in the tape
        
        This function inserts the material in the ENDF tape tree. If one or more
        materials are already present, the new material is inserted after the
        materials that are already there.
        
        Arguments:
            self       the tape
            material   the material to be inserted
        """
    def material(self, mat: int) -> Material | ... | ...:
        """
        Return the material(s) with the requested MAT number
        
        This function returns either a single material (if only a single material
        is present) or a sequence of materials (if more than one material is
        present) since a tape can contain multiple instances of the same material
        (e.g. at different temperatures).
        
        Arguments:
            self    the tape
            mat     the MAT number of the material to be returned
        """
    def remove(self, mat: int) -> None:
        """
        Remove all materials with the given MAT number
        
        Arguments:
            self    the ENDF tree file
            mat     the mat number of the materials to be removed
        """
    @typing.overload
    def replace(self, material: Material) -> None:
        """
        Insert or replace the material in the tape
        
        This function inserts the material in the ENDF tape tree. If one or more
        materials are already present, the old materials are removed before inserting
        the new material.
        
        Arguments:
            self       the tape
            material   the material to be inserted
        """
    @typing.overload
    def replace(self, material: ENDFtk.Material) -> None:
        """
        Insert or replace the material in the tape
        
        This function inserts the material in the ENDF tape tree. If one or more
        materials are already present, the old materials are removed before inserting
        the new material.
        
        Arguments:
            self       the tape
            material   the material to be inserted
        """
    def to_file(self, filename: str) -> None:
        """
        Write the tape to a file
        
        Arguments:
            self        the tape
            filename    the file name and path
        """
    def update_directory(self, copy_mod: bool = False) -> None:
        """
        Update the MF1 MT451 directory for all materials in the tape
        
        An exception will be thrown if a material in the tape has no MF1 MT451
        section is not present, or if there was an issue parsing it.
        
        Arguments:
            self        the tape
            copy_mod    copy mod numbers if available (default is False)
        """
    @property
    def TPID(self) -> ENDFtk.TapeIdentification:
        """
        The tape identification (the first line in the file)
        """
    @property
    def content(self) -> str:
        """
        The content of the tape
        """
    @property
    def material_numbers(self) -> list[int]:
        """
        All unique material numbers in the tape
        """
    @property
    def materials(self) -> ...:
        """
        All materials in the tape
        """
    @property
    def tape_id(self) -> ENDFtk.TapeIdentification:
        """
        The tape identification (the first line in the file)
        """
