#ifndef __FILEPROCESSOR_H__
#define __FILEPROCESSOR_H__

class FileProcessor
{
public:
	FileProcessor();

	static const vector<string>& loadTable();
	static const void            addTableNote(const vector<string>& note);
};

#endif