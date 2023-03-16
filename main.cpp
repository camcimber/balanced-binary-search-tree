

#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
using namespace std;

class AVLTree {
public:

    struct TreeNode {
        int value;
        TreeNode* left;
        TreeNode* right;
        string name;
        int height;

        TreeNode(int value, string name) {
            this->name = name;
            this->value = value;
            left = nullptr;
            right = nullptr;
            height = 0;
        }
    };

    TreeNode* root;
    int numNodes = 0;

    AVLTree(){
        root = nullptr;
    }

    //height function
    int findHeight(TreeNode* node){

//        if(node == nullptr){
//            return 0;       //leaf nodes height = 0
//        }
//        return node->height;

        int maxHeight = 0;
        if (node != nullptr){
            maxHeight = max(findHeight(node->left), findHeight(node->right));
        }
        else{
            return 0;
        }

        return maxHeight + 1;
    }

    //getBalance function       balanced = -1,0,1
    int getBalanceFact(TreeNode* node){
        if(node == nullptr){
            return 0;
        }
        else
            //height of left subtree - right subtree
            return (findHeight(node->left) - findHeight(node->right));
    }

    //rotation functions
    TreeNode* rotateLeft (TreeNode* node)
    {
        TreeNode * newParent = node->right;
        TreeNode* grandchild = node->right->left;
        newParent->left = node;
        node->right = grandchild;

        return newParent; //aka new root
    }

    TreeNode* rotateRight (TreeNode* node)
    {
        TreeNode* newParent = node->left;
        TreeNode* grandchild = node->left->right;
        newParent->right = node;
        node->left = grandchild;

        return newParent;    //aka new root
    }

