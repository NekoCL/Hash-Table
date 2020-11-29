#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Hash {
private:
    static const int table_slots = 26;

    struct Node {
        string key;
        int value;
    };

    Node* hash_table[table_slots];

public:
    Hash();
    void insert_node(string key, int value);
    void delete_node(string key, int value);
    void print_table();

};

//Initiate an empty hash table
Hash::Hash() {
    for (int i = 0; i < table_slots; i++) {
        hash_table[i] = new Node;
        hash_table[i]->key = "never_used";
        hash_table[i]->value = 97+i;
    }
}

//Method to insert into the hash table
void Hash::insert_node(string key, int value) {
    int index = value-97;
    int index_start = index;
    int temp_value = value;

    //Add into a free slot
    if ( hash_table[index]->key == "never_used" || hash_table[index]->key == "tombstone" ) {
        hash_table[index]->key = key;
    } else if ( hash_table[index]->key == key ) {
        //do nothing if key is already there
    } else {
        temp_value++;
        index++;
        if ( temp_value > 122 ) {
            temp_value = 97;
        }
        if ( index > 25 ) {
            index = 0;
        }

        //Loop until a free slot is found
        for (int i = index; i < table_slots; i++) {
            if ( hash_table[index]->key == "never_used" || hash_table[index]->key == "tombstone" ) {
                hash_table[index]->key = key;
                break;
            } else {
                temp_value++;
                index++;
            }
        }
        //Looping back to start of table
        if ( hash_table[index]->key != key ) { //check if last slot already got inserted
            if ( temp_value > 122 ) {
                temp_value = 97;
            }
            if ( index > 25 ) {
                index = 0;
            }
            for (int i = index; i < index_start; i++) {
                if ( hash_table[index]->key == "never_used" || hash_table[index]->key == "tombstone" ) {
                    hash_table[index]->key = key;
                    break;
                } else {
                    temp_value++;
                    index++;
                }
            }
        }

    }
}

//Method to delete from the hash table
void Hash::delete_node(string key, int value) {
    int index = value-97;
    int index_start = index;
    int temp_value = value;

    //Loop until key is found
    for (int i = index; i < table_slots; i++) {
        if ( hash_table[index]->key == key ) {
            hash_table[index]->key = "tombstone";
            break;
        } else {
            temp_value++;
            index++;
        }
    }
    //Looping back to start of table
    if ( temp_value > 122 ) {
        temp_value = 97;
    }
    if ( index > 25 ) {
        index = 0;
    }
    for (int i = index; i < index_start; i++) {
        if ( hash_table[index]->key == key ) {
            hash_table[index]->key = "tombstone";
            break;
        } else {
            temp_value++;
            index++;
        }
    }

}

//Method to print the hash table
void Hash::print_table() {
    for (int i = 0; i < table_slots; i++) {
        if ( hash_table[i]->key == "never_used" || hash_table[i]->key == "tombstone" ) {
            //ignore empty slots
        } else {
            cout << hash_table[i]->key + " ";
        }
    }
}


int main() {
    vector<string> inputs;
    string read;
    getline(cin,read);
    string get_key;
    stringstream input(read);

    string key;
    int value; //97 to 122 for a to z

    //Initiate a hash table
    Hash new_table;

    //Get the inputs
    while ( input >> get_key ) {
        inputs.push_back(get_key);
    }

    //For loop to read inputs. Leading A for insertion, leading D for deletion
    for (int i = 0; i < inputs.size(); i++) {
        if ( inputs[i][0] == 'A' ) { //add
            inputs[i].erase(0,1);
            value = (int)inputs[i].back();
            new_table.insert_node(inputs[i], value);

        } else if ( inputs[i][0] == 'D' ) { //delete
            inputs[i].erase(0,1);
            value = (int)inputs[i].back();
            new_table.delete_node(inputs[i], value);

        }
    }

    //Print the hash table
    new_table.print_table();

    return 0;
}
