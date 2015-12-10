#include "srccolor.h"

void srccolor::process() {
    char buffer[10];
    unsigned width, height, value;
    bool success;

	if (!stimulusfile->is_open()) return;

	// read in PGM identifier
	*stimulusfile >> buffer;
	if (strcmp(buffer,"P3")) {
		cout << "no color PGM file" << endl;
		return;
	}
	// read in and put out width
	success = read_value_from_file_without_comments(stimulusfile,&width);
	if (success == false) return;
	if (width > maxwidth) {
		cout << "width of image " << width << " larger than maximum width " << maxwidth << endl;
		return;
	}
	parameters.write(width);
	// does not support comment lines in image file!
	// read in and put out height
	success = read_value_from_file_without_comments(stimulusfile,&height);
	if (success == false) return;
	parameters.write(height);
	// read in and put out max gray value
	success = read_value_from_file_without_comments(stimulusfile,&value);
	if (success == false) return;
	parameters.write(value);
	cout << "inputfile:: width: " << width<< " height: " << height<< " greyvalue: " << value << endl;

    for (unsigned pixels=0;pixels<(width*height);pixels++) {
        success = read_value_from_file_without_comments(stimulusfile,&value);
        if (success == false) return;
        output_red.write(value);
        success = read_value_from_file_without_comments(stimulusfile,&value);
        if (success == false) return;
        output_green.write(value);
        success = read_value_from_file_without_comments(stimulusfile,&value);
        if (success == false) return;
        output_blue.write(value);
	}

}


