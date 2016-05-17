#!C:\Python27\python.exe
# EASY-INSTALL-ENTRY-SCRIPT: 'pyOCD==0.7.1.dev11','console_scripts','pyocd-tool'
__requires__ = 'pyOCD==0.7.1.dev11'
import sys
from pkg_resources import load_entry_point

if __name__ == '__main__':
    sys.exit(
        load_entry_point('pyOCD==0.7.1.dev11', 'console_scripts', 'pyocd-tool')()
    )
