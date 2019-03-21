# Texer

Generates Latex code from handwritten math symbols and outputs images.

QTDIR and Python Directory in project file should be modified before compile.  
You may now use texer.pro to run qmake and make. (change PYTHON_PATH under texer.pro and run `qmake texer.pro`, `make` and `make install`)

## Manual

You could use the release version (which includes a setup.exe) to install it.  
Write in the box and click recognize button. You should write a single symbol at a time. If you want to jump into superscript (subscript), click the superscript (subscript) button, and click the jump button to get out of it. It could automatically deal with nested formulas. The clear button clears all inputs, the rewrite button clears the box while the undo button reverses to the last state. You may write latex code in the text box on your own and click the show button for image. The text editor supports highlight and code hints (you may update code hints in latex.api). The copy button copies the image into your clipboard.  
Showing the image requires Internet connection (online mode) or a python & latex environment (offline mode). Several models for recognition are provided (Random Forest and Neural Network, symbol only or includes numbers and certain alphabets).

## Install Python Dependencies

The program requires a python environment. It is tested on python 3.6.8 (32-bit). (The model inside the release version works only on 32-bit python)  
Run `pip install -r requirements.txt` to install python dependencies. (Under the installed directory if using the release version.)
A version that doesn’t need a python environment is provided in release, but I don’t guarantee that it works correctly.

## Easter Egg

There exists an Easter egg via which one can make his own dataset.  
You could put the mouse below the graph scene (in a certain area) for ten seconds and it will appear.

## Known Bugs

Display errors under high resolution.  
You may look over log.txt to find out errors for Python embedment.  
Recognition overfits the author's personal handwriting because it is trained by a small training set written by the author.  
And also the dataset is all written by the author, so it doesn’t contain all symbols or alphabets.  
The current release version has to be run as administrator because it writes to temp files in its own directory.  
Temp files have to be removed manually in uninstallation.  
There are bugs in memory management, but I have no idea how to fix it. (Python couldn't be correctly finalized while using numpy, see <https://github.com/numpy/numpy/issues/656/>.) Other memory issues may exist as well. But it shall not worry the user too much.