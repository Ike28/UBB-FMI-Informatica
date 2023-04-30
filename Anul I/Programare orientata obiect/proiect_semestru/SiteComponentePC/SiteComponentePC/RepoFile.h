#pragma once
#include <string>
using namespace std;

class RepoFile
{
	protected:
		string filename;
		virtual void writeToFile() = 0;
		virtual void loadFromFile() = 0;
	public:
		RepoFile() { }
		RepoFile(string filenameGiven) { filename = filenameGiven; }
		~RepoFile() { }

		string getFilename() { return filename; }
		void setFilename(string filenameGiven) { filename = filenameGiven; }

};