    TreeNode* insertHelper(TreeNode* root, int value, string name){
        if(root == nullptr){
            TreeNode* newNode = new TreeNode(value, name);
            cout << "successful" << endl;
            numNodes++;
            return newNode;
        }
        else if(value < root->value ){
            root->left = insertHelper(root->left, value, name);
        }
        else if(value > root->value){
            root->right = insertHelper(root->right, value, name);
        }
        else{
            cout << "unsuccessful"<< endl;
            return root;
        }

        //update height
//        root->height = 1 + max(findHeight(root->left),
//                               findHeight(root->right));

        //get balanced factor of root
        int balancedFactor = getBalanceFact(root);

        if(balancedFactor > 1 && value < root->left->value){  //L L
            return rotateRight(root);
        }
        if(balancedFactor < -1 && value > root->right->value){ // R R
            return rotateLeft(root);
        }
        if(balancedFactor > 1 && value > root->left->value) { //L R
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if(balancedFactor < -1 && value < root->right->value){
            root->right = rotateRight(root->right); // R L
            return rotateLeft(root);
        }

        return root;
    }

    void insert(string name, int id){
        if(this->root == nullptr) {
            this->root = insertHelper(this->root, id, name);
        }
        else{
            this->root = insertHelper(this->root,id, name);
        }
    }

    TreeNode* removeHelper(TreeNode* root, int value, string name){
        if(root == nullptr){
            return root;
        }
        string idDNE = searchID(value);
        if(idDNE.empty()){
            cout << "unsuccessful" << endl;
        }
        else if(value < root->value){
            root->left = removeHelper(root->left, value, name);
        }
        else if(value > root->value){
            root->right = removeHelper(root->right, value, name);
        }
        else if (value == root->value){    //item is in the local root
            if(root->left == nullptr && root->right == nullptr ){   //check no children
                delete (root);
                cout << "successful"<< endl;
                numNodes--;
                return nullptr;
            }
            else if(root->right == nullptr ){ //check if root has one child
                TreeNode* temp = root->left;
                delete(root);
                cout << "successful" << endl;
                numNodes--;
                return temp;
            }
            else if(root->left == nullptr){
                TreeNode* temp = root->right;
                delete(root);
                cout << "successful" << endl;
                numNodes--;
                return temp;
            }
            else {  //check if root has two children: inorder successor
                TreeNode* temp = root->right;
                while(temp->left != nullptr){
                    temp = temp->left;
                }
                root->value = temp->value;
                root->name = temp->name;
                root->right = removeHelper(root->right, temp->value, temp->name);
            }
        }

        return root;
    }
    void remove(string name, int id){
        this->root = removeHelper(this->root, id, name);
    }

    void removeInorderHelper(TreeNode* root, int n, int& curr){    //remove node at nth location

        if(root == nullptr){
            return;
        }
        removeInorderHelper(root->left, n, curr);
        if(curr == n){
            remove(root->name, root->value);

            if(n == curr){ //to ensure only removing one element
                curr++;
                return;
            }
        }
        curr++;
        removeInorderHelper(root->right, n, curr);

    }
    void removeInorder(int n){
        int curr = 0;
        if(n > numNodes){
            cout << "unsuccessful" << endl;
        }
        else {
            removeInorderHelper(this->root, n, curr);
        }
    }

    string searchIDHelper(TreeNode* root, int id, bool &n, string &nameToReturn){
        if(root == nullptr){
            n = false;
            return nameToReturn;
        }
        if(root->value == id) {
            n = true;
            nameToReturn = root->name;
            return nameToReturn;
        }
        else if(root->value > id && n == false) {
            searchIDHelper(root->left, id, n, nameToReturn);
        }
        else if(root->value < id && n == false) {
            searchIDHelper(root->right, id, n, nameToReturn);
        }
        return nameToReturn;

    }
    string searchID(int id){
        bool n = false;
        string nameToReturn = "";
        searchIDHelper(this->root, id, n, nameToReturn);
        return nameToReturn;
    }

    void searchNameHelper(TreeNode* root, string name, vector<int>& duplicateNameIds){
        if(root == nullptr){
            return;
        }
        if (name == root->name) {
            duplicateNameIds.push_back(root->value);
        }
        searchNameHelper(root->left, name, duplicateNameIds);

        searchNameHelper(root->right, name, duplicateNameIds);

    }
    void searchName(string name, vector<int>& duplicateNameIds){
        searchNameHelper(this->root,  name, duplicateNameIds);
    }

    void inorderHelper(TreeNode* root, vector<string> &vec, bool finished){
        if (root == nullptr) {
            return;
        }
        else {
            inorderHelper(root->left, vec, finished);

            vec.push_back(root->name);

            inorderHelper(root->right, vec, finished);

        }

    }
    void printInorder(vector<string> &vec){
        bool finished = false;
        inorderHelper(this->root, vec, finished);
    }

    void preorderHelper(TreeNode* root, vector<string> &vec) {
        if (root == nullptr) {
            return;
        }
        else {
            vec.push_back(root->name);

            preorderHelper(root->left, vec);

            preorderHelper(root->right, vec);
        }
    }
    void printPreorder(vector<string> &vec){
        preorderHelper(this->root, vec);
    }
    void postorderHelper(TreeNode* root, vector<string> &vec){
        if (root == nullptr) {
            return;
        }
        else {
            postorderHelper(root->left, vec);

            postorderHelper(root->right, vec);

            vec.push_back(root->name);
        }
    }
    void printPostorder(vector<string> &vec){
        postorderHelper(this->root, vec);
    }

    void printLevelCountHelper(TreeNode* root){

        if (root == nullptr){ //no height
            cout << 0 << endl;
        }
        else {
            cout << findHeight(root)  << endl;
        }

    }
    void printLevelCount(){
        printLevelCountHelper(this->root);
    }

};


int main() {

    AVLTree t;

    int numLines;
    string line, command;
    getline(cin, line);

    numLines = stoi(line); // access to number of lines

    while(numLines != 0) {

        string input;
        getline(cin, input);
        vector<string> output;  //contain all the strings -> for traversals
        vector<int> duplicateNameIds; //searchName command

        stringstream s_stream(input);
        getline(s_stream, command, ' '); //insert

        int idNum;
        unsigned int finder, finder2, finder3; //parsing helpers
        string name, idString;

        if(command == ("insert")){
            //parse to get the name ->
            finder = input.find('"'); // inside " -> should be index 0
            name = input.substr(finder + 1);    //ex. Steven" 12345678

            finder2 = name.find('"');
            name = name.substr(0, finder2); // print everything before " (name)

            //parse to get the idNum
            idString = input.substr(finder + finder2 + 3); // print everything after " (id)
            idNum = stoi(idString);

            //check line to ensure a-z A-z ' '
            regex nameCheck = regex("^[a-zA-Z\\s]*$");
            bool isAlpha = regex_match(name, nameCheck);

            //check IdNum to ensure 8 only digits
            regex idCheck = regex("^[0-9]{8}$");
            bool isIdNum = regex_match(idString, idCheck);
            if (!isIdNum || !isAlpha) {
                cout << "unsuccessful" << endl;
            }
            else{
                t.insert(name, idNum);
            }


        }
        else if(command == ("remove")){
            finder3 = input.find(' ');
            idString = input.substr(finder3 + 1); // 12345678 -> print everything after command
            idNum = stoi(idString);

            //check IdNum to ensure 8 only digits
            regex idCheck2 = regex("^[0-9]{8}$");
            bool isIdNum = regex_match(idString, idCheck2);
            if (!isIdNum) {
                cout << "unsuccessful" << endl;
            }

            t.remove(name, idNum);
        }
        else if(command == "removeInorder"){
            finder3 = input.find(' ');
            string inputString = input.substr(finder3 + 1);
            int inputNum = stoi(inputString);

            t.removeInorder(inputNum);

        }
        else if(command == "printPreorder"){
            output.clear();
            t.printPreorder(output);
            for(int i = 0; i < output.size() - 1; i++){
                cout << output[i] << ", ";
            }
            cout << output[output.size() - 1] << endl;
        }
        else if(command == "printInorder"){
            output.clear();
            t.printInorder(output);
            for(int i = 0; i < output.size() - 1; i++){
                cout << output[i] << ", ";
            }
            cout << output[output.size() - 1] << endl;
        }
        else if(command == "printPostorder"){
            output.clear();
            t.printPostorder(output);
            for(int i = 0; i < output.size() - 1; i++){
                cout << output[i] << ", ";
            }
            cout << output[output.size() - 1] << endl;
        }
        else if(command == "search") {
            finder3 = input.find(' ');
            string searchString = input.substr(finder3 + 1); // print everything after command

            //check IdNum to ensure 8 only digits
            regex idCheck = regex("^[0-9]{8}$");
            bool isIdNum = regex_match(searchString, idCheck);
            if (isIdNum) {
                idNum = stoi(searchString);
                string idName = t.searchID(idNum);
                if (idName == "") {
                    cout << "unsuccessful" << endl;
                } else {
                    cout << idName << endl;
                }
            }

            finder = input.find('"');
            name = input.substr(finder + 1);

            finder2 = name.find('"');
            name = name.substr(0, finder2);

            //check input to ensure a-z A-z ' '
            regex nameCheck = regex("^[a-zA-Z\\s]*$") ;
            bool isAlpha = regex_match(name, nameCheck);

            if(isAlpha){
                t.searchName(name, duplicateNameIds);
                if(duplicateNameIds.size() == 0){
                    cout << "unsuccessful" << endl;
                }
                else {
                    for (int i = 0; i < duplicateNameIds.size(); i++) {
                        cout << duplicateNameIds[i] << endl;
                    }
                }
            }

        }
        else if(command == "printLevelCount"){
            t.printLevelCount();
        }

        //decrement after operation complete
        numLines--;
    }

    return 0;
}
