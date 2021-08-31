#include <bits/stdc++.h>
#include <string.h>
using namespace std;

#define ALPHABET_SIZE 26
#define false 0
#define true 1
#define MAX_WORD_SIZE   50
#define MAX_MEANING_SIZE 1000

int letterToInt(char letter)  {

    if (letter >= 'A' && letter <= 'Z')  {
        return letter - 'A';
    }

    else if (letter >= 'a' && letter <= 'z')  {
        return letter - 'a';
    }

    return -1;
}

struct trieNode  {

    struct trieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    string value;

};

struct trieNode* getNode(void)  {

    struct trieNode *pNode =  new trieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)  {
        pNode->children[i] = NULL;
    }

    return pNode;
}

int insert(struct trieNode *root, string word, string meaning)  {

    struct trieNode *pCrawl = root;

    for (int i = 0; i < word.length(); i++)  {

        int index = letterToInt(word[i]);

        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    pCrawl->isEndOfWord = true;
    pCrawl->value = "";

    if(meaning != "null")  {
        pCrawl->value = meaning;
    }

    return true;
}

bool search(struct trieNode *root, string word)  {

    struct trieNode *pCrawl = root;

    for (int i = 0; i < word.length(); i++)  {

        int index = letterToInt(word[i]);

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    if (pCrawl != NULL && pCrawl->isEndOfWord && pCrawl->value != "")  {

        cout << "The meaning of the word is: \n";
        cout << pCrawl->value;
    }

    else if(pCrawl->value == "" and pCrawl->isEndOfWord)  {
        cout << "The meaning of this word is yet to be added." << endl;
    }

    else  
        return false;
  
    return true;
}

bool deleteWord(struct trieNode *root, string word)  {

    struct trieNode *pCrawl = root;

    for (int i = 0; i < word.length(); i++)  {

        int index = letterToInt(word[i]);

        if (!pCrawl->children[index])  {
            return false;
        }

        pCrawl = pCrawl->children[index];
    }

    if (pCrawl != NULL && pCrawl->isEndOfWord)  {

        pCrawl->isEndOfWord = false;
        return true;
    }

    return false;
}


void alphabeticalOrder(struct trieNode* root, char allWords[], int index)  {

    struct trieNode* pCrawl = root;

    if(pCrawl != NULL && pCrawl->isEndOfWord == true)  {

        for(int j = 0; j < index; j++)  {
            cout << allWords[j];
        }

        if(pCrawl->value != "")  {
            cout << ": ";
        }

        cout << pCrawl->value << "\n";
    }

    for(int i = 0; i < ALPHABET_SIZE; i++)  {
        if(pCrawl->children[i] != NULL) {
            allWords[index] = 'a' + i;

            alphabeticalOrder(pCrawl->children[i], allWords, index + 1 );
        }
    }
}

void print_prefix_search(struct trieNode* root, char allWords[], int index, string prefix)  {

    struct trieNode* pCrawl = root;

    if(pCrawl != NULL && pCrawl->isEndOfWord == true) {

        cout << prefix;

        for(int j = 0; j < index; j++)  {
            cout << allWords[j];
        }

        if(pCrawl->value != "") {
            cout << ": ";
        }

        cout << pCrawl->value << "\n";

    }

    for(int i = 0; i < ALPHABET_SIZE; i++)  {

        if(pCrawl->children[i] != NULL) {

            allWords[index] = 'a' + i;

            print_prefix_search(pCrawl->children[i], allWords, index + 1, prefix);
        }
    }

    return;
}

void prefix_search(struct trieNode* root, string prefix)  {

    struct trieNode* pCrawl = root;

    for(int i = 0; i < prefix.length(); i++){

        int index = letterToInt(prefix[i]);

        if(!pCrawl->children[index]){

            cout << "No string exist with the given prefix"<<"\n";
            return;
        }

        pCrawl = pCrawl->children[index];
    }

    char allWords[50];

    print_prefix_search(pCrawl, allWords, 0, prefix);
}

bool searchSuggestedWord(struct trieNode* root, string word, int count)  {
  
    struct trieNode *pCrawl = root;

    for (int i = 0; i < word.length(); i++)  {

        int index = letterToInt(word[i]);

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    if (pCrawl != NULL && pCrawl->isEndOfWord)  {
      
        if(count == 0)  {
            cout << "Suggested words are: ";
        }
        cout << word << "  ";
    }
  
    else 
        return false;
  
    return true;
}

bool suggestedWords(struct trieNode* root, string word, int number)  {

    int count = 0;

    for(int i = 0; i < word.length(); i++)  {

        string temp = word;

        for(int j = 0; j < ALPHABET_SIZE; j++)  {

            if(count < number && j != letterToInt(word[word.length() - i - 1]))  {

                temp[word.length() - i - 1] = j + 97;

                if(searchSuggestedWord(root, temp, count) and count < number)  {
                    count++;
                }
            }
        }
    }

    if(count == 0)  {
            cout << "\nSorry we couldn't find any words related to " << word << " in our Dictionary.\n";
        return false;
    }

    else if (count < number)  {
        cout << "\nWe could only find " << count << " words related to " << word << " in our Dictionary.\n";
        return true;
    }

    else   {
        return true;
    }
}

void get_Str(struct trieNode *temp,string s, int *n, vector<string> &suggestion_arr)  {

    if(*n == 0)  return;
    
    if(temp->isEndOfWord and (*n > 0 or *n == -1))  {

        suggestion_arr.push_back(s);
        if(*n > 0)
            (*n)--;
    }

    for(int i = 0; i < 26; i++)  {

        if(temp->children[i] != NULL)  {

            s.push_back((char)(i+'a'));

            get_Str(temp->children[i],s,n,suggestion_arr);

            s.pop_back();
        }
    }
}


void Suggest_Str(struct trieNode* root,string s, int *n, vector<string> &suggestion_arr)  {

    struct trieNode *temp=root;

    for(int i = 0; i < s.length(); i++)  {

        if(temp->children[letterToInt(s[i])] == NULL)  {

            get_Str(temp,s.substr(0,i),n,suggestion_arr);
            return ;
        }

        temp=temp->children[letterToInt(s[i])];
    }

    get_Str(temp,s,n,suggestion_arr);

    return;
}

bool check(struct trieNode *root,string s)  {

    struct trieNode *temp=root;

    for(int i = 0; i < s.length(); i++)  {

        if(temp->children[letterToInt(s[i])] == NULL)  
            return false;

        temp=temp->children[letterToInt(s[i])];
    }

    return temp->isEndOfWord;
}

int remove_parenthesis(string &word, string &duplicate){

    int flag = 0;

    if(letterToInt(word[word.size()-1]) == -1)  {

        if(word.back() >= '0' and word.back() <= '9');
        else word.pop_back();
    }
  
    if( word.size() > 0 and letterToInt(word[0]) == -1){

        if(word[0] >= '0' and word[0] <= '9');
        else word.erase( word.begin() + 0);
    }

    duplicate=word;

    for(int i = 0; i < word.size(); i++)  { 

        if(letterToInt(word[i]) == -1){
            word.erase( word.begin() + i );
            i--;
            flag = 1;
        }

    }

    return flag;
}

void spellCheckConsole(struct trieNode *root, string &word)  {

    int flag = 0;
    string duplicate;

    flag = remove_parenthesis(word,duplicate);

    if(word.size() == 0){
        return ;
    }

    if(flag == 0 and check(root,word))  {
        cout << "This word is a valid English Word!!!!" << "\n";
    }

    else  {

        cout << "This is not a valid English Word!!!"<< "\n";
        cout << "How many word you want as suggestion (if 'All' Enter -1): ";

        int n ;
        cin >> n;

        vector<string>suggestion_arr;
        Suggest_Str(root, word, &n, suggestion_arr);

        cout << "Number of suggested words are " << suggestion_arr.size() << "\n";

        for(auto i: suggestion_arr)  {
            cout << i << "\n";
        }
     }
}

void suggestVaryingWords(trieNode *root, string &word)  {
 
    cout << "How many word you want as suggestion (if 'All' Enter -1): ";

    int n;
    cin >> n;

    vector<string> suggestion_arr;
    Suggest_Str(root, word, &n, suggestion_arr);

    cout << "Number of suggested words are " << suggestion_arr.size() <<"\n";

    for(auto i: suggestion_arr)  {
        cout << i << "\n";
    }
}

void spellCheckFile(struct trieNode *root, string file_name) {

    string word;

    ifstream file1(file_name);

    while(file1 >> word) {

        int flag = 0;
        string duplicate;

        flag = remove_parenthesis(word,duplicate);

        if(word.size() == 0)
            continue;

        else if(flag == 0 and check(root,word))  {
            cout << "String" << word << " is present" <<"\n";
        }

        else  {

            cout << duplicate<< " is not a valid English Word!!!" << "\n";
            cout << "How many word you want as suggestion: ";

            int n;
            cin >> n;

            int Count=n;

            vector<string>suggestion_arr;
            Suggest_Str(root, word, &n, suggestion_arr);

            cout << "Number of suggested words are " << suggestion_arr.size() <<"\n";

            for(auto i: suggestion_arr)  {
                cout << i << "\n";
            }
        }
    }
}

void trie_input(struct trieNode *root)  {

    int count=0;

    ifstream file("koo.txt");

    string str,meaning,duplicate;

     while (!file.eof()) {

        file>>str;
        remove_parenthesis(str,duplicate);

        getline(file, meaning);

        if(str.size()>0)
            insert(root,str,meaning);

        count++;

    }
  
    cout << "Welcome to our Dictionary. Our Dictionary right now contains " << count << " words.\n";
}

bool isvalid(string &meaning)  {

    for(auto i: meaning)  {

        if(letterToInt(i) == -1)  {
            return false;
        }
    }

    return true;
}

string valid_word()  {
    string word;

    do {
        cin >> word;

        if(isvalid(word))  {
            break;
        }

        cout << "Not a valid word(use alphabet only), Please enter again: ";
    }while(true);

    return word;
}

string valid_meaning()  {
    string meaning;

    do {
        cin >> meaning;

        if(isvalid(meaning))  {
            break;
        }
        cout << "Not a valid meaning(use alphabet only), Please enter again: ";

    }while(true);

    return meaning;
}

int main()  {

    struct trieNode *root = getNode();

    trie_input(root);

    string command;

    do  {

        cout << "\nWhat would you like to do?\n";
        cout << "1. Insert a word.\n";
        cout << "2. Search the meaning of a word.\n";
        cout << "3. Delete a word.\n";
        cout << "4. Print dictionary in alphabetical order.\n";
        cout << "5. Prefix search.\n";
        cout << "6. Show suggested words of same Length.\n";
        cout << "7. Show suggested words.\n";
        cout << "8. Check Spelling. \n";

        fflush(stdin);

        cout << "Enter your choice: ";

        int call;
        cin >> call;
        cout << "\n";

        string word;
        string meaning;

        switch(call){

            case 1:
                    cout << "Enter the word you would like to insert: ";
                    word = valid_word();

                    cout << "Enter its meaning: ";
                    meaning = valid_meaning();

                    if(insert(root, word, meaning))  {
                        cout << word << " has been added to the Dictionary.\n";
                    }

                    break;

            case 2:

                    cout << "Enter the word you would like to search: ";
                    word = valid_word();

                    if(!search(root, word))  {
                        cout << "Sorry, the word you searched for doesn't exist." << endl;
                        cout << "Would you like to add it to the Dictionary.(Yes/No) ";

                        string add;
                        cin >> add;

                        if(add == "yes" || add == "Yes" || command == "YES")  {

                            cout << "Enter its meaning: ";
                            meaning = valid_meaning();

                            if(insert(root, word, meaning)) {
                                cout << word << " has been added to the Dictionary.\n";
                            }
                        }
                    }

                    break;

            case 3:
                    cout << "Which word would you like to delete? ";
                    word = valid_word();

                    if(deleteWord(root, word))  {
                        cout << word << " has been successfully deleted from the Dictionary.\n";
                    }

                    else  {
                        cout << "No such word exists in the Dictionary.\n";
                    }

                    break;

            case 4:
                    char allWords[50];

                    alphabeticalOrder(root, allWords, 0);
                    cout << "\n";

                    break;

            case 5:
                    cout << "Enter the word you would like to use as a prefix: ";
                    word = valid_word();
                    cout << "\n";

                    prefix_search(root, word);

                    break;

            case 6:
                    cout << "Enter the word for whose suggested words you want to see of same length: ";

                    word = valid_word();
                    int number;

                    cout << "How many suggested words do you want to see: ";
                    cin >> number;

                    suggestedWords(root, word, number);

                    break;

            case 7:
                    cout << "Enter a word for whose suggested words you want : ";
                    word = valid_word();

                    suggestVaryingWords(root, word);

                    break;

            case 8:

                    cout << "Choose one of the following options: ";

                    cout << "1 - Use Spell Checker for Console: " << "\n";
                    cout << "2 - Use Spell Checker for file: " << "\n";

                    cout << "Enter your choice: ";

                    int choice;
                    cin >> choice;

                    if(choice == 1)  {

                        cout << "Enter a word to check it correct or not and get suggested words if it is not correct"<< "\n";
                        word = valid_word();

                        spellCheckConsole(root,word);
                    }

                    else  {

                        cout<<"Enter the name of the input file to get suggestions for the wrong words" << "\n";
                        cin >> word;

                        spellCheckFile(root, word);
                    }


                    break;

            default: cout << "Enter a valid entry.";
        }

    fflush(stdin);
        cout << "\n\nWould you like to continue or exit?(Yes/No) ";
        cin >> command;
    }

    while(command == "yes" || command == "Yes" || command == "YES");

    cout << "Thanks for using our Dictionary.\n";

    return 0;
}
