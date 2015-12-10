#include "srcgeneral.h"


bool srcgeneral::read_value_from_file_without_comments(ifstream *stimulusfile, unsigned *result) {
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
