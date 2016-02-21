//
//  main.cpp
//  SrcParser
//
//  Created by Evgeniy Shumakov on 21.02.16.
//  Copyright © 2016 Evgeniy Shumakov. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;



void srcparser(string arg) {
    
    string filename;
    string line;
    int count;
    // Cheking if single source file in argument
    
    
    if(arg.substr(arg.length()-4,4)==".cpp") {
        filename=arg;
        
        cout << "Source file specified\n";
        try {
            ifstream ifile(filename);
            if(ifile.is_open()) {
                cout << "Filename:\t" << filename << "\n";
                cout << "Included:\n";
                while(getline(ifile,line)) {
                    if(line.substr(0,8)=="#include") {
                        cout << "\t" << line.substr(9,line.length()-9) << "\n";
                        count++;
                    }
                  }
                if(count>0) {
                    cout << "Founds:" << count << "\n";
                }
                else {
                    cout << "No include founds\n";
                }
                ifile.close();
            }
        }
        catch (exception e) {
            cout << e.what() << "\n";
        }
        
        exit(0);
    }
    if(arg.substr(arg.length()-2,2)==".h") {
        filename=arg;
        cout << "Header file specified\n";
        try {
            ifstream ifile(filename);
            if(ifile.is_open()) {
                cout << "Filename:\t" << filename << "\n";
                cout << "Included:\n";
                while(getline(ifile,line)) {
                    if(line.substr(0,8)=="#include") {
                        cout << "\t" << line.substr(9,line.length()-9) << "\n";
                        count++;
                    }
                    
                }
                if(count>0) {
                    cout << "Founds:" << count << "\n";
                }
                else {
                    cout << "No include founds\n";
                }
                ifile.close();
            }
        }
        catch (exception e) {
            cout << e.what() << "\n";
        }
        
        exit(0);
        
    }
    
        cout << "Directory specified\n";
        cout << arg << "\n";
    
        
}

void argparser(int argc, const char * argv[]) {
    
    // Validation number of arguments
    
    if(argc<1) {
        cout << "Incorrect number of arguments\n";
        exit(0);
    }
    
    srcparser(argv[1]);
}

int main(int argc, const char * argv[]) {
    // Test block
    //std::cout << argv[0] << "\n";
    
    argparser(argc,argv);
    
    return 0;
}
