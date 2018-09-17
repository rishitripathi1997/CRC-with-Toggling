//
//  main.cpp
//  CRC
//
//  Created by Rishi Tripathi on 01/08/18.
//  Copyright © 2018 Rishi Tripathi. All rights reserved.
//

#include <iostream>
using namespace std;

string CRCGenerator(string frame, string generator, int frameSize, int generatorSize);
bool recieverSideCheckingForData(string recievingData, string generator, int frameSize, int generatorSize);
char XOR(char a, char b);
string toggleRecievedData(string recievingData);

int main(int argc, const char * argv[]) {
    string frame, generator, CRC = "";
    int frameSize, generatorSize;
    
    cout<<"Enter the frame = ";
    cin>>frame;
    frameSize = int(frame.length());
    
    cout<<"Enter the generator = ";
    cin>>generator;
    generatorSize = int(generator.length());
    
    string frameWithZero, recievingData;
    
    frameWithZero = frame;
    recievingData = frame;
    
    for (int i = frameSize; i<frameSize+generatorSize-1; i++) {
        frameWithZero.append("0");
    }
    cout<<"Frame with Zero = "<<frameWithZero<<endl;
    
    CRC = CRCGenerator(frameWithZero, generator, frameSize, generatorSize);
    cout<<"CRC = "<<CRC<<endl;
    recievingData.append(CRC);
    cout<<"Recieving Data = "<<recievingData<<endl;
    
    /*for (int i = frameSize; i<frameSize+CRC.length(); i++) {
     recievingData.append(to_string(CRC[i]));
     }*/
    
    if(recieverSideCheckingForData(toggleRecievedData(recievingData), generator, frameSize, generatorSize) == true){
        cout<<"No discripency in data real data is recieved by reciever"<<endl;
    }
    else{
        cout<<"yes discripency in data real data is not recieved by reciever"<<endl;
    }
    
    return 0;
}

//this function will generate CRC or remainder
string CRCGenerator(string frameWithZero, string generator, int frameSize, int generatorSize){
    
    char nextdivident[generatorSize];
    int index = 0;
    
    for (int i=0; i<generatorSize; i++) {
        nextdivident[i] = frameWithZero[i];
        index++;
    }
    //cout<<""nextdivident;
    
    while(index <= frameSize){
        if(nextdivident[0] == 1){
            for(int i=0; i<generatorSize; i++){
                nextdivident[i] = XOR(nextdivident[i], generator[i]);
                //cout<<nextdivident<<endl;
            }
            for(int i=0; i<generatorSize-1; i++){
                nextdivident[i] = nextdivident[i+1];
                //cout<<nextdivident<<endl;
            }
            
        }
        else{
            for(int i=0; i<generatorSize; i++){
                nextdivident[i] = XOR(nextdivident[i], '0');
                //cout<<nextdivident<<endl;
            }
            
            for(int i=0; i<generatorSize-1; i++) {
                nextdivident[i] = nextdivident[i+1];
                //cout<<nextdivident<<endl;
            }
        }
        
        if(index < frameSize){
            nextdivident[generatorSize-1] = frameWithZero[index];
        }
        index++;
    }
    //cout<<"CRC pre = "<<nextdivident<<endl;
    string CRC;
    for (int i = 0; i<generatorSize-1; i++) {
        if(nextdivident[i]==0)
            CRC.append("0");
        else
            CRC.append("1");
    }
    //cout<<CRC;
    return CRC;
}

// Recieving side function will return true or false according to data correction.
bool recieverSideCheckingForData(string recievingData, string generator, int frameSize, int generatorSize){
    
    string remainder;
    remainder = CRCGenerator(recievingData, generator, frameSize, generatorSize);
    //cout<<endl<<"Remainder = "<<remainder<<endl;
    for (int i=0; i<remainder.length(); i++) {
        if(remainder[i] == 0)
            return false;
    }
    return true;
}

char XOR(char a, char b){
    if(a == b) return '0';
    else return '1';
}

string toggleRecievedData(string recievingData){
    int r = (rand() % 34);
    cout<<"random number is "<<r<<endl;
    if (r % 2 == 0) {
        if (recievingData[1]==1) {
            recievingData[1] = 0;
            cout<<recievingData[1];
            return  recievingData;
        }
        else{
            recievingData[1] = 1;
            return recievingData;
        }
    }
    return recievingData;
}







