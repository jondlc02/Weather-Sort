
#include "test.h"

// Method for adding data to tree
void weatherMap::addData()
{
    string line;
    string word;
    vector <string> row;

    fstream file;
    file.open("weather.csv", ios::in);
    //fstream file("weather.csv", ios::in);
    getline(file, line); //remove titles
    while (getline(file, line))
    {
        row.clear();
        stringstream str(line);
        while(getline(str, word, '"'))
        {
          if (word == "" || word == ",")
          {
            continue;
          }
            row.push_back(word);
                /*
                 * index legend
                 * 0 - precipitation
                 * 1 - full date
                 * 2 - month
                 * 3 - week
                 * 4 - year
                 * 5 - city
                 * 6 - code
                 * 7 - city/state
                 * 8 - state
                 * 9 - avgTemp
                 * 10 - maxTemp
                 * 11 - minTemp
                 * 12 - windDirection
                 * 13 - windSpeed
                 */
        }
        insert({row[1], row[7]}, stoi(row[9]), stoi(row[11]), stoi(row[10]), stod(row[0]), stod(row[13]));
    }
}

// Constructor && Destructor
weatherMap::weatherMap() {
    root = nullptr;
    //this->addData();
}

weatherMap::~weatherMap() {
    deleteMap(root);
}

// Main functions
void weatherMap::insert(pair <string, string> dateLocation, double avgTemp, double minTemp, double maxTemp, double precipitation, double windSpeed) {
    this->root = insertHelper(this->root, dateLocation, avgTemp, minTemp, maxTemp, precipitation, windSpeed);
}

// Main Function Helpers
Node* weatherMap::insertHelper(Node *&root, pair <string, string> dateLocation, double avgTemp, double minTemp, double maxTemp, double precipitation, double windSpeed) {
    if (root == nullptr) {
        root = new Node(dateLocation, avgTemp, minTemp, maxTemp, precipitation, windSpeed);
    }

    else if (root->dateLocation == dateLocation) { // Delete if dateLocation is not unique
        delete root;
        root = nullptr;
    }

    else if (dateLocation < root->dateLocation)
        root->left = insertHelper(root->left, dateLocation, avgTemp, minTemp, maxTemp, precipitation, windSpeed);

    else
        root->right = insertHelper(root->right, dateLocation, avgTemp, minTemp, maxTemp, precipitation, windSpeed);

    // Check balance factor of nodes to assure the tree stays balanced using rotations
    if (getBalanceFactor(root) > 1 && dateLocation < root->left->dateLocation)
        return rotateRight(root);
    else if (getBalanceFactor(root) > 1 && dateLocation > root->left->dateLocation)
        return rotateLeftRight(root);
    else if (getBalanceFactor(root) < -1 && dateLocation > root->right->dateLocation)
        return rotateLeft(root);
    else if (getBalanceFactor(root) < -1 && dateLocation < root->right->dateLocation)
        return rotateRightLeft(root);
    return root;
}

// Main command functions
vector <pair <int, string>> weatherMap::avgTemp(double low, double high) {
    return avgTempHelper(this->root, low, high);
}

vector <pair <int, string>> weatherMap::minTemp(double min) {
    return minTempHelper(this->root, min);
}

vector <pair <int, string>> weatherMap::maxTemp(double max) {
    return maxTempHelper(this->root, max);
}

vector <pair <int, string>> weatherMap::windSpeed(double low, double high) {
    return windSpeedHelper(this->root, low, high);
}

vector <pair <int, string>> weatherMap::precipitation(double low, double high) {
    return precipitationHelper(this->root, low, high);
}

// Main command function helpers
vector <pair <int, string>> weatherMap::avgTempHelper(Node *node, double low, double high) {
    if (node == nullptr)
        cout << "";
    else {
        avgTempHelper(node->left, low, high);
        if (node->avgTemp >= low && node->avgTemp <= high) {
          if (results.size() == 0)
                    {
                        results.push_back(make_pair(1, node->dateLocation.second));
                    }
                    else
                    {
                        for (int j = 0; j < results.size(); j++)
                        {
                            if (results.at(j).second == node->dateLocation.second)
                            {
                                results.at(j).first++;
                                break;
                            }
                            else
                            {
                                results.push_back(make_pair(1, node->dateLocation.second));
                                break;
                            }
                        }
                    }
          }
        avgTempHelper(node->right, low, high);
        
    }
    sort(results.begin(), results.end(), greater<pair<int, string>>());
    return results;
    
}

