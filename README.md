# Texer
Generates Latex code from handwritten math symbols and outputs images.

QTDIR and Python Directory in project file should be modified before compile.  
You may now use texer.pro to run qmake and make. (change PYTHON_PATH under texer.pro)

## Install Python Dependencies
The program requires a python environment. It is tested on python 3.6.8 (32-bit). (The model inside the release version works only on 32-bit python)

Run `pip install -r requirements.txt` to install python dependencies. (Under the installed directory if using the release version.)

## Easter Egg
There exists an Easter egg via which one can make his own dataset.

## Known Bugs

Display errors under high resolution.  
You may look over log.txt to find out errors for Python embedment.  
Recognition overfits the author's personal handwriting because it is trained by a small training set written by the author.  
The current release version has to be run as administrator because it writes to temp files in its own directory.  
Temp files have to be removed manually in uninstallation.  
There are bugs in memory management, but I have no idea how to fix it. (Python couldn't be correctly finalized while using numpy, see https://github.com/numpy/numpy/issues/656.) Other memory issues may exist as well.