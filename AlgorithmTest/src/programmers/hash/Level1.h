/*
 * ProgrammersFirst.h
 *
 *  Created on: 2021. 9. 8.
 *      Author: dhjeong
 */

#ifndef PROGRAMMERSFIRST_H_
#define PROGRAMMERSFIRST_H_

#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

class Level1 {
public:
	Level1();
	virtual ~Level1();

	void run() {
		std::vector<string> participant;
		std::vector<string> completion;

//		["leo", "kiki", "eden"]	["eden", "kiki"]	"leo"
//		["marina", "josipa", "nikola", "vinko", "filipa"]	["josipa", "filipa", "marina", "nikola"]	"vinko"
//		["mislav", "stanko", "mislav", "ana"]	["stanko", "ana", "mislav"]
		participant.push_back("leo");
		participant.push_back("kiki");
		participant.push_back("eden");
		completion.push_back("eden");
		completion.push_back("kiki");
		printf("%s\n", solution(participant, completion).c_str());


		participant.clear();
		completion.clear();
		participant.push_back("marina");
		participant.push_back("josipa");
		participant.push_back("nikola");
		participant.push_back("vinko");
		participant.push_back("filipa");
		completion.push_back("josipa");
		completion.push_back("filipa");
		completion.push_back("marina");
		completion.push_back("nikola");
		printf("%s\n", solution(participant, completion).c_str());

		participant.clear();
		completion.clear();
		participant.push_back("mislav");
		participant.push_back("stanko");
		participant.push_back("mislav");
		participant.push_back("ana");
		completion.push_back("stanko");
		completion.push_back("ana");
		completion.push_back("mislav");
		printf("%s\n", solution(participant, completion).c_str());
	}

	string solution(vector<string>& participant, vector<string>& completion) {
		string answer = "";
		map<string, int> pMap;
		map<string, int> cMap;

		for (unsigned int i = 0; i < participant.size(); i++) {
			if (pMap.find(participant[i]) != pMap.end()) {
				pMap.find(participant[i])->second++;
			} else {
				pMap.insert(make_pair(participant[i], 1));
			}
		}

		for (unsigned int i = 0; i < completion.size(); i++) {
			if (pMap.find(completion[i]) != pMap.end()) {
				pMap.find(completion[i])->second--;
				if (pMap.find(completion[i])->second == 0) {
					pMap.erase(completion[i]);
				}
			}
		}

		answer = pMap.begin()->first;

		return answer;
	}
};

#endif /* PROGRAMMERSFIRST_H_ */
