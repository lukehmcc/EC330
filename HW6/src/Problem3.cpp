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
  TrieNode(std::string key) : isWord(false), key(key) {}

  // prints from whatever level you give it
  static void printFrom(const TrieNode *root, std::string prefix = "",
                        int depth = 0) {
    if (!root)
      return;

    // indent 2 spaces per level
    std::string indent(depth * 2, ' ');

    // print the current key (empty on the synthetic root)
    if (!prefix.empty())
      std::cout << indent << prefix << (root->isWord ? " *" : "") << '\n';

    // recurse into children
    for (const auto &kv : root->children)
      printFrom(kv.second, kv.first, depth + 1);
  }

  // prints all info of the current node
  void printNode() const {
    std::cout << "Node key: \"" << key << "\"\n";
    std::cout << "isWord: " << std::boolalpha << isWord << '\n';
    std::cout << "Children count: " << children.size() << '\n';
    if (!children.empty()) {
      std::cout << "Children keys: ";
      for (const auto &kv : children)
        std::cout << '"' << kv.first << "\" ";
      std::cout << '\n';
    }
  }
};

// peeks ahead at the stream to get future chars n spots ahead
char peekAhead(std::istream &in, std::size_t n) {
  std::string buf;
  buf.reserve(n);
  char c;
  while (buf.size() < n && in.get(c))
    buf.push_back(c);

  bool sucsess = (n == buf.size()) ? true : false;

  // restore the stream position
  for (auto it = buf.rbegin(); it != buf.rend(); ++it)
    in.putback(*it);

  in.clear(); // reset in case there is an overflow near EOF

  // either return the char or an error
  if (sucsess) {
    return c;
  } else {
    return '\0';
  }
}

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
        current = current->children.at(subst);
        // or if it doesn't
      } else {
        // and if it is the full size, mark it as a word
        TrieNode *newNode = new TrieNode(subst);
        if (i + 1 == line.size()) {
          newNode->isWord = true;
        }
        current->children[subst] = newNode;
        current = current->children.at(subst);
      }
    }
  }

  // 2: From each index, check if following letters match trie
  std::ifstream inFile(fileName);
  if (!inFile) {
    std::cerr << "Cannot open " << fileName << '\n';
    return -1;
  }
  int wordCount = 0;
  char ch;
  while (inFile.get(ch)) {
    current = root;
    std::string word(1, ch);
    int c = 0; // acc to keep track of how far forward you want to peek
    // keep recurring until you fall off the trie
    while (true) {
      c++;
      // if the word exists, do something
      if (current->children.count(word)) {
        // set the current to the child
        current = current->children.at(word);
        // if it is a word count that
        if (current->isWord) {
          wordCount++;
        }
        // then seek ahead to the next letter
        char peek = peekAhead(inFile, c);
        // if you hit EOF, break
        if (peek == '\0') {
          break;
        }
        word.push_back(peek);
        // now that the word has updated, repeat this
      } else {
        // you feel off the tree, break
        break;
      }
    }
  }
  // that while lops fails but the last var gets pulled, so make sure to check
  // if that one is a valid trie entry

  std::string endString = std::string(1, ch);
  if (root->children.count(endString) && root->children.at(endString)->isWord) {
    wordCount++;
  }

  // 3: Return
  return wordCount;
}
