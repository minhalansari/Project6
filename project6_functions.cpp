// project proj06
//4 functions to do the fibonacci sequence
//first function vec_2_str takes a vector and returns a string that contains the values of the vector
//second function gen_nstep_vector- takes two parameters - limit and nstep
//generates a fibonacci sequence with the nstep value and returns it as a vector
//third function num_to_nstep_coding calls gen_nstep_vector to get a encoded vector and uses to that return a binary string
//fourth function nstep_coding_to_num returns a long by taking the binary string and using the indexes of the ones to get the indexes of the numbers used in the vector and adds the corresponding number together
#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include "proj06_functions.h"
#include <sstream>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
using std::begin; using std::end;

string vec_2_str(const vector<long>& v){ //takes a vector v as a parameter and returns a string w the values of the vector
    std::stringstream ss;
    for(size_t i = 0; i < v.size(); ++i){ //for loop to go through each item and add to string w a comma
        if(i != 0)
        ss << ",";
        ss << v[i];
    }
    std::string s = ss.str();
    return s;
}

vector<long> gen_nstep_vector (long limit, long nstep){ //returns a vector containing longs of the fibonacci sequence until the limit using the n step number
    //initialize 2 vectors
    vector<long> numbers; 
    vector<long> finalnumbers;
    for(int i = 0; i< limit; i++){ //for loop to add all numbers to number
       numbers.push_back(i);
    }
    numbers[0] = 1; //start it at one
    //add two ones to finalnumbers
    finalnumbers.push_back(1); 
    finalnumbers.push_back(numbers[0]);
    //2 fibonacci sequence
    if(nstep <= 2){
        finalnumbers.push_back(numbers[0] + numbers[1]); 
        while(finalnumbers.back() < limit){
            for(int i2 = 2; finalnumbers.back() < limit; i2 ++){
                if(limit >finalnumbers[i2] + finalnumbers[i2-1]){
                    finalnumbers.push_back(finalnumbers[i2] + finalnumbers[i2-1]);
                }
                else{
                    return finalnumbers;
                }
            
            
            }
        }
    }
    //fibonacci with any number besides 2
    if(nstep > 2){
        long sum = numbers[0]+numbers[1];
        long count = 3;
        finalnumbers.push_back(numbers[0]+numbers[1]);
        while(sum < limit and count < nstep){ //to get seeds 
            for(int i3 = 2; finalnumbers.back() < limit;i3++){
                if(count < nstep){
                    sum += finalnumbers[i3];
                    count +=1;
                    
                    finalnumbers.push_back(sum);
                }
                else{
                    break;
                }
                

            } 
        long sum2=0;
        int i4;
        int count2 = 0;
        while(finalnumbers.back()< limit){ //to calculate the next numbers
            long lastnum = finalnumbers.back();
            long lastindex = finalnumbers.size()-1;
            for(int i5 = lastindex;count2 < nstep;i5 = i5-1){ 
                    count2 += 1;
                    sum2 += finalnumbers[i5];
            }
            if(sum2 <= limit){
                finalnumbers.push_back(sum2);
                sum2=0;
                count2 = 0;
            }
            else{
                break;
            }
            
        }
        }
        return finalnumbers;
    }
    
}   

string num_to_nstep_coding(long num, long nstep){
    vector<long>sequence = gen_nstep_vector(num, nstep); //call function to generate a vector
    int largestnum = sequence.back(); //get the largest number 
    int greedynum = num - largestnum; //subtract the largest number from the limit
    int closestnum;
    int greedynum2;
    int indxgreedynum2;
    string final;
    char ch = '0';
    final.insert(0,sequence.size()-1, '0'); //make the string all zeros
    char ch2 = '1';
    final[final.size()-1] = ch2; //add a one in the final spot
    closestnum = 10000;
    while(greedynum > 0){
        for(int i6 =1; i6 < sequence.size();i6++){
            greedynum2= greedynum - sequence[i6];
            if(greedynum2 < closestnum and greedynum2 >= 0 ){ //find the numbers used
                indxgreedynum2 = i6;
                closestnum = greedynum2;
            }
        }
        greedynum = closestnum;
        final[indxgreedynum2-1] = ch2;
    }
    return final;
}
long nstep_coding_to_num(const string& coding, const vector<long>& nstep_sequence){ //convert binary string to long
    long finalsum = 0; //initilize final sum
    std::vector<int> vec;
    for(int i7=0; i7< coding.size();i7++){
        vec.push_back(coding[i7] - '0'); //add all values of string to a vector
    }
    for(int i8=0; i8< vec.size(); i8++){
        if(vec[i8]==1){
            finalsum += nstep_sequence[i8+1]; //use the index of value 1 in the vec and use the index to add the real number in nstep_sequence to the final sum
        }
    }
    return finalsum;
}

