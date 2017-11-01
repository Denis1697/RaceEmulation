#ifndef __FILEPROCESSOR_H__
#define __FILEPROCESSOR_H__

class FileProcessor
{
public:
	static vector<string> loadTable();
	static void           addTableNote(const vector<string>& note);
};

#endif