#include "src.h"


/*
bool src::read_value_from_file_without_comments(ifstream *stimulusfile, unsigned *result) {
    char buffer[70], temp;
	bool success;

	success = false;
	while (success == false){
        if (stimulusfile->eof()) {
            cout << "error file of wrong length" << endl;
            break;
        }
		*stimulusfile >> buffer;
		if (strcmp(buffer,"#")) {
			// data was not comment
			*result = atoi(buffer);
			success = true;
		}
		else {
			// process comment till end of line
	        if (stimulusfile->eof()) {
	            cout << "error file of wrong length" << endl;
	            break;
	        }
			temp = stimulusfile->get();
			while (temp != '\n'){
		        if (stimulusfile->eof()) {
		            cout << "error file of wrong length" << endl;
		            break;
		        }
				temp = stimulusfile->get();
			}
		}
	}

	return success;
}
*/
// process
void src::process() {
    char buffer[10];
    unsigned width, height, value;
    bool success;

	if (!stimulusfile->is_open()) return;

	// read in PGM identifier
	*stimulusfile >> buffer;
	if (strcmp(buffer,"P2")) {
		cout << "no greyscale PGM file" << endl;
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
        output.write(value);
	}
}


