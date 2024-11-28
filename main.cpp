#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <stack>
#include <chrono>

using namespace std; 

const int INF = INT_MAX;

struct Person{
    string name;
    string lastName;
    string adress; 
    string dna;
    string phoneNum;
};

vector <Person> people;
vector <vector<int>> matrix;

void loadData(const string& fileName){
    ifstream file(fileName);
    if(!file.is_open()){
        cout << "No se pudo abrir el archivo \n";
        return;
    }

    string line;
    while(getline(file, line)){
        stringstream ss(line);
        Person person;

        getline(ss, person.name, ',');
        getline(ss, person.lastName, ',');
        getline(ss, person.adress, ',');
        getline(ss, person.dna, ',');
        getline(ss, person.phoneNum, ',');

        people.push_back(person);
    }

    file.close();
}

void adjMatrix(){
    int n = people.size();
    matrix = vector<vector<int>>(n, vector<int>(n, INF));

    srand(time(0));

    for (int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if (i == j){
                matrix[i][j] = 0;
            }
            else{
                int  weight = (rand() %100 < 80) ? rand() % 10 + 1 :INF;    
                matrix[i][j] = weight;
                matrix[j][i] = weight;     
            }
        }
    }
}

int bfsSearch(const string& wantedDNA){
    queue<int> q;
    vector<bool> visited(people.size(), false);

    q.push(0);
    visited[0] = true;

    while(!q.empty()){
        int atMoment = q.front();
        q.pop();
    
    if(people[atMoment].dna == wantedDNA){
        return atMoment;
    }

    for(int i = 0; i < matrix[atMoment].size(); ++i){
        if (matrix[atMoment][i] != INF && !visited[i]){
            q.push(i);
            visited[i] = true;
        }
    }

    }
    return -1;
}

int dfsSearch(const string& wantedDNA){
    stack<int> s;
    vector<bool> visited(people.size(), false);

    s.push(0);
    visited[0] = true;

    while(!s.empty()){
        int atMoment = s.top();
        s.pop();
    
    if(people[atMoment].dna == wantedDNA){
        return atMoment;
    }

    for(int i = 0; i < matrix[atMoment].size(); ++i){
        if (matrix[atMoment][i] != INF && !visited[i]){
            s.push(i);
            visited[i] = true;
        }
    }

    }
    return -1;  
}

int main(){
    loadData("people.txt");

    string searchDNA;
    cout << "Que DNA desea buscar? \n";
    cin >> searchDNA;

    auto startBFS = chrono::high_resolution_clock::now();
    int indexBFS = bfsSearch(searchDNA);
    auto endBFS = chrono::high_resolution_clock::now();

    double timeBFS = chrono::duration<double,milli>(endBFS - startBFS).count();
    if (indexBFS != -1){
        cout << "Se encontro con BFS a la persona " << people[indexBFS].name <<  " " <<people[indexBFS].lastName << " en " << timeBFS << " milisegundos\n";
    }
    else{
        cout << "No se encontró a una persona con ese ADN";
    }

    auto startDFS = chrono::high_resolution_clock::now();
    int indexDFS = dfsSearch(searchDNA);
    auto endDFS = chrono::high_resolution_clock::now();

    double timeDFS = chrono::duration<double,milli>(endDFS - startDFS).count();
    if (indexDFS != -1){
        cout << "Se encontro con DFS a la persona " << people[indexDFS].name << " " << people[indexDFS].lastName <<" en " << timeDFS << " milisegundos\n";
    }
    else{
        cout << "No se encontró a una persona con ese ADN";
    }
    
    return 0;


}

//video: https://drive.google.com/drive/folders/1QbdUQ2rXbnRU017gLGJYYTCQnuRHP88T?usp=sharing
