#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>


void load_file(const std::string file_name, std::vector<std::string> *data_vector){
        std::string line; //stores the current line being processed
        std::ifstream infile(file_name); // create a OS file_handle to the actual input file
        while(std::getline(infile, line)) { //copies the line being processed to the line variable 
                data_vector->push_back(line); //adds it to our data_vector
        }
        infile.close(); //we cannot forget to close this or bad things happen!
}

void count_data(const std::vector<std::string> *data_vector, std::map<std::string, int> *final_counts) {

        for(auto data_entry : *data_vector) {
                if(final_counts->find(data_entry) == final_counts->end()) { // if we dont get to the end of the map before finding our data_entry
                                                                            //We didn't find any entry so add it as a new pair to the map with an initial count of 1
                        std::cout << "[!]\tNo entry found for : " << data_entry << " adding to counts map" << std::endl;
                        final_counts->insert(std::make_pair(data_entry, 1)); //add a new entry if we dont already have one
                } else { 
                        //We did find the entry, so locate it in the map and increment it's value by 1
                        std::map<std::string, int>::iterator it = final_counts->find(data_entry);
                        it->second++;
                }
        }
}

void print_data(const std::map<std::string, int> *final_counts) {
        for(auto &data_entry : *final_counts) {
                std::cout << "[=]\t Key: " << data_entry.first << " Value: " << data_entry.second << std::endl;
        }
}

void determine_distribution(const std::map<std::string, int> *final_counts) {
        int total = 0 ; //used to track our total
        // Work out what our total is
        for(auto &data_entry : *final_counts) {
                total += data_entry.second;
        }
        std::cout << "[=]\t Total number of items: " << total << std::endl;
        //Calculate the percentage of the total for each pet
        std::cout << "[+]\t Determining distribution" << std::endl;
        for(auto &data_entry: *final_counts) {
                float count = static_cast<float>(data_entry.second); // We would lose precision if we did this as integer math
                auto distribution = (count / static_cast<float>(total)) * 100.0f; // Work out the percentage of total
                std::cout << "[=]\t Distribution for Key: " << data_entry.first << " : " << distribution << "%" << std::endl;
        }
}

void find_max(const std::map<std::string, int> *final_counts) {
        std::string key = "";
        int max = -1;
        for(auto &data_entry: *final_counts) {
                if(data_entry.second > max) {
                        max = data_entry.second; //New max is value
                        key = data_entry.first; // for our output
                }
        }
        std::cout << "[=]\t Max value: " << max << " Key: " << key << std::endl;
}

void find_min(const std::map<std::string, int> *final_counts) {
        int min = INT_MAX; // crazy big number! 
        std::string key = "";
        for(auto &data_entry : *final_counts) {
                if(data_entry.second < min) {
                        min = data_entry.second; // make min our value
                        key = data_entry.first; // for our output!
                }
        }    
        std::cout << "[=]\t Min Value: " << min << " Key: " << key << std::endl;
}

int main(int argc, char *argv []) {

        //Check that user has actually passed a data file for us to read
        //If they haven't print our usage warning and exit the program early
        if(argv[1] == NULL){
                std::cout << "ERROR: Please pass the file you want to stats for" << std::endl;
                std::cout << "Usage:" << std::endl;
                std::cout << "\t./stats_generator data_file.txt" << std::endl;
                return -1;
        }
        //Some variables to hold all of our data
        std::vector<std::string> data_vector;
        std::map<std::string, int> result_data;

        //Load our data from the text file
        std::cout << "[+]\t Loading " << argv[1] << std::endl;
        load_file(std::string(argv[1]), &data_vector);

        //Do a little bit of pre-processing to actually
        //Count all of our data and store it in a key,value pair
        std::cout << "[+]\t Counting data lines" << std::endl;
        count_data(&data_vector, &result_data);

        //Now actually print the things we're interested in
        std::cout << "[+]\tPrinting data" << std::endl;
        //Simply prints all of our counts
        print_data(&result_data);
        //Works out the percentage of the total for each key
        determine_distribution(&result_data);
        //Finds the largest value
        find_max(&result_data);
        //Finds the smallest value
        find_min(&result_data);
}