vector <pair <int, string>> weatherMap::minTempHelper(Node *node, double min) {
    if (node == nullptr)
        cout << "";
    else {
        minTempHelper(node->left, min);
        if (node->minTemp >= min) {
             if (results.size() == 0)
                    {
                        results.push_back(make_pair(1, node->dateLocation.second));
                    }
                    else
                    {
                        for (int j = 0; j < results.size(); j++)
                        {
                            if (results.at(j).second == node->dateLocation.second)
                            {
                                results.at(j).first++;
                                break;
                            }
                            else
                            {
                                results.push_back(make_pair(1, node->dateLocation.second));
                                break;
                            }
                        }
                    }
        }
        minTempHelper(node->right, min);
    }
    sort(results.begin(), results.end(), greater<pair<int, string>>());
    return results;
}

vector <pair <int, string>> weatherMap::maxTempHelper(Node *node, double max) {
    if (node == nullptr)
        cout << "";
    else {
        maxTempHelper(node->left, max);
        if (node->minTemp <= max) {
             if (results.size() == 0)
                    {
                        results.push_back(make_pair(1, node->dateLocation.second));
                    }
                    else
                    {
                        for (int j = 0; j < results.size(); j++)
                        {
                            if (results.at(j).second == node->dateLocation.second)
                            {
                                results.at(j).first++;
                                break;
                            }
                            else
                            {
                                results.push_back(make_pair(1, node->dateLocation.second));
                                break;
                            }
                        }
                    }
        }
        maxTempHelper(node->right, max);
    }
    sort(results.begin(), results.end(), greater<pair<int, string>>());
    return results;
}

vector <pair <int, string>> weatherMap::windSpeedHelper(Node *node, double low, double high) {
    if (node == nullptr)
        cout << "";
    else {
        windSpeedHelper(node->left, low, high);
        if (node->windSpeed >= low && node->windSpeed <= high) {
             if (results.size() == 0)
                    {
                        results.push_back(make_pair(1, node->dateLocation.second));
                    }
                    else
                    {
                        for (int j = 0; j < results.size(); j++)
                        {
                            if (results.at(j).second == node->dateLocation.second)
                            {
                                results.at(j).first++;
                                break;
                            }
                            else
                            {
                                results.push_back(make_pair(1, node->dateLocation.second));
                                break;
                            }
                        }
                    }
        }
        windSpeedHelper(node->right, low, high);
    }
    sort(results.begin(), results.end(), greater<pair<int, string>>());
    return results;
}

vector <pair <int, string>> weatherMap::precipitationHelper(Node *node, double low, double high) {
    if (node == nullptr)
        cout << "";
    else {
        precipitationHelper(node->left, low, high);
        if (node->precipitation >= low && node->precipitation <= high) {
             if (results.size() == 0)
                    {
                        results.push_back(make_pair(1, node->dateLocation.second));
                    }
                    else
                    {
                        for (int j = 0; j < results.size(); j++)
                        {
                            if (results.at(j).second == node->dateLocation.second)
                            {
                                results.at(j).first++;
                                break;
                            }
                            else
                            {
                                results.push_back(make_pair(1, node->dateLocation.second));
                                break;
                            }
                        }
                    }
            }
        precipitationHelper(node->right, low, high);
    }
    sort(results.begin(), results.end(), greater<pair<int, string>>());
    return results;
}

bool weatherMap::searchVector(vector <pair <int, string>> results, string location) {
    for (auto p : results) {
        if (p.second == location)
            return true;
    }
    return false;
}

// Rotate helper functions based off class slides
Node *weatherMap::rotateLeft(Node *node) {
    Node *grandchild = node->right->left;
    Node *newParent = node->right;
    newParent->left = node;
    node->right = grandchild;
    return newParent;
}

Node *weatherMap::rotateRight(Node *node) {
    Node *grandchild = node->left->right;
    Node *newParent = node->left;
    newParent->right = node;
    node->left = grandchild;
    return newParent;

}

Node *weatherMap::rotateLeftRight(Node *node) {
    Node* greatGrandChild = node->left->right->left;
    Node* newChild = node->left->right;
    Node* grandChild = node->left;
    node->left = newChild;
    newChild->left = grandChild;
    grandChild->right = greatGrandChild;
    Node* newParent = rotateRight(node);
    return newParent;
}

Node *weatherMap::rotateRightLeft(Node *node) {
    Node* greatGrandChild = node->right->left->right;
    Node* newChild = node->right->left;
    Node* grandChild = node->right;
    node->right = newChild;
    newChild->right = grandChild;
    grandChild->left = greatGrandChild;
    Node* newParent = rotateLeft(node);
    return newParent;
}

// Additional helper functions
void weatherMap::deleteMap(Node *node) {
    if (node != nullptr) {
        deleteMap(node->left);
        deleteMap(node->right);
        delete node;
        node = nullptr;
    }

}

double weatherMap::getHeight(Node *node) {
    if (node == nullptr)
        return 0;
    else
        return 1 + max(getHeight(node->left), getHeight(node->right));
}

double weatherMap::getBalanceFactor(Node *node) {
    if (node == nullptr)
        return 0;

    return getHeight(node->left) - getHeight(node->right);
}