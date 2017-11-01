#include "Includes.h"

vector<string>
FileProcessor::loadTable() {
	ifstream fin("Records.txt", ios_base::in);
	vector<string> records;
	
	string nick;
	string distance;
	string time;

	while (fin >> nick >> distance >> time) {
		records.push_back(nick);
		records.push_back(distance);
		records.push_back(time);
	}

	fin.close();
	return records;
}

void 
FileProcessor::addTableNote(const vector<string>& note) {
	ofstream fout("Records.txt", ios_base::app);

	for (int i = 0; i < note.size(); i++) {
		fout << note[i] << " ";
	}
	fout << endl;

	fout.close();
}
