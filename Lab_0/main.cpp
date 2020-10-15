#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>

int main(int argc, char* argv[]) {
	std::map<std::string, long long> histogram;
	std::string line,
				word;
	int totalWords = 0;
	int beginPos;
	bool flagPos = true;
	std::ifstream fin(argv[1]);

	//input
	while (std::getline(fin, line)) {
		for (int i = 0; line[i] != 0; i++) {
			if (flagPos && (isalpha(line[i]) || isdigit(line[i]))) {
				beginPos = i;
				flagPos = false;
			}
			if (!flagPos && (!(isalpha(line[i + 1]) || isdigit(line[i + 1])) || line[i + 1] == 0)) {
				word = line.substr(beginPos, i - beginPos + 1);
				histogram[word]++;
				word = "";
				flagPos = true;
				totalWords++;
			}
		}
	}
	fin.close();
	
	//sort
	std::vector<std::pair<std::string, long long>> sortVector;

	for (std::map<std::string, long long>::iterator it = histogram.begin(); it != histogram.end(); it++) {
		sortVector.push_back(std::make_pair(it->first, it->second));
	}

	std::sort(sortVector.begin(), sortVector.end(),
		[](const std::pair<std::string, long long>& p1, const std::pair<std::string, long long>& p2)
		{
			return (p1.second > p2.second ||
				(!(p2.second > p1.second) && p1.first < p2.first));
		});
	
	//output
	std::ofstream fout(argv[2]);
	fout << "Слово;Частота;Частота(в %)\n";
	for (int i = 0; i < sortVector.size(); i++)
		fout << sortVector[i].first << ";" << sortVector[i].second << ";" << (sortVector[i].second / (double)totalWords) * 100 << "\n";

	fout.close();

	return 0;
}
