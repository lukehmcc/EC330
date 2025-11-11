#include <cctype>
#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

// finds the number of BU-IDs in the file whose digits add to a number greater
// than 28
// A BUID starts with a U -> 8 numbers -> non number
int threeA(std::string fileName) {
  // load the file
  std::ifstream inFile(fileName);
  if (!inFile) {
    std::cerr << "Cannot open " << fileName << '\n';
    return -1;
  }

  // some vars
  int validIDCounter = 0;
  int currentState = -1;
  int currentAcc = 0;

  // now read char by char
  char ch;
  while (inFile.get(ch)) {
    // check if BUID has started
    if (ch == 'U' && currentState == -1) {
      currentState = 0;
    }
    // now check if you're in the numeric section
    else if (currentState > -1 && ch >= '0' && ch <= '9' && currentState < 8) {
      currentAcc += ch - '0';
      currentState++;
      // if numeric condition not met, ereset the current state & counter
    } else {
      // condition for the end of the ID checker
      if (currentState == 8 && currentAcc > 28) {
        validIDCounter++;
      }
      currentState = -1;
      currentAcc = 0;
    }
  }
  return validIDCounter;
}

void printQueue(std::queue<char> inQueue) {
  // iterate throught and print elements
  std::cout << "Current sentence: ";
  while (!inQueue.empty()) {
    std::cout << inQueue.front();
    inQueue.pop();
  }
  std::cout << std::endl;
}
bool isPangram(std::queue<char> inQueue) {
  // define the vector
  std::vector<int> v;
  v.resize(256, 0); // resize to full ascii

  // iterate throught and count elements
  while (!inQueue.empty()) {
    if (!isalpha(inQueue.front())) {
      continue;
    }
    v[tolower(inQueue.front())]++;
    inQueue.pop();
  }

  // ensure a-z are all accounted for
  for (int i = 'a'; i < 'z'; i++) {
    if (v[i] == 0) {
      return false;
    }
  }

  return true;
}

bool isPangramFromFreqTab(int *data) {
  for (int i = 0; i < 26; i++) {
    if (data[i] == 0) {
      return false;
    }
  }
  return true;
}

void printFreqTab(int *data) {
  for (int i = 0; i < 26; i++) {
    std::cout << data[i];
    if (i != 25) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;
}

std::string queueToString(std::queue<char> queue) {
  std::string toReturn;
  while (!queue.empty()) {
    toReturn.push_back(queue.front());
    queue.pop();
  }
  return toReturn;
}

// determines the shortest length of a panagram
int threeB(std::string fileName) {
  // The method I will be using: Worm method O(n)
  int shortestLength = INT_MAX;
  std::string shortestPangram = "";

  // load the file
  std::ifstream inFile(fileName);
  if (!inFile) {
    std::cerr << "Cannot open " << fileName << '\n';
    return -1;
  }

  // Create a queue
  std::queue<char> sentence;
  int freqTab[26] = {};

  // start looping through the file
  char ch;
  while (inFile.get(ch)) {
    // debug prints
    // std::cout << "new char: " << ch << std::endl;
    // printQueue(sentence);
    // printFreqTab(freqTab);

    // // 1: Repeatedly queue and check if pangram. Once pangram, record that
    // // length if shorter than current shortest.
    // // 2: Once pangram, dequeue until not pangram.
    // // 3: Repeat until EOF
    // // 4: Return the shortest length
    ch = tolower(ch); // make sure to only deal with lower case
    sentence.push(ch);
    if (isalpha(ch)) {
      freqTab[ch - 'a']++;
    }
    while (isPangramFromFreqTab(freqTab)) {
      if (sentence.size() < shortestLength) {
        shortestLength = sentence.size();
        shortestPangram = queueToString(sentence);
      }
      if (isalpha(sentence.front())) {
        freqTab[sentence.front() - 'a']--;
      }
      sentence.pop();
    }
  }
  return (shortestLength == INT_MAX) ? -1 : shortestLength;
}

class TrieNode {
public:
  std::string key;
  std::unordered_map<std::string, TrieNode *> children;
  bool isWord;
  TrieNode() : isWord(false) {}
};

// returns how many valid dictonary words there are in the file
int threeC(std::string fileName) {
  // Use Trie (O(n*m)) where:
  // n: file length
  // m: size of dictionary

  // 1: Create a Trie
  std::ifstream dict("dictionary.txt");
  if (!dict) {
    std::cerr << "Cannot open " << fileName << '\n';
    return -1;
  }

  TrieNode *root = new TrieNode;
  TrieNode *current = root;
  std::string line;
  while (std::getline(dict, line)) {
    current = root;
    for (int i = 0; i < line.size(); i++) {
      // check if there already is this substring at this level. if there isn't
      // then create it and keep moving down.
      std::string subst = line.substr(0, i + 1); // grab that many chars
      // if it contains that substring
      if (current->children.count(subst)) {

        // or if it doesn't
      } else {
      }
    }
  }

  // 2: From each index, check if following letters match trie
  std::ifstream inFile(fileName);
  if (!inFile) {
    std::cerr << "Cannot open " << fileName << '\n';
    return -1;
  }
  // 3: If they do add to the count
  return 0;
}
