Write a command line tool which loads all image files within a folder into memory and processes one after the other. 
You can choose the file format and (manually) convert the attached files. You can assume all files are monochrome. The images
show laser lines and the task is to get the positions of the lines in the image. The processing
should deliver all image pixel coordinates where the pixel brightness of the image after it has
been averaged over +/-5 pixels horizontally is maximal within a neighbourhood of
horizontally +/- 10 pixels. E.g. you could average first with a 1D box-filter and then check for
the local maxima. Please also only take the maxima where the pixel brightness in the
original (not averaged) image is at least 15.
Measure and output the total processing time.
After taking the time, you could export the coordinates into a text file to check for yourself
whether the correct maxima have been found.
Ideally the processing is done on a GPU using a CUDA-kernel.
