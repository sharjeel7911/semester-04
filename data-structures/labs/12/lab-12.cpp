#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

int repeatingelement(int arr[], int n);
pair<int, int> twoSum(int arr[], int target, int length);
vector<int> topKFrequent(vector<int>& nums, int k);
char firstUniqueChar(string str);
void findDuplicates(vector<int>& nums);
void countGrades();
void countVotes();

int main() {
	int choice;

	do {
		cout << "\n========== MENU ==========\n";
		cout << "1. Find First Repeating Element\n";
		cout << "2. Two Sum\n";
		cout << "3. Top K Frequent Elements\n";
		cout << "4. First Unique Character\n";
		cout << "5. Find Duplicates\n";
		cout << "6. Count Grades from File\n";
		cout << "7. Count Votes and Determine Winner\n";
		cout << "0. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
			case 1: {
				int n;
				cout << "Enter size of array: ";
				cin >> n;

				int arr[n];
				cout << "Enter elements: ";
				for (int i = 0; i < n; i++) cin >> arr[i];

				cout << "First Repeating Element: " << repeatingelement(arr, n) << endl;
				break;
			}

			case 2: {
				int n, target;
				cout << "Enter size of array: ";
				cin >> n;

				int arr[n];
				cout << "Enter elements: ";
				for (int i = 0; i < n; i++) cin >> arr[i];

				cout << "Enter target: ";
				cin >> target;

				pair<int, int> ans = twoSum(arr, target, n);

				if (ans.first == -1)
					cout << "No pair found.\n";
				else
					cout << "Indices: " << ans.first << " " << ans.second << endl;

				break;
			}

			case 3: {
				int n, k;

				cout << "Enter size of array: ";
				cin >> n;

				vector<int> nums(n);

				cout << "Enter elements: ";
				for (int i = 0; i < n; i++) cin >> nums[i];

				cout << "Enter k: ";
				cin >> k;

				vector<int> result = topKFrequent(nums, k);

				cout << "Top " << k << " frequent elements: ";
				for (int x : result) cout << x << " ";

				cout << endl;
				break;
			}

			case 4: {
				string str;

				cout << "Enter a string: ";
				cin >> str;

				char ch = firstUniqueChar(str);

				if (ch == '\0')
					cout << "No unique character found.\n";
				else
					cout << "First Unique Character: " << ch << endl;

				break;
			}

			case 5: {
				int n;

				cout << "Enter size of array: ";
				cin >> n;

				vector<int> nums(n);

				cout << "Enter elements: ";
				for (int i = 0; i < n; i++) cin >> nums[i];

				cout << "Duplicate Elements: ";
				findDuplicates(nums);
				cout << endl;

				break;
			}

			case 6:
				countGrades();
				break;

			case 7:
				countVotes();
				break;

			case 0:
				cout << "Exiting Program...\n";
				break;

			default:
				cout << "Invalid Choice!\n";
		}

	} while (choice != 0);

	return 0;
}
int repeatingelement(int arr[], int n) {
	unordered_set<int> seen;
	int firstRepeat = -1;

	for (int i = n - 1; i >= 0; i--) {
		if (seen.find(arr[i]) != seen.end()) {
			firstRepeat = arr[i];
		} else {
			seen.insert(arr[i]);
		}
	}
	return firstRepeat;
}

pair<int, int> twoSum(int arr[], int target, int length) {
	unordered_map<int, int> key;

	int first = 0, second = 0;
	for (int i = 0; i < length; i++) {
		first = arr[i], second = target - first;
		if (key.find(second) != key.end()) {
			return {key[second], i};
		} else {
			key[first] = i;
		}
	}
	return {-1, -1};
}

vector<int> topKFrequent(vector<int>& nums, int k) {
	unordered_map<int, int> freq;

	for (int num : nums) {
		freq[num]++;
	}

	vector<pair<int, int>> vec;
	for (auto& it : freq) {
		vec.push_back({it.second, it.first});
	}

	sort(vec.begin(), vec.end(), greater<pair<int, int>>());

	vector<int> ret;
	for (int i = 0; i < k; i++) {
		ret.push_back(vec[i].second);
	}
	return ret;
}

char firstUniqueChar(string str) {
	unordered_map<char, int> freq;

	for (char ch : str) {
		freq[ch]++;
	}

	for (char ch : str) {
		if (freq[ch] == 1) return ch;
	}
	return '\0';
}

void findDuplicates(vector<int>& nums) {
	unordered_map<int, int> freq;

	for (int num : nums) {
		freq[num]++;
	}

	for (auto it : freq) {
		if (it.second > 1) cout << it.first << " ";
	}
}

void countGrades() {
	ifstream file("grades.txt");
	if (!file) {
		cout << "File could not be opened!";
		return;
	}

	unordered_map<char, int> gradeCount;

	string name;
	char grade;

	while (file >> name >> grade) {
		gradeCount[grade]++;
	}

	cout << "Grade Counts:\n";

	for (char g = 'A'; g <= 'F'; g++) {
		cout << g << " : " << gradeCount[g] << endl;
	}
}

void countVotes() {
	ifstream file("votes.txt");
	if (!file) {
		cout << "File could not be opened!";
		return;
	}

	unordered_map<string, int> votes;
	string name;

	while (file >> name) {
		votes[name]++;
	}

	int maxVotes = 0;

	for (auto it : votes) {
		if (it.second > maxVotes) maxVotes = it.second;
	}

	for (auto it : votes) {
		cout << it.first << " : " << it.second << " votes - ";

		if (it.second == maxVotes) {
			cout << "Winner";
		} else {
			cout << "Loser";
		}
		cout << endl;
	}
}